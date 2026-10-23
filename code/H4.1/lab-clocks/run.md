# Run it: three clock processes over HTTP

All commands run from the `code/` folder of a fresh clone. You need Go and `curl`; nothing else.

## 1. Build the program

```
go build -o /tmp/clk/node ./H4.1/lab-clocks/cmd/node
```

## 2. Start three processes (ports 8101 to 8103)

```
/tmp/clk/node -id A -listen 127.0.0.1:8101 -peers B=http://127.0.0.1:8102,C=http://127.0.0.1:8103 &
/tmp/clk/node -id B -listen 127.0.0.1:8102 -peers A=http://127.0.0.1:8101,C=http://127.0.0.1:8103 &
/tmp/clk/node -id C -listen 127.0.0.1:8103 -peers A=http://127.0.0.1:8101,B=http://127.0.0.1:8102 &
```

## 3. A and B each write once, with no message between them

```
curl -s -X POST '127.0.0.1:8101/local?label=x=1'
curl -s -X POST '127.0.0.1:8102/local?label=x=2'
```

The vector clocks are `{A:1}` and `{B:1}`: each has an entry the other lacks, so the writes are concurrent.

## 4. A sends a message to B, then B writes again

```
curl -s -X POST '127.0.0.1:8101/send?to=B&payload=m1'
curl -s -X POST '127.0.0.1:8102/local?label=x=3'
curl -s 127.0.0.1:8101/log
curl -s 127.0.0.1:8102/log
```

B's third event carries `{A:2 B:3}`, which is after A's `{A:1}` and after A's send `{A:2}`.

## 5. Stop C and send to it: the send returns at once (a refused connection is not a hang; a blackholed peer would cost the 500 ms timeout)

```
kill <pid of C>
curl -s -X POST '127.0.0.1:8101/send?to=C&payload=m2'
```

## Recorded on 2026-10-22 on the author's machine

```
--- A and B each write, no messages
{"event":"x=1","lamport":1,"proc":"A","vector":"{A:1}"}
{"event":"x=2","lamport":1,"proc":"B","vector":"{B:1}"}
--- A sends to B, then B writes again
{"event":"send m1","lamport":2,"proc":"A","vector":"{A:2}"}
{"event":"x=3","lamport":4,"proc":"B","vector":"{A:2 B:3}"}
--- logs
A
x=1 L=1 V={A:1}
send m1 L=2 V={A:2}
B
x=2 L=1 V={B:1}
recv m1 L=3 V={A:2 B:2}
x=3 L=4 V={A:2 B:3}
--- kill C, send to it: A does not hang
{"event":"send m2","lamport":3,"proc":"A","vector":"{A:3}"}
```

Note the Lamport times: A's `x=1` and B's `x=2` both have time 1 though they are concurrent, and `x=3` (time 4) is after both.
