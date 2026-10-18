# Run it: three quorum nodes, a fault proxy in front of each

All commands run from the `code/` folder of a fresh clone. You need Go and `curl`; nothing else.

## 1. Build the three programs

```
go build -o /tmp/q/node ./H4.2/lab-quorumkv/cmd/node
go build -o /tmp/q/client ./H4.2/lab-quorumkv/cmd/client
go build -o /tmp/q/faultproxy ./shared/go/faultproxy
```

## 2. Start three nodes (ports 8001 to 8003) and a fault proxy in front of each (7001 to 7003, control ports 9001 to 9003)

```
for i in 1 2 3; do /tmp/q/node -listen 127.0.0.1:800$i & done
for i in 1 2 3; do /tmp/q/faultproxy -listen 127.0.0.1:700$i -upstream 127.0.0.1:800$i -control 127.0.0.1:900$i -seed 1 & done
N=A=127.0.0.1:7001,B=127.0.0.1:7002,C=127.0.0.1:7003
```

## 3. Write and read with N = 3, W = 2, R = 2

```
/tmp/q/client -nodes $N put k v1 1
/tmp/q/client -nodes $N get k
```

## 4. Kill node C, then write and read again: both still work

Find the process with `pgrep -f 'listen 127.0.0.1:8003'` and stop it with `kill`.

```
/tmp/q/client -nodes $N put k v2 2
/tmp/q/client -nodes $N get k
```

## 5. Kill node B too: both fail with `not enough replicas answered`

## 6. Restart B, then make node A hang instead of die

```
curl -X POST 127.0.0.1:9001/blackhole
/tmp/q/client -nodes $N put k v3 3
curl -X POST 127.0.0.1:9001/heal
```

The client waits 500 ms for A, counts it as down, and the operation fails because only B answers.

## Recorded on 2026-10-18 on the author's machine

```
put ok
get k = "v1" (version 1)
--- kill node C
put ok
get k = "v2" (version 2)
--- kill node B too
put failed: quorumkv: not enough replicas answered: 1 of 2 acks
get failed: quorumkv: not enough replicas answered: 1 of 2 replies
--- restart B, blackhole A
put failed: quorumkv: not enough replicas answered: 1 of 2 acks
get failed: quorumkv: not enough replicas answered: 1 of 2 replies
```
