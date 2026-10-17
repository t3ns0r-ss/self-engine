# Design tracks: toolchains confirmed at D0

Confirmed on 2026-10-15 on the lab server (the machine that also hosts this checkout). Plan: `DESIGN_TRACKS_PLAN.md` Sections 3 and 3.1.

| Tool | Version in use | Source checked | Notes |
|---|---|---|---|
| Go | 1.27.2 (`go 1.27` in `code/go.mod`) | https://go.dev/dl/?mode=json, 2026-10-15 | Installed to `~/.local/go`. The plan was tested on 1.24.7; every Go test and script was re-run on 1.27.2. |
| g++ | 16.0.1 snapshot 20260315 (`ubuntu-toolchain-r/test` PPA package `g++-16`) | PPA package list, 2026-10-15 | **Not the 16.2 release the plan names**: the PPA only carries a GCC 16 development snapshot. `-std=c++23` works. Revisit when a released 16.x is packaged (or build 16.2 from source). The plan was tested on 13.3. |
| Node.js | 24.22.0 (current LTS) | https://nodejs.org/dist/index.json | Installed to `~/.local/node`. CI pins Node 22 (unchanged from the CP track). |
| Docker Engine / Compose | 29.9.1 / v5.6.0 | Docker apt repository | Installed with `~/install-root.sh`. |
| Astro / Starlight | as in `package.json` (Astro 7.x) | `npm ls` | The Section 18.6 routes are verified against the real build, not the version in the plan. |

## Docker images (pinned by manifest-list digest)

Each digest is the multi-architecture index digest of the tag, read from the Docker Hub tag API on 2026-10-15.

| Stack | Image | Digest | Licence (checked in the project's own repository) |
|---|---|---|---|
| PostgreSQL | `postgres:18.6` | `sha256:74935e72241653ca55e0414067e6d8763aceb8a810eb51b452253ec3dcfc4336` | PostgreSQL licence (permissive) |
| MySQL | `mysql:9.7.2` | `sha256:c7cb87a9822f499375287930cbff71d6d3b201e346b45108b1115b435ee2df13` | GPLv2 (MySQL Community) |
| Redis | `redis:8.8.3` | `sha256:eb1aa641bc5380ed14442398e45a5a51aeaaac919fab811e4f134eb77c71dd2d` | **Redis 8 is tri-licensed: RSALv2, SSPLv1 or AGPLv3** (its `LICENSE.txt`). Running it locally for labs is fine; see "Questions for Saurabh" in `PROGRESS.md`. |
| Kafka | `apache/kafka:4.3.1` | `sha256:77e3df9054047a88b520d0cc46e16696d3b22022e1d580aeccd2632df6532837` | Apache License 2.0 |

`apache/kafka:4.3.1` is the newest 4.x tag by version number; the newest push is `4.2.2` (2026-09-28), a patch of an older line.

## Lab server check (2026-10-15)

`bash scripts/labserver.sh init` then `check` on this machine (`LABSERVER_HOST=local`):

```
go              go version go1.27.2 linux/amd64
g++             g++ (Ubuntu 16-20260315-1ubuntu1~24~ppa1) 16.0.1 20260315 (experimental)
docker          Docker version 29.9.1
compose         Docker Compose version v5.6.0
git             git version 2.43.0
tar             tar (GNU tar) 1.35
docker daemon: reachable
cpus: 4
memory: 3.7 GiB total, about 2.1 GiB available
disk: 54 GB free
```

Each stack was started with `up --wait`, reached `healthy`, and was stopped with `down -v`. Kafka: one topic was created, one message produced and consumed.

**Host ports.** PostgreSQL (5432) and MySQL (3306) already run on this machine for other services and are left alone. The lab stacks use `LAB_POSTGRES_PORT=15432`, `LAB_MYSQL_PORT=13306`, `LAB_REDIS_PORT=16379`, `LAB_KAFKA_PORT=19092` from the gitignored `.env.labserver`. Stacks are started one at a time because only about 2 GiB of memory is free.

## Go modules

None (`allowed_modules: []`). Expected first additions, each through Section 9.5 when a lab needs it: a PostgreSQL driver, a MySQL driver, a Redis-protocol client, a Kafka client, a WebSocket library.

## Samples re-run on the new toolchains (2026-10-16)

- Appendix A solution unit (`caller-unchanged`, with `check.hpp`): passes under `test_design.sh` with g++ 16 and the address and undefined-behaviour sanitizers.
- Appendix B claim program and the `quorumkv` lab with its tests on `simnet`: pass with Go 1.27.2 and `-race`.
- Appendix C token-bucket kit: `exercise_kit_check.sh` fails the starter, passes the reference, and catches all three mutants (one only by the race detector); kept as `tests/fixtures/design/bucket`.
- `tests/design-scripts.test.mjs` runs every script on synthetic Go and C++ units, including a thread-sanitizer-only mutant.
