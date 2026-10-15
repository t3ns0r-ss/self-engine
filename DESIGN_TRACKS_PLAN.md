# DESIGN_TRACKS_PLAN.md: Low Level Design (LLD) and High Level Design (HLD) Training

**Audience:** the same autonomous coding agent that follows `PLAN.md`, in the same repository.
**Learner:** Saurabh, a working backend engineer (C#/.NET day to day) preparing for design rounds at product-based companies and for deeper systems work. He has real production experience but little formal practice in design interviews and little formal vocabulary for design trade-offs.
**What this adds:** two new tracks on the existing site, built the same way as the competitive-programming (CP) programme in `PLAN.md`: strict dependency order, one idea at a time, recognition first, everything checkable checked by code.

- **LLD track** (low level design): designing the classes, interfaces, and object interactions of one program, in code. Interview names: "machine coding", "object-oriented design".
- **HLD track** (high level design, also called system design): designing the components, data, and traffic flow of a service that runs on many machines.

Read this whole file, then `PLAN.md` Sections 0, 2, 4, 5, 6, 7, 8, 10, 12, 14, 16, and 17 (as revised by its Revision 2). If you believe something here is wrong, write the concern in `PROGRESS.md` under "Questions for Saurabh" and continue with work that doesn't depend on it.

**Revision 2.** This file was revised after an independent review. Changes: the three scripts were fixed and retested (test output no longer leaks into measurements; correct line counts for files without a final newline; renames, deletions, and binary files handled; ladder rungs supported in the kit check); every field that a validation rule checks now exists in a schema; quotas scale for the first topics of a track; the quorum claim is scoped correctly; outbox and change data capture now come after message queues; decision records are taught at the start of HLD; topics were added for interview process, service architecture, conflict resolution, data-access patterns, and optimistic concurrency; and the volume of authored material was cut by about half.

---

## Table of contents

0. Relationship to PLAN.md
1. Goal and quality bar
2. The design recognition procedure
3. Tracks, ids, and settings
4. Repository layout additions
5. LLD curriculum (47 topics)
6. HLD curriculum (52 topics)
7. Data files: schemas
8. Lesson page: template and section rules
9. Code, simulations, and measurement
10. Exercise bank and reference solutions
11. Site additions
12. Build-time validation
13. Per-topic pipeline
14. Milestones and review gates
15. Progress and feedback
16. Definition of Done
17. Failure handling
- Appendix A: sample LLD Recognition Card (Strategy), with measured numbers
- Appendix B: sample HLD Recognition Card (replication quorum), with checked numbers

---

## 0. Relationship to PLAN.md

### 0.1 Inherited unchanged
Everything in `PLAN.md` that is not listed in 0.2 applies as written. In particular:
- Section 0 operating rules 1–9, with "problem" read as "exercise or cited source" where relevant. Rule 1 becomes: never state a link, title, or fact about a real system from memory; open the source first.
- Tech stack (Section 2), self-hosting and deployment (14.2), git workflow (14.0), CI (14.1), `PROGRESS.md` and `FEEDBACK.md` (Section 16), writing rules (Section 7), the storage module and progress page (Section 10).
- Copyright rule: never copy text, diagrams, or code from books, blogs, or papers. Summaries are one line in your own words. Diagrams are drawn fresh in Mermaid.

### 0.2 Overrides and additions
| Topic | Change |
|---|---|
| Curriculum | `curriculum.yaml` rows get a `track` field (`cp`, `lld`, `hld`). `order` is per track. Strict dependency order applies **within a track**. There are **no cross-track dependencies**: a topic's `requires`, `uses`, `techniques`, and card references only name topics of its own track. |
| Ids | LLD topics `L{phase}.{n}`, HLD topics `H{phase}.{n}` (e.g., `L2.1`, `H4.2`). File naming follows PLAN.md Section 3: `L2.1` → data file `L2-1.yaml`, lesson `lld/phase-2/L2-1-strategy.mdx`. Exercise ids are globally unique as `{topic}/{local-id}`, e.g., `L2.1/ex-3`. |
| Lesson template | Section 8 of this file replaces PLAN.md Section 6 for LLD and HLD topics. |
| "Problems" | Replaced by **exercises** (Section 10). There is no online judge for design, so each exercise ships with its own checker: tests, a numeric answer, or an evidence-based rubric. |
| Code | LLD code is C#; HLD code is Python 3 (standard library only). Tested with the scripts in Section 9, not with `stress.sh`. |
| Validation | Section 12 of this file adds to PLAN.md Section 12. |
| Definition of Done | Section 16 of this file replaces PLAN.md Section 17.1 for these tracks. |

### 0.3 Order of work
1. Finish whatever PLAN.md milestone is in progress. Do not interleave.
2. Run milestone **D0** (Section 14) before any design lesson: infrastructure, then the exercise inventory.
3. Design lessons are written at the pace Saurabh studies (PLAN.md pacing rule, per track).

---

## 1. Goal and quality bar

### 1.1 Goal
Take Saurabh from "I can build services that work" to "given an unfamiliar design prompt, I can quickly name the forces in it, choose a structure for a stated reason, and defend the trade-off with numbers or measured code". As in the CP programme, the special emphasis is **recognition**: looking at a requirement and knowing where to look, by checking a structural property rather than matching surface words.

### 1.2 Quality properties, in priority order
1. **Correct:** every claim is proved, computed, simulated, measured, or cited to a source that was opened. Every code sample compiles and passes its tests.
2. **Honest about cost:** every technique is taught with its price (extra code, extra machines, extra failure modes) and with the situations where it should **not** be used. A lesson that teaches only when to use a tool is incomplete.
3. **Builds recognition:** each technique is tied to the force or need it answers, a decisive property, and kill signals.
4. **Sticks:** spaced re-design of related prompts, recognition drills, and number drills.
5. **Calibrated:** exercises rise in small steps, each adding one force.
6. **Readable for Saurabh:** terms defined before use; abbreviations expanded on first use on each page; code or a diagram for every mechanism; every C# or Python construct that is not obvious explained in plain words. No pattern or architecture is explained by metaphor alone (no "like a pizza shop" without the code or diagram that follows immediately).

### 1.3 How CP ideas map to design
| In CP | In LLD | In HLD |
|---|---|---|
| Constraints → complexity budget | Expected changes → edit cost and blast radius | Traffic and data size → QPS, bytes, machines, latency budget |
| Question form → weak signals | Requirement wording → weak signals | Prompt wording → weak signals |
| Structural property = precondition of the proof | Force = the pressure the structure relieves, with a measurable symptom | Property = the assumption under which a guarantee or capacity argument holds |
| Kill signal | Over-engineering signal (the pattern costs more than it saves) | Premature-complexity signal (the component is not needed at this scale) |
| Look-alike pairs | Patterns with similar class diagrams but different forces (State vs Strategy) | Components with similar jobs but different guarantees (queue vs log; cache vs replica) |
| Ladder, one twist per rung | Change ladder: one new requirement per rung | Scale ladder: one new order of magnitude or constraint per rung |
| Brute-force stress test | Behaviour tests, mutants, and change-cost measurement | Exhaustive checks and seeded simulations of the stated math |
| Checkpoint | Timed build with tests plus rubric | Timed design plus rubric |

### 1.4 Pedagogical inspiration
- **LLD:** the Gang of Four's *Design Patterns* (patterns as named solutions to forces); Fowler's *Refactoring* (smells and small safe steps); Liskov's substitution principle (Liskov 1987; Liskov and Wing 1994), stated with Meyer's design-by-contract rules for preconditions and postconditions; test-driven design. Emphasise forces and measurement over memorising UML.
- **HLD:** Kleppmann's *Designing Data-Intensive Applications* (trade-offs stated precisely); the Google *Site Reliability Engineering* book (SLOs, failure); the classic papers (Section 10.6); queueing theory for latency.
- Read these to check your understanding. Do not copy their text or figures.

---

## 2. The design recognition procedure

Every lesson teaches its techniques through this procedure. It is the design version of the three-layer procedure in `PLAN.md` Section 11.1.

### 2.1 Layer 1: numbers first
- **LLD:** list what is *expected to change* and how often, using only the prompt and the clarifying answers: how many variants exist today, how many more are plausible, which dimensions vary independently, who tests and owns each part. This gives the **trade-off table** (2.3).
- **HLD:** compute the **load**: requests per second (QPS), reads versus writes, stored bytes per year, bandwidth, peak factor, latency target, availability target. Then the **budget**: how many machines, how much memory, whether one machine can possibly do it.

### 2.2 Layer 2: wording → candidates (weak signals)
Wording only raises candidates; it never decides. A weak signal is always a pair: how the requirement is worded, and the shape of the numbers or variants around it. "There is a database" or "there are several vehicle types" alone is never a weak signal.

### 2.3 Layer 3: the decisive property → decision
- **LLD force:** a named pressure with a measurable symptom. Symptoms used in this course:
  - **Blast radius** of a change: the number of *other* pre-existing, separately tested behaviours whose code sits in the same function or class body as an edited line (exact rule in Section 9.3).
  - **Edit cost:** files and lines touched per change request (measured by `change_cost.sh`).
  - **Branch growth:** how the number of branches grows as variants are added.
  - **Testability:** whether a class can be tested without its real collaborators.
  
  The decisive property says which symptom the pattern removes. The **trade-off table** shows the pattern's overhead, its edit cost per change, and its blast radius, next to the plain design's. There is usually **no single break-even number**, because overhead is counted in lines while blast radius is counted in behaviours put at risk. The lesson states the trade in words and numbers (Appendix A shows how).
- **HLD property:** the assumption under which a guarantee or capacity argument holds. For example: "reads can tolerate staleness of up to 1 second", "keys are spread evenly enough that no shard exceeds one machine's capacity", "write quorum W plus read quorum R exceeds the replica count N, and the read starts after the write was acknowledged".

Every card states the property, **how to test it** in one check, and its **kill signals**. Kill signals include the over-engineering case (the technique would cost more than it saves at the stated numbers) with a concrete instance.

### 2.4 Decision records
Every worked example and reference solution ends with a short **decision record**: the choice, the numbers or measured costs behind it, the two best alternatives, and the change in numbers that would flip the decision ("if reads exceed 50 000 per second, add a cache; below that, the database alone is enough"). LLD teaches the format in L1.1; HLD teaches it in H0.2. Earlier topics in each track write a two-line version (choice and reason).

---

## 3. Tracks, ids, and settings

Create `src/data/design.config.yaml`:

```yaml
lld_language: csharp          # change only if Saurabh says so in PROGRESS.md (see below)
dotnet_target: net10.0        # the current Long-Term Support (LTS) release; check Microsoft's .NET support policy page at D0
hld_language: python          # simulations and calculators; standard library only
hld_python_min: "3.10"
```

**Changing `lld_language`** is a deliberate project change, not a setting the scripts read: it requires updating Section 9.2's unit layout, block 3 of `test_design.sh`, the kit `test.sh` files, and the CI job. Record the change under "Questions for Saurabh" first and wait for approval.

**`dotnet_target`:** .NET 8 support ends in November 2026, so new code targets the current LTS release. Confirm the version on Microsoft's support policy page during D0 and pin the SDK in CI (`actions/setup-dotnet` with an exact version) and in a `global.json`.

**Cross-track links:** a lesson may link to another track only in an optional final `## See also` section (Section 8). These links are never prerequisites.

---

## 4. Repository layout additions

```
.
├── DESIGN_TRACKS_PLAN.md       # this file
├── global.json                 # pins the .NET SDK version
├── code/
│   ├── _shared/constants.json  # generated from src/data/constants.yaml (Section 9.6); committed
│   ├── L2.1/
│   │   └── strategy-fee/                 # an LLD pattern unit (Section 9.3)
│   │       ├── unit.yaml
│   │       ├── naive/{base/, scenarios/NN-name.patch, test.sh}
│   │       ├── patterned/{base/, scenarios/NN-name.patch, test.sh}
│   │       └── measured-naive.tsv, measured-patterned.tsv
│   └── H4.2/
│       ├── claim-1/                      # an HLD claim check (Section 9.5): check.py + expected.txt
│       └── calc-quorum-table/            # an HLD calculator (Section 9.6): calc.py + expected.txt
├── exercises/                  # exercise kits Saurabh works in locally (Section 10.3)
│   └── L2.1/
│       ├── ex-3/{README.md, test.sh, starter/, tests/}
│       └── ladder/rung-1/ … rung-6/      # one kit per rung of a change ladder
├── reference/                  # reference solutions, same relative paths as the kits (Section 10.4)
├── reference-mutants/          # deliberately wrong solutions, same relative paths (Section 10.3)
├── notes/design/               # private notes per topic (never rendered): sources checked, calibration, dropped ideas
├── scripts/
│   ├── change_cost.sh          # Section 9.4 (exact code given, tested)
│   ├── test_design.sh          # Section 9.7 (exact code given, tested)
│   ├── exercise_kit_check.sh   # Section 9.8 (exact code given, tested)
│   ├── constants_export.mjs    # Section 9.6
│   └── keyword_collisions.mjs  # Section 12, D11
└── src/
    ├── data/
    │   ├── design.config.yaml
    │   ├── constants.yaml      # sourced planning constants for HLD (Section 7.5)
    │   ├── rubrics.yaml        # Section 10.7
    │   ├── product-names.yaml  # Section 12, D9
    │   ├── topics/             # L2-1.yaml, H4-2.yaml, … (Section 7.2)
    │   └── exercises/          # one file per topic (Section 7.3) + INVENTORY.yaml (Section 10.10)
    └── content/docs/
        ├── lld/phase-0/ … phase-7/
        └── hld/phase-0/ … phase-8/
```

`.gitignore`: add `**/bin/`, `**/obj/`, `**/__pycache__/`, `**/.build/`.

---

## 5. LLD curriculum (47 topics)

Topics are ordered by `order` within the track; "requires" is explicit. Keywords work as in PLAN.md Section 4 (case-insensitive whole-phrase search). A lesson may not use a later topic's keyword outside "What this topic does not cover".

**Topic kinds** (a column in `curriculum.yaml`, `kind:`):
- `measured`: has at least one `measured` claim and therefore two pattern units from different domains (Section 9.3). Section 1 of the lesson shows `change_cost.sh` numbers.
- `standard`: claims are proved, illustrated with tested code, or cited; no pattern units required. Section 1 shows a naive program and its concrete problem, demonstrated by a failing test or a smell.
- `light`: recognition-focused coverage of a less common pattern. 1–2 cards, a ladder of 3–4 rungs, drill of 6; no pattern units; no checkpoint (its drill items join the phase exam pool instead).
- `capstone`: no new technique (L7.7).

### Phase L0: Object foundations
| order | id | slug | kind | title | requires | keywords |
|---|---|---|---|---|---|---|
| 1 | L0.1 | classes-invariants | standard | Classes, encapsulation, invariants, immutability | — | class invariant, immutable object |
| 2 | L0.2 | polymorphism | standard | Interfaces, abstract classes, dynamic dispatch, how a virtual call works | L0.1 | dynamic dispatch, virtual method, abstract class |
| 3 | L0.3 | relationships | standard | Association, aggregation, composition, inheritance; composition over inheritance | L0.1, L0.2 | composition over inheritance, aggregation |
| 4 | L0.4 | uml | standard | Reading and drawing class and sequence diagrams (Mermaid) | L0.3 | class diagram, sequence diagram |
| 5 | L0.5 | srp-ocp | measured | Single Responsibility and Open/Closed principles, measured with change scenarios | L0.3 | single responsibility principle, open/closed principle, blast radius |
| 6 | L0.6 | lsp-isp-dip | standard | Liskov Substitution (as contracts), Interface Segregation, Dependency Inversion | L0.2, L0.5 | liskov substitution, interface segregation, dependency inversion |
| 7 | L0.7 | smells | standard | Code smells and safe refactoring steps | L0.5, L0.6 | code smell, refactoring step |
| 8 | L0.8 | testable-design | standard | Unit tests, test doubles (stubs, fakes, spies), testability as a design criterion | L0.6 | test double, stub object, fake object |

### Phase L1: From requirements to a model
| order | id | slug | kind | title | requires | keywords |
|---|---|---|---|---|---|---|
| 9 | L1.1 | requirements | standard | Clarifying requirements: scope, assumptions, use cases, what to ask; decision records | L0.5 | functional requirement, non-functional requirement |
| 10 | L1.2 | entities | standard | Entities from nouns, behaviour from verbs, assigning responsibility | L1.1, L0.5 | information expert, responsibility assignment |
| 11 | L1.3 | state-modelling | standard | State, lifecycle, enums, illegal transitions, invariants over time | L1.2, L0.1 | object lifecycle, transition table |
| 12 | L1.4 | api-design | standard | Method signatures, errors (exceptions vs result types), validation, idempotency | L1.2, L0.6 | result type, idempotent method |
| 13 | L1.5 | data-in-memory | standard | Choosing in-memory data structures for the operations an object must support | L1.4 | data structure choice, operation cost table |
| 14 | L1.6 | machine-coding-round | standard | How a machine-coding round runs: time-boxing, narrating, extending under pressure | L1.1, L1.2, L0.8 | machine coding round |

### Phase L2: Varying behaviour
| order | id | slug | kind | title | requires | keywords |
|---|---|---|---|---|---|---|
| 15 | L2.1 | strategy | measured | Strategy | L0.5, L0.6, L1.2 | strategy pattern |
| 16 | L2.2 | template-method | measured | Template Method (and when inheritance is fine) | L0.3, L2.1 | template method |
| 17 | L2.3 | state | measured | State | L1.3, L2.1 | state pattern |
| 18 | L2.4 | command | measured | Command, undo and redo | L2.1, L0.8 | command pattern, undo stack |
| 19 | L2.5 | observer | measured | Observer and event models (push vs pull) | L0.6, L1.4 | observer pattern, event listener |

### Phase L3: Creating objects
| order | id | slug | kind | title | requires | keywords |
|---|---|---|---|---|---|---|
| 20 | L3.1 | factory | measured | Simple Factory and Factory Method; registries instead of switch | L2.1 | factory method, simple factory |
| 21 | L3.2 | abstract-factory | measured | Abstract Factory | L3.1 | abstract factory, product family |
| 22 | L3.3 | builder | measured | Builder; telescoping constructors; immutable construction | L0.1, L1.4 | builder pattern, telescoping constructor |
| 23 | L3.4 | singleton-di | measured | Singleton and its costs; dependency injection and the composition root | L0.6, L0.8, L3.1 | singleton pattern, dependency injection, composition root |
| 24 | L3.5 | prototype | light | Prototype and copying objects (shallow vs deep) | L0.1, L3.1 | prototype pattern, deep copy |

### Phase L4: Structuring objects
| order | id | slug | kind | title | requires | keywords |
|---|---|---|---|---|---|---|
| 25 | L4.1 | adapter | measured | Adapter | L0.6 | adapter pattern |
| 26 | L4.2 | decorator | measured | Decorator | L0.3, L2.1 | decorator pattern |
| 27 | L4.3 | composite | measured | Composite | L0.2, L0.3 | composite pattern |
| 28 | L4.4 | facade | measured | Facade | L0.5 | facade pattern |
| 29 | L4.5 | proxy | measured | Proxy (virtual, protection, caching) | L4.1, L0.6 | proxy pattern, lazy loading |
| 30 | L4.6 | bridge-flyweight | light | Bridge and Flyweight | L2.1, L4.2 | bridge pattern, flyweight pattern |
| 31 | L4.7 | data-access | measured | Repository, Unit of Work, and Null Object | L0.6, L0.8, L4.4 | repository pattern, unit of work, null object |

### Phase L5: Collaboration between objects
| order | id | slug | kind | title | requires | keywords |
|---|---|---|---|---|---|---|
| 32 | L5.1 | chain | measured | Chain of Responsibility | L2.1, L4.2 | chain of responsibility |
| 33 | L5.2 | mediator | measured | Mediator | L2.5 | mediator pattern |
| 34 | L5.3 | iterator | measured | Iterator and lazy sequences | L0.2, L4.3 | iterator pattern, lazy sequence |
| 35 | L5.4 | memento | light | Memento and snapshots | L2.4 | memento pattern |
| 36 | L5.5 | visitor | light | Visitor and double dispatch | L0.2, L4.3 | visitor pattern, double dispatch |

### Phase L6: Concurrency in designs
| order | id | slug | kind | title | requires | keywords |
|---|---|---|---|---|---|---|
| 37 | L6.1 | races-locks | standard | Race conditions, atomicity, visibility, locks, deadlock and lock ordering | L0.1 | race condition, deadlock, lock ordering |
| 38 | L6.2 | thread-safe-objects | standard | Thread-safe objects: immutability, confinement, concurrent collections, lock granularity, optimistic concurrency (compare-and-swap, version numbers) | L6.1, L1.5 | lock granularity, compare-and-swap, optimistic concurrency |
| 39 | L6.3 | producer-consumer | standard | Producer–consumer, blocking queues, thread pools | L6.2 | blocking queue, thread pool |
| 40 | L6.4 | async | standard | Async/await, timeouts, cancellation | L6.3 | async/await, cancellation token |

### Phase L7: Whole systems (integration)
Each L7 lesson opens with "This topic combines X and Y." linking both. Each family lesson teaches a **family skeleton** (the base design most prompts of that family share) plus the three mistakes that recur in that family; its ladder is one evolving system (Section 10.2).
| order | id | slug | kind | title | requires | keywords |
|---|---|---|---|---|---|---|
| 41 | L7.1 | family-allocation | standard | Allocation systems: parking lot, locker, hotel and seat booking | L2.1, L2.3, L6.2 | allocation system |
| 42 | L7.2 | family-state-machines | standard | State-machine systems: vending machine, ATM, elevator, traffic light | L2.3, L2.5, L6.1 | state-machine system |
| 43 | L7.3 | family-caches | standard | Cache and store systems: LRU and LFU cache, key-value store with expiry, rate limiter | L1.5, L2.1, L6.2 | eviction policy, token bucket |
| 44 | L7.4 | family-games | standard | Game systems: tic-tac-toe, snake and ladder, chess | L2.1, L2.3, L4.3 | game system |
| 45 | L7.5 | family-events | standard | Event-driven systems: notification service, logger, in-memory pub/sub, order book | L2.5, L5.1, L6.3 | event-driven system, order book |
| 46 | L7.6 | family-hierarchy-and-marketplace | standard | Hierarchies and marketplaces: file system, spreadsheet, expense splitting, ride matching | L4.3, L5.5, L6.2 | expense splitting, ride matching |
| 47 | L7.7 | lld-recognition | capstone | Recognition: mixed prompts, family and pattern not given | all LLD topics, expanded | (none) |

Notes:
- "all LLD topics" is expanded to explicit ids in `curriculum.yaml`, as in PLAN.md Section 4.
- L7.7 has no new technique: its lesson is the recognition procedure, a recap handbook, and mixed mock rounds; Sections 4, 6, and 7 of the template are replaced by the recap.
- Anti-patterns are taught inside the topic that prevents them: God class in L0.5, inappropriate inheritance in L0.3, Singleton overuse in L3.4, and pattern overuse in every pattern lesson's kill signals.

---

## 6. HLD curriculum (52 topics)

Same conventions as Section 5 (HLD topics are all `standard` except H8.10, `capstone`). Numbers in lessons come from `constants.yaml` (Section 7.5) and calculator units (Section 9.6), never from memory.

### Phase H0: Numbers, vocabulary, and the design round
| order | id | slug | title | requires | keywords |
|---|---|---|---|---|---|
| 1 | H0.1 | latency-throughput | Latency, throughput, percentiles, tail latency, Little's law | — | tail latency, little's law |
| 2 | H0.2 | estimation | Back-of-envelope estimation: QPS, storage, bandwidth, machines, error bounds; decision records | H0.1 | back-of-envelope, peak factor |
| 3 | H0.3 | availability | Availability math: nines, serial and parallel composition, MTBF, MTTR, SLI, SLO, SLA | H0.1 | mean time between failures, service level objective |
| 4 | H0.4 | queueing | Queueing basics: utilisation and latency, why systems fall over near full load | H0.1 | utilisation, queueing delay |
| 5 | H0.5 | networking | Networking for designers: DNS, TCP vs UDP, HTTP versions, TLS cost, L4 vs L7 load balancers, WebSocket, gRPC | H0.1 | tcp handshake, websocket, grpc |
| 6 | H0.6 | api-design | API design: REST resources, idempotency keys, pagination (offset vs cursor), versioning, errors | H0.5 | cursor pagination, idempotency key |
| 7 | H0.7 | design-round | How a system design round runs: scoping, time-boxing, narrating, handling pushback | H0.2, H0.6 | system design round |

### Phase H1: Data on one machine
| order | id | slug | title | requires | keywords |
|---|---|---|---|---|---|
| 8 | H1.1 | data-models | Data models by access pattern: relational, document, key-value, wide-column, graph, time-series; transactional (OLTP) vs analytical (OLAP) workloads | H0.2 | document store, wide-column store, olap |
| 9 | H1.2 | indexes | Indexes: B-tree vs log-structured merge tree (LSM), read/write/space amplification | H1.1 | b-tree, lsm tree, write amplification |
| 10 | H1.3 | transactions | Transactions, ACID, isolation levels, anomalies (lost update, write skew) | H1.1 | isolation level, write skew, lost update |
| 11 | H1.4 | schema-design | Schema design from access patterns; normalisation vs denormalisation | H1.1, H1.2 | denormalization, denormalisation |
| 12 | H1.5 | single-node-cache | Caching on one machine: cache-aside, write-through, write-back, eviction, hit-rate math | H0.2, H1.2 | cache-aside, write-through, hit rate |

### Phase H2: Scaling reads and splitting services
| order | id | slug | title | requires | keywords |
|---|---|---|---|---|---|
| 13 | H2.1 | stateless-lb | Stateless services, horizontal scaling, load-balancing algorithms | H0.4, H0.5 | horizontal scaling, least connections, power of two choices |
| 14 | H2.2 | caching-at-scale | Caches at scale: CDN, shared cache, TTL, invalidation, stampede control | H1.5, H2.1 | content delivery network, cache stampede |
| 15 | H2.3 | replication | Replication: leader–follower, lag, read-your-writes, monotonic reads, failover | H1.3, H2.1 | replication lag, read-your-writes, failover |
| 16 | H2.4 | read-scaling | Read-scaling patterns: replicas, materialised views, fan-out on write vs on read | H2.2, H2.3 | materialized view, fan-out on write |
| 17 | H2.5 | service-architecture | Monolith vs services, API gateway, service discovery | H2.1, H0.6 | api gateway, service discovery, microservices |

### Phase H3: Scaling writes and data
| order | id | slug | title | requires | keywords |
|---|---|---|---|---|---|
| 18 | H3.1 | partitioning | Partitioning (sharding): range vs hash, hot spots, rebalancing | H2.3, H1.4 | partition key, rebalancing |
| 19 | H3.2 | consistent-hashing | Consistent hashing and virtual nodes | H3.1 | consistent hashing, virtual node |
| 20 | H3.3 | sharded-indexes | Secondary indexes on sharded data: local vs global, scatter–gather | H3.1, H1.2 | scatter-gather, global secondary index |
| 21 | H3.4 | ids-ordering | Unique ids and ordering: UUID, ticket server, Snowflake-style ids, clock caveats | H3.1 | snowflake id, k-sortable |
| 22 | H3.5 | hot-keys | Hot keys and skew: salting, splitting, request coalescing | H3.1, H2.2 | hot key, key salting, request coalescing |

### Phase H4: Consistency and coordination
| order | id | slug | title | requires | keywords |
|---|---|---|---|---|---|
| 23 | H4.1 | time-ordering | Time and ordering: clocks, Lamport clocks, vector clocks, happened-before | H3.4, H0.5 | lamport clock, vector clock, happened-before |
| 24 | H4.2 | quorums | Replication with quorums: N, W, R; sloppy quorums; read repair; anti-entropy | H2.3, H3.2, H4.1 | read quorum, write quorum, read repair, sloppy quorum |
| 25 | H4.3 | conflicts | Multi-leader and leaderless conflicts: last-write-wins pitfalls, version vectors, CRDT basics | H4.1, H4.2 | last-write-wins, version vector, crdt |
| 26 | H4.4 | cap-consistency | CAP and PACELC stated precisely; the spectrum of consistency models | H4.2, H4.3 | cap theorem, linearizability, eventual consistency |
| 27 | H4.5 | consensus | Consensus: leader election and log replication (Raft level), leases, fencing tokens | H4.4 | raft, leader election, fencing token |

### Phase H5: Asynchronous work and overload
| order | id | slug | title | requires | keywords |
|---|---|---|---|---|---|
| 28 | H5.1 | queues-logs | Queues and logs: partitions, consumer groups, ordering, delivery semantics, retries, dead-letter queues | H4.2, H3.1 | consumer group, at-least-once, dead-letter queue |
| 29 | H5.2 | distributed-transactions | Distributed transactions: two-phase commit, sagas, transactional outbox, change data capture, idempotent consumers | H1.3, H4.5, H5.1 | two-phase commit, saga, transactional outbox, change data capture |
| 30 | H5.3 | stream-batch | Batch vs stream processing; event time vs processing time; windows | H5.1 | stream processing, event time |
| 31 | H5.4 | pubsub-push | Pub/sub, notification fan-out, webhooks, push channels | H5.1, H2.4 | publish-subscribe, webhook, notification fan-out |
| 32 | H5.5 | scheduling | Job scheduling, delayed jobs, workflows | H5.1, H4.5 | job scheduler, delayed job, workflow engine |
| 33 | H5.6 | overload | Overload control: rate limiting, backpressure, load shedding, retries with jitter, circuit breakers | H0.4, H5.1 | rate limiting, load shedding, circuit breaker, retry storm |

### Phase H6: Specialised structures and services
| order | id | slug | title | requires | keywords |
|---|---|---|---|---|---|
| 34 | H6.1 | probabilistic | Probabilistic structures: Bloom filter, count-min sketch, HyperLogLog | H0.2 | bloom filter, count-min sketch, hyperloglog |
| 35 | H6.2 | search | Search: inverted index, ranking basics, sharded search, typeahead | H1.2, H3.3 | inverted index, typeahead |
| 36 | H6.3 | geo | Geospatial indexing: geohash, quadtree, cell ids | H3.1 | geohash, quadtree |
| 37 | H6.4 | blob-storage | Blob storage and large files: chunking, deduplication, resumable upload, metadata vs data | H3.1, H2.2 | resumable upload, content-defined chunking |

### Phase H7: Running it for real
| order | id | slug | title | requires | keywords |
|---|---|---|---|---|---|
| 38 | H7.1 | resilience | Failure modes, timeouts, bulkheads, graceful degradation, multi-zone and multi-region, recovery point and time objectives | H4.4, H5.6 | bulkhead, recovery point objective, multi-region |
| 39 | H7.2 | observability | Metrics, logs, traces; SLO-based alerting; capacity planning | H0.3, H5.3 | error budget, distributed tracing |
| 40 | H7.3 | deployment | Deployments: rolling, blue/green, canary, feature flags, schema migrations without downtime | H7.1, H1.4 | canary release, blue/green deployment, expand and contract |
| 41 | H7.4 | security-tenancy | Security basics and multi-tenancy: authentication vs authorisation, tokens, encryption, tenant isolation, abuse | H0.5, H0.6 | oauth, multi-tenancy, noisy neighbour |
| 42 | H7.5 | build-vs-buy | Build vs buy and cost models | H7.1 | build vs buy, cost per request |

### Phase H8: Whole systems (integration)
Each H8 lesson opens with "This topic combines X and Y." Each family lesson teaches a **family skeleton**, its scale ladder (Section 10.2), and the three mistakes that recur in that family.
| order | id | slug | title | requires | keywords |
|---|---|---|---|---|---|
| 43 | H8.1 | family-lookup | Read-heavy lookup: URL shortener, paste service, key-value store | H2.2, H3.2, H3.4 | url shortener |
| 44 | H8.2 | family-feeds | Feeds: social timeline, news feed, activity stream | H2.4, H3.5, H5.4 | news feed |
| 45 | H8.3 | family-realtime | Real-time collaboration: chat, presence, live comments, collaborative editing (basic) | H0.5, H5.4, H4.3 | chat system, presence service, collaborative editing |
| 46 | H8.4 | family-storage-media | Storage and media: file sync, video upload and streaming, object store | H6.4, H5.5 | file sync, video pipeline |
| 47 | H8.5 | family-search-discovery | Search and discovery: typeahead, web crawler, trending and top-K | H6.1, H6.2, H5.3 | web crawler, top-k |
| 48 | H8.6 | family-geo-matching | Geo and matching: nearby places, ride hailing, delivery dispatch | H6.3, H5.4, H3.5 | ride hailing, nearby search |
| 49 | H8.7 | family-money-booking | Money and booking: payments, wallets and ledgers, ticket booking, flash sales | H5.2, H1.3, H5.6 | double-entry ledger, flash sale |
| 50 | H8.8 | family-integration | Data integration: multi-tenant ETL and ERP sync, idempotent upserts, dedupe by external key, reconciliation | H5.5, H5.2, H7.4 | etl pipeline, reconciliation job |
| 51 | H8.9 | family-infra | Infrastructure services: rate limiter, distributed cache, distributed lock, id generator, message queue, metrics system | H5.6, H4.5, H3.2, H7.2 | distributed lock service |
| 52 | H8.10 | hld-recognition | Recognition: mixed prompts, family and components not given | all HLD topics, expanded | (none) |

Notes:
- Technology names (specific databases, queues, caches) may appear in an HLD lesson only as **examples of a category already defined** in that lesson, inside `:::example[Real systems]` blocks, each with a cited source for any factual claim (Section 12, D9). Cards name properties, never products.
- "all HLD topics" is expanded to explicit ids in `curriculum.yaml`.

---

## 7. Data files: schemas

### 7.1 Curriculum rows
Append the LLD and HLD rows to `src/data/curriculum.yaml` with `track` (`lld` or `hld`), `phase`, `order` (per track), `id`, `slug`, `kind` (`measured | standard | light | capstone`; HLD rows use `standard` or `capstone`), `title`, explicit `requires`, and `keywords`. Add `track: cp` to existing rows. Zod: `track` is one of `cp | lld | hld`; every `requires` id exists in the same track with a smaller `order`; the first topic of each track has empty `requires`.

### 7.2 Topic data file: `src/data/topics/{id-with-dash}.yaml`
Same top-level structure as `PLAN.md` Section 5 (as revised), with these fields:

```yaml
id: "L2.1"
track: lld                          # lld | hld

uses:                               # every earlier topic relied on (same track); drives the header and "What you need"
  - {topic: "L0.5", what: "Change scenarios and blast radius"}
  - {topic: "L0.6", what: "Depending on an interface instead of a concrete class"}
  - {topic: "L1.2", what: "Assigning a responsibility to one class"}

claims:                             # one entry per numbered claim in the lesson (Section 8.4)
  - id: "L2.1.1"
    kind: measured                  # proved | computed | simulated | measured | cited
    title: "Adding a pricing plan edits no existing pricing logic, at a cost in lines"
    plain_words: "With one class per plan, a new plan is a new class plus one line of wiring; the old plans are untouched."
    evidence: ["L2.1/strategy-fee", "L2.1/strategy-notify"]   # code units under code/; measured needs >= 2 with different domains
    source: null                    # cited only: {title, url, accessed: YYYY-MM-DD, section}
  - id: "L2.1.2"
    kind: proved
    title: "Callers that depend only on the shared signature never change when a variant is added"
    plain_words: "If the calling code only knows the interface, a new class that implements it cannot require edits to that calling code."
    evidence: ["L2.1/caller-unchanged"]   # a solution unit whose tests compile the unchanged caller against a new variant
    source: null

cards:                              # 1–4 per topic (light topics: 1–2)
  - id: strategy
    name: "Strategy"
    force: "Behaviour that varies independently of the code that uses it, with variants added or changed over time."   # HLD: `need`
    decisive_property: "All variants fit one method signature, and callers do not need to know which variant runs."
    from_claim: "L2.1.2"
    how_to_test: "List the variants and write the one signature they could all share. If the inputs differ per variant, the property does not hold yet."
    trade_off_table:                # LLD; from pattern units via change_cost.sh, never by hand. HLD: `capacity_table` (below)
      units: ["L2.1/strategy-fee", "L2.1/strategy-notify"]
      overhead: "+3 files and +14 non-blank lines for two plans (fee unit)."
      per_change: "About 8 lines touched per added plan, against 2 for a switch case (fee unit)."
      blast_radius: "Switch: grows by one other behaviour per plan added. Strategy: 0 for plan logic."
      verdict: "No single break-even: Strategy costs lines and buys isolation. It pays when plans are added or changed repeatedly and are tested or owned separately."
    constraint_shapes:              # LLD: variant shapes; HLD: load shapes. 1–3, each with arithmetic
      - "3 or more variants now, or 2 plus a stated expectation of more; each variant longer than one or two lines"
    weak_signals:                   # 2–4, each {form, shape}
      - form: "The prompt says 'support different' pricing, payment, discount, routing, or sorting rules"
        shape: "At least 3 named kinds, or 'new kinds will be added', and the kinds differ in a calculation or decision, not only in stored data"
    kill_signals:                   # ≥ 2; at least one is an over-engineering signal with numbers
      - "Two variants, no expected change, one line each: a plain conditional is 14 lines shorter (measured)"
      - "Variants differ in the data they carry, not in what they do: use fields or subtypes"
    in_action:                      # same shape as PLAN.md 5; candidates must include the simplest option
      statement: "…"
      constraints: "…"
      budget: "…"
      candidates:
        - {tool: "Plain conditional", verdict: rejected, because: "…"}
        - {tool: "Strategy", verdict: chosen, because: "…"}
      property_check: "…"
      decision: "…"
    examples:                       # ≥ 2 positive, ≥ 2 negative; ≥ 1 of each is inline with numbers
      positive:
        - inline: {input: "…", answer: "…", why: "…"}
      negative:
        - inline: {input: "…", answer: "…", why: "…"}
          correct_tool: {topic: "L0.3", card: subtype-per-variant}   # or {simplest: "plain conditional"}
    lookalikes:                     # structured references to this or earlier topics only
      - description: "One subclass per variant (inheritance, from L0.3)"
        tool: {topic: "L0.3", card: subtype-per-variant}
        flipping_difference: "Subclasses fix the variant when the object is created; Strategy lets the caller pick or change it at run time and keeps variants separate from the class that uses them."
    cost: "Time: one extra method call per use. Code: see trade_off_table."
```

The State-versus-Strategy pair is written in L2.3's lesson (State is taught after Strategy), where the order rule allows it.

**HLD cards** use the same shape with these replacements:
- `force` → `need`: the requirement the technique answers, with its number ("reads exceed what one primary can serve").
- `trade_off_table` → `capacity_table`: `{units: [calc units], threshold: "the number at which the technique becomes necessary", price: "extra machines, staleness, latency, failure modes"}`.
- `decisive_property`: the assumption under which the guarantee holds (Appendix B).
- Claim kinds used: `proved`, `computed`, `simulated` (seeded simulation with a stated tolerance), `cited`.

### 7.3 Exercise file: `src/data/exercises/{id-with-dash}.yaml`

```yaml
topic: "L2.1"
exercises:
  - id: ex-3                        # local id; the global id is "L2.1/ex-3" (used in storage and links)
    role: ladder                    # ladder | worked_example | drill | checkpoint | review | exam
                                    # ladder and worked_example are the practice set; the rest are reserved (Section 10.8)
    type: change_ladder             # LLD: recognise | refactor | build | change_ladder | mock
                                    # HLD: recognise | estimate | deep_dive | scale_ladder | failure | mock
    title: "Parking fees"
    prompt: "Own words, at most 120 words. States the task, nothing about the solution."
    inspired_by: null               # {title, url, accessed} if a public source gave the idea; a link only
    card: strategy                  # ladder rungs and worked examples: the card exercised (null on a no-new-structure rung)
    rung: 3                         # ladder only
    new_force: "Pricing now depends on the day as well as the duration."     # ladder only; exactly one per rung
    needs_new_structure: true       # ladder only; at least one rung per ladder is false
    review_set: null                # review only: 1 or 2
    answer: null                    # recognise only; see below
    clarifying:                     # build, deep_dive, scale_ladder, mock: ≥ 4 entries, ≥ 2 critical
      - {q: "Which currencies?", a: "One. Whole numbers only.", critical: false}
      - {q: "Can a customer switch plans mid-stay?", a: "No.", critical: true}
    checkers:                       # a list; allowed combinations per type in Section 10.1
      - {kind: kit, path: "L2.1/ladder/rung-3"}                # exercises/<path> and reference/<path>
      # - {kind: numeric, calc: "H0.2/calc-photo-uploads", key: "peak_reads_per_second", unit: "requests per second", factor: 2}
      # - {kind: rubric, id: "rubric-lld-build-v1"}
    reference: "reference/L2.1/ladder/rung-3"
    alternatives: ["Plain conditional until the 3rd plan; better when plans never change"]
    hints: ["…", "…", "…"]          # practice set only; exactly 3, progressive
    time_limit_minutes: null        # required for checkpoint and exam items and for type mock
    techniques: ["L2.1", "L0.5"]    # topics the reference uses; each this topic or earlier, same track
    checked_on: "2026-10-14"        # date you ran the kit, recomputed the numbers, or opened the cited source
```

`answer` for `recognise` exercises is one of:
```yaml
answer: {kind: card, card: {topic: "L2.1", card: strategy}, property: "All plans fit fee(minutes)", why_others_fail: "…"}
answer: {kind: none, simplest: "plain conditional", why: "Two fixed plans; Strategy would add 3 files and 14 lines for no expected change"}
```

### 7.4 Rubrics: `src/data/rubrics.yaml`
Format and the standard rubrics are in Section 10.7.

### 7.5 Planning constants: `src/data/constants.yaml` (HLD)
```yaml
- id: ssd-random-read
  quantity: "SSD random read latency"
  value: 1.0e-4                     # a number in the unit below
  unit: "s"                         # s | bytes | bytes/s | requests/s | count | ratio
  display: "about 100 microseconds" # always a rounded phrase
  source: {title: "…", url: "…", accessed: "2026-10-14", section: "…"}
  caveat: "Hardware-dependent. Use for order-of-magnitude reasoning only."
```
Every constant used in any HLD lesson, calculator, or exercise comes from this file. Each has a source you opened and a caveat. No constant is invented. Calculator units read values from the exported JSON (Section 9.6), so changing a constant updates every dependent number and every dependent check.

---

## 8. Lesson page: template and section rules

Lesson file: `src/content/docs/{lld|hld}/phase-{n}/{id-dash}-{slug}.mdx`. Required headings, in this order, with this exact text (an optional final `## See also` is allowed for cross-track links):

```mdx
---
title: "L2.1 Strategy"
sidebar:
  order: 15
topic: "L2.1"
---
import { Code } from '@astrojs/starlight/components';
import TopicHeader from '../../../../components/TopicHeader.astro';
import WhatYouNeed from '../../../../components/WhatYouNeed.astro';
import ClaimEvidence from '../../../../components/ClaimEvidence.astro';
import TradeOffTable from '../../../../components/TradeOffTable.astro';
import Cards from '../../../../components/Cards.astro';
import Exercises from '../../../../components/Exercises.tsx';
import Drill from '../../../../components/Drill.tsx';
import LookalikePairs from '../../../../components/LookalikePairs.astro';
import SelfTest from '../../../../components/SelfTest.astro';
import Checkpoint from '../../../../components/Checkpoint.tsx';
import DecisionMapUpdate from '../../../../components/DecisionMapUpdate.astro';

<TopicHeader topic="L2.1" />

## 1. Why this topic exists
## 2. Prerequisites and scope
### What you need
<WhatYouNeed topic="L2.1" />
### What this topic does not cover
## 3. Definitions
## 4. Principles and claims
## 5. Recognition Cards
<Cards topic="L2.1" />
## 6. Reference designs
## 7. Mistake catalogue
## 8. Worked examples
## 9. Exercise ladder
<Exercises topic="L2.1" client:load />
## 10. Recognition drill
<Drill topic="L2.1" client:load />
## 11. Look-alike pairs
<LookalikePairs topic="L2.1" />
## 12. Self-test questions
<SelfTest topic="L2.1" />
## 13. Checkpoint
<Checkpoint topic="L2.1" client:load />
## 14. Decision map update
<DecisionMapUpdate topic="L2.1" />
```
Adjust the relative import depth to the folder depth. `light` topics keep heading 13 with the text "This topic has no checkpoint; its drill items join the phase exam pool."

### 8.1 Section 1: Why this topic exists
- **LLD `measured` topics:** a naive program of at most 40 lines that works, then one realistic change request that hurts it, with the numbers from the pattern unit's `change_cost.sh` output (edit cost) and its `unit.yaml` (blast radius).
- **LLD `standard` and `light` topics:** a naive program of at most 40 lines and its concrete problem, shown by a failing test, a broken invariant, or a class that cannot be tested.
- **HLD:** a prompt-sized load (for example, 3 000 requests per second on 3 TB) with the computed budget showing why the simple single-machine design fails, or holds. If it holds, say so, and say where it stops holding.
- Then one plain paragraph with the key idea. No code or diagram yet.

### 8.2 Section 2: Prerequisites and scope
As `PLAN.md` 6.2: `<WhatYouNeed>` from `uses`; "What this topic does not cover" is the only place later keywords may appear.

### 8.3 Section 3: Definitions
As `PLAN.md` 6.3. LLD definitions include a 3–6 line C# example. HLD definitions include a number or tiny diagram when the term is quantitative ("p99 latency: the value below which 99 of every 100 requests fall").

### 8.4 Section 4: Principles and claims
Every claim is numbered `Claim {topic}.{n}`, has an entry in `claims` (Section 7.2), and uses this layout:
1. **Statement,** precise.
2. **In plain words** (`:::tip[In plain words]`): one or two sentences, no symbols the reader has not met.
3. **A tiny instance with real numbers** before any argument.
4. **Reasoning,** as numbered steps (at most 8, each at most two lines), by kind:
   - `proved`: a proof (rules of `PLAN.md` 6.4). HLD evidence: a `claim-*` unit that checks the statement exhaustively on all small cases. LLD evidence: a solution unit whose tests demonstrate the claim (for example, an unchanged caller compiled against a newly added variant; or, for the Liskov principle, a test that fails when a subtype strengthens a precondition).
   - `computed`: a derivation that shows units on every line. Evidence: a `calc-*` unit.
   - `simulated` (HLD): what is simulated, the seed, the number of runs, and the tolerance. Evidence: a `claim-*` unit with a fixed seed.
   - `measured` (LLD `measured` topics): the two variants and the change scenarios applied to both. Evidence: at least two pattern units with different `domain`s; the tables render from their `measured-*.tsv` files through `<TradeOffTable>`. State what the measurements show and what they do not.
   - `cited`: the source (title, URL, accessed date, section), the claim in your own words, and one sentence on what the source does **not** say. A fact about a real system is never written without a cited claim. Quote at most a few words.
5. **Preconditions box,** exactly:
   ```mdx
   :::note[This claim needs]
   1. …
   :::
   ```
   For `measured` claims, it lists the conditions of the experiment ("the variants are tested separately; each variant is more than one line").
6. **Evidence:** `<ClaimEvidence claim="…" />` shows the unit's code (or table) and its tested output (`expected.txt` or `measured-*.tsv`).
7. **Cost line:** one or two sentences stating the price.

Reading test (Definition of Done): every step must be followable with the track's Phase 0 knowledge plus this page.

### 8.5 Section 5: Recognition Cards
As `PLAN.md` 6.5 (as revised), with the field names of Section 7.2. Also:
- Every LLD card in a `measured` topic has a `trade_off_table` rendered from units; every HLD card with a capacity argument has a `capacity_table` from calc units. Never typed by hand.
- At least one kill signal per card is an **over-engineering** signal with a concrete instance and numbers.
- HLD cards name properties and numbers, never products. LLD cards name forces and symptoms, never frameworks.
- Negative examples include "the simplest design is correct here" instances (`correct_tool: {simplest: …}`).

### 8.6 Section 6: Reference designs
- **LLD:** for each pattern or principle, in order: a class diagram (Mermaid); a sequence diagram of one call; the plain design and then the designed version, both as tested code via `<Code>` imports of the unit files; **How it works** (walk through the names); **C# details explained** (every generic, delegate, LINQ call, `record`, default interface member, attribute, or other non-obvious construct, in plain words, or "None beyond earlier topics"); **Tested** (the commands and result).
- **HLD:** a Mermaid architecture diagram; the read path and the write path as numbered steps; the data model; the capacity table from a calc unit; the failure table (what happens when each component fails, how it is detected, what the user sees).
- Always show the simplest alternative first, then the designed version, then the measured or computed difference.

### 8.7 Section 7: Mistake catalogue
4–8 entries (light topics: 2–3), each `### Mistake: {short name}`:
- **LLD:** the wrong code (a real, compiling copy of the reference with the mistake introduced), its symptom (a failing test, a worse `change_cost.sh` row, or a smell from L0.7), and the fix with one sentence on why. Produce each by writing the wrong version and running it. These wrong versions double as kit mutants where they fit (Section 10.3).
- **HLD:** the failing design plus a small simulation or computation that shows the failure in numbers (for example, 1 000 concurrent cache misses becoming 1 000 database reads, against 1 with request coalescing), as a `claim-*` or `calc-*` unit.
- At least one mistake per lesson is the over-engineered version.
- If a deliberately wrong version passes every test and costs the same, investigate (PLAN.md 8.5): either the tests are weak (strengthen them) or the variant is fine (document it as an alternative, with its reasoning).

### 8.8 Section 8: Worked examples
2 examples (light topics: 1), each an exercise with `role: worked_example`, headed `### Example {n}: {Title}`, then these level-4 headings exactly:
1. `#### Step 1: Numbers` (LLD: the expected-change table. HLD: load, storage, bandwidth, latency budget.)
2. `#### Step 2: Wording → candidate structures` (at least two candidates from allowed topics, one of which is **the simplest thing that could work**)
3. `#### Step 3: Property check → decision` (why each rejected candidate fails or is not worth its cost)
4. `#### Step 4: Design` (diagram; interfaces or API; data model)
5. `#### Step 5: Code or calculation` (a tested unit)
6. `#### Step 6: Decision record` (decision, numbers behind it, two best alternatives, and the change in numbers that would flip it)

Worked examples are the only exercises whose full solutions appear in the lesson.

### 8.9 Section 9: Exercise ladder
One evolving scenario (Section 10.2) of 4–6 rungs (light topics: 3–4), with at least one rung per card. Each rung adds exactly one new force (`new_force`); the first rung is "Base case of the card". At least one rung has `needs_new_structure: false`: the right response is to leave the design alone, and the rung's reference says why, with numbers.

### 8.10 Section 10: Recognition drill
6–8 items of type `recognise` (light topics: 6), from the reserved set (Section 10.8). Quotas, used identically everywhere in this file:
- **"None" quota:** at least 20% of items, rounded up, have `answer.kind: none`.
- **Earlier-card quota:** at least min(3, E) items are answered by a card from an earlier topic, where E is the number of cards in earlier topics of the same track (so the first topic of a track needs none).
Each prompt includes the numbers that matter for recognition.

### 8.11 Section 11: Look-alike pairs
1–3 pairs, as `PLAN.md` 6.11. Both sides within the same or earlier topics of the track. Typical LLD pairs appear in the later topic where the second tool is taught (State versus Strategy lives in L2.3). The first topic of a track may have zero pairs.

### 8.12 Section 12: Self-test questions
4–6 conceptual questions with concrete counterexamples or numbers. At least one asks for the **cost** of the technique and at least one asks when **not** to use it.

### 8.13 Section 13: Checkpoint
One timed exercise from the reserved set (`role: checkpoint`), scored by its checkers. Not present for `light` topics.
| Track and phase | Checkpoint type | Minutes |
|---|---|---|
| LLD L0–L1 | `build` (kit plus `rubric-lld-build-v1`) | 45 |
| LLD L2–L6 | `build` | 60 |
| LLD L7 | `mock` | 90 |
| HLD H0–H3 | `deep_dive` (timed) | 30 |
| HLD H4–H7 | `deep_dive` (timed) | 40 |
| HLD H8 | `mock` (full design) | 45 |
Pass rule: score at least 70% on the rubric, every `critical` criterion scored at least 1 with a one-line evidence note, all kit tests passing where there is a kit, and at least 75% of this topic's drill items correct. Record `checkpointPassedOn`.

### 8.14 Section 14: Decision map update
As `PLAN.md` 6.14. LLD groups are **symptoms** ("a change keeps editing the same function", "an object behaves differently in different states", "I need undo"). HLD groups are **needs with numbers** ("reads above one machine's capacity", "writes above one primary's capacity", "ordering required per entity").

---

## 9. Code, simulations, and measurement

### 9.1 General rules
- Every code unit lives under `code/{topic}/{unit-name}/`. Every expected output or measured table is produced by running the unit and **checked against hand-derived values or independent reasoning before it is committed** (as `PLAN.md` 8.2 requires). Never commit an `expected.txt` or `measured-*.tsv` you have not understood.
- Seeds are fixed and written in the file; simulations print the seed.
- Units use only constructs explained in earlier lessons of the same track; new constructs are explained where first used.
- Comments in code that state a problem use a multi-line block without a leading asterisk on each line.

### 9.2 LLD solution units (C#)
A solution unit is a .NET solution with a library project and an xUnit test project:
```
code/L2.1/caller-unchanged/
├── CallerUnchanged.sln
├── src/CallerUnchanged/CallerUnchanged.csproj        # TargetFramework from design.config.yaml (net10.0); Nullable enable; TreatWarningsAsErrors true
└── tests/CallerUnchanged.Tests/CallerUnchanged.Tests.csproj
```
Rules: one public type per file; no `static` mutable state (except where a mistake-catalogue entry shows why); PascalCase names; interfaces begin with `I`; every language feature beyond earlier lessons explained where first used (`record`, pattern matching, LINQ, `async`, and so on). At least 6 tests per unit, including edge cases and one test per behaviour a mistake-catalogue entry breaks.

**No C# in this plan was compiled** (the workspace used to write it had no .NET SDK). Your first LLD unit must build and pass in CI (PLAN.md 14.1, with `actions/setup-dotnet` pinned to the version in `global.json`). If a snippet here does not compile, fix it; the intent is what counts.

### 9.3 LLD pattern units (the measured comparison)
Required only in `measured` topics: at least two units with different `domain`s, at least one with 3 or more scenarios.

```
code/L2.1/strategy-fee/
├── unit.yaml
├── naive/       {base/, scenarios/01-name.patch, 02-name.patch, …, test.sh}
├── patterned/   {base/, scenarios/…the same file names…, test.sh}
├── measured-naive.tsv
└── measured-patterned.tsv
```
```yaml
# unit.yaml
kind: pattern
domain: parking-fees                  # a measured claim needs units with different domains
variants: [naive, patterned]
claims: ["L2.1.1"]
scenarios:                            # one entry per patch file name
  - name: 01-weekend
    request: "Add a weekend plan at double the hourly rate."
    blast_radius:                     # counted by you, by reading; listed by name so a reviewer can check
      naive: {count: 2, behaviours: ["HOURLY", "DAILY"], where: "FeeCalculator.fee"}
      patterned: {count: 0, behaviours: [], where: "Main (wiring only)"}
```
Definitions used by lessons:
- **Blast radius of a change:** the number of **other** pre-existing, separately tested behaviours whose code sits in the same function or class body as any edited line. The behaviour being changed or added does not count. A composition root or registration list counts 0 if it only constructs and registers objects and contains no behaviour logic; if it contains logic, count the behaviours in it.
- **Overhead:** non-blank lines and files in the base design (the `base` line of the script output).
- **Edit cost:** files modified, added, and deleted; lines added and removed in modified files; lines in new files (script output).

Rules:
1. `base/` is a complete, compiling program. `test.sh <dir>` builds and runs the behaviour tests and exits 0 on success. It must pass on the base and after every scenario, for both variants, with the same assertions.
2. Patches apply cumulatively, in file-name order. Create each patch by editing a working copy and running `git diff`; never write patches by hand.
3. `measured-*.tsv` is the committed output of `change_cost.sh` for that variant. `test_design.sh` regenerates and compares it.
4. At least one scenario is chosen so that the patterned design is **not** better (for example, the first added variant, or a change to the shared signature). The lesson must show it.

### 9.4 `scripts/change_cost.sh` (use exactly; tested)
Applies each scenario patch in order to a copy of `base/`, runs the unit's tests after each step (their output is discarded, and shown only on failure), and prints the measurements. It is language-neutral: the unit's own `test.sh` builds and tests.
```bash
#!/usr/bin/env bash
# Usage: change_cost.sh <variant-dir>
# <variant-dir> contains: base/ (starting code), scenarios/NN-name.patch (applied cumulatively, in name order),
# and test.sh (called as: bash test.sh <work-dir>; must exit 0 on the base and after every scenario).
# Prints only the measurement table on stdout; test output is discarded (it is shown only on failure).
set -euo pipefail
V="${1:?usage: change_cost.sh <variant-dir>}"
V="$(cd "$V" && pwd)"
W="$(mktemp -d)"
LOG="$(mktemp)"
trap 'rm -rf "$W" "$LOG"' EXIT
cp -r "$V/base/." "$W/"
cd "$W"
git init -q .
git config user.email "t@example.com"; git config user.name "t"
git add -A; git commit -qm base
run_tests() {
  if ! bash "$V/test.sh" "$W" > "$LOG" 2>&1; then
    echo "FAIL: tests fail $1" >&2; cat "$LOG" >&2; exit 1
  fi
}
run_tests "on base"
files=$(git ls-files | wc -l)
loc=$(git ls-files -z | xargs -0 awk 'NF { c++ } END { print c + 0 }')
printf "base\tfiles=%s\tnonblank_lines=%s\n" "$files" "$loc"
printf "scenario\tfiles_modified\tfiles_added\tfiles_deleted\tlines_added_in_modified\tlines_removed_in_modified\tlines_in_new_files\n"
for p in "$V"/scenarios/*.patch; do
  git apply --index "$p"
  mod=0; add=0; del=0; la=0; lr=0; ln=0
  while IFS=$'\t' read -r a r path; do
    [ "$a" = "-" ] && { echo "FAIL: binary file in scenario $(basename "$p"): $path" >&2; exit 1; }
    status=$(git diff --cached --no-renames --name-status -- "$path" | cut -f1)
    case "$status" in
      A) add=$((add+1)); ln=$((ln+a)) ;;
      D) del=$((del+1)) ;;
      *) mod=$((mod+1)); la=$((la+a)); lr=$((lr+r)) ;;
    esac
  done < <(git diff --cached --no-renames --numstat)
  git commit -qm "$(basename "$p")"
  run_tests "after $(basename "$p")"
  printf "%s\t%s\t%s\t%s\t%s\t%s\t%s\n" "$(basename "$p" .patch)" "$mod" "$add" "$del" "$la" "$lr" "$ln"
done
```
Output (tab-separated) for the sample unit in Appendix A, patterned variant:
```
base	files=5	nonblank_lines=32
scenario	files_modified	files_added	files_deleted	lines_added_in_modified	lines_removed_in_modified	lines_in_new_files
01-weekend	1	1	0	2	1	5
02-free30	1	0	0	1	0	0
```
Tested on: the Appendix A unit (both variants); a `test.sh` that prints build chatter (excluded from the output); a file without a final newline (counted correctly); a rename (reported as one deletion plus one addition); and a failing `test.sh` (exits non-zero with the test log on standard error).

### 9.5 HLD claim units (`claim-*`)
```
code/H4.2/claim-1/{check.py, expected.txt}
```
- `check.py`: Python 3, standard library only, readable, at most 60 lines, run as `python3 -I check.py`. It checks the claim **exhaustively** over all small cases (kind `proved`) or by **seeded simulation** with a stated tolerance (kind `simulated`), and prints one labelled line per case.
- `expected.txt` is derived by hand from the claim or its proof first (Appendix B shows the pattern), then compared to the program's output. A mismatch means the claim, the proof, or the program is wrong; resolve that before anything else. Never overwrite `expected.txt` with the program's output to make a test pass.
- Simulated numbers must be stable across runs (fixed seed), and the claim states how close is close enough ("within 2 percentage points").

### 9.6 HLD calculator units (`calc-*`)
```
code/H0.2/calc-photo-uploads/{calc.py, expected.txt}
```
- `calc.py` reads constants from `code/_shared/constants.json`, found with `Path(__file__).resolve().parents[2] / "_shared" / "constants.json"` (so it works under `python3 -I`). The JSON is generated from `src/data/constants.yaml` by `scripts/constants_export.mjs`, which `npm run build` runs; the build fails if the committed JSON differs from a fresh export.
- It prints every intermediate quantity with its unit, as `key = value unit` lines, so exercises can reference a value by `key` (Section 7.3).
- Formulas are written as comments. Round only in the final printed value, and say how.

### 9.7 `scripts/test_design.sh` (use exactly; tested)
Runs every `check.py` and `calc.py` unit (standard output must equal `expected.txt`), every pattern unit (regenerated `change_cost.sh` output must equal `measured-*.tsv`), and every C# solution (`dotnet test`).
```bash
#!/usr/bin/env bash
# Usage: test_design.sh [code-root]   (default: code)
# Runs every design code unit under the root:
#   1. claim/calc units: check.py or calc.py; stdout must equal expected.txt exactly
#   2. pattern units (unit.yaml with "kind: pattern"): change_cost.sh stdout must equal measured-<variant>.tsv
#   3. C# solutions (*.sln): dotnet test   (edit this block if lld_language changes; see Section 3)
set -euo pipefail
ROOT="${1:-code}"
HERE="$(cd "$(dirname "$0")" && pwd)"
fail=0

while IFS= read -r f; do
  d="$(dirname "$f")"
  if [ ! -f "$d/expected.txt" ]; then echo "MISSING expected.txt: $d"; fail=1; continue; fi
  if ! python3 -I "$f" | diff -q - "$d/expected.txt" > /dev/null; then echo "FAIL (output differs from expected.txt): $d"; fail=1; fi
done < <(find "$ROOT" \( -name check.py -o -name calc.py \) | sort)

while IFS= read -r y; do
  d="$(dirname "$y")"
  grep -q '^kind: pattern' "$y" || continue
  variants="$(sed -n 's/^variants: \[\(.*\)\]/\1/p' "$y" | tr -d ' ' | tr ',' ' ')"
  [ -n "$variants" ] || { echo "MISSING variants in $y"; fail=1; continue; }
  for v in $variants; do
    out="$(mktemp)"; err="$(mktemp)"
    if ! bash "$HERE/change_cost.sh" "$d/$v" > "$out" 2> "$err"; then echo "FAIL (change_cost): $d/$v"; cat "$err"; fail=1
    elif ! diff -q "$out" "$d/measured-$v.tsv" > /dev/null; then echo "FAIL (measured-$v.tsv is out of date): $d"; fail=1; fi
    rm -f "$out" "$err"
  done
done < <(find "$ROOT" -name unit.yaml | sort)

while IFS= read -r sln; do
  command -v dotnet > /dev/null || { echo "dotnet not installed; cannot test $sln"; fail=1; continue; }
  dotnet test "$sln" --nologo -warnaserror > /dev/null || { echo "FAIL (dotnet test): $sln"; fail=1; }
done < <(find "$ROOT" -name '*.sln' | sort)

[ "$fail" -eq 0 ] && echo "All design code units passed" || exit 1
```

### 9.8 `scripts/exercise_kit_check.sh` (use exactly; tested)
Every LLD exercise kit must prove its tests are real: they fail on the starter, pass on the reference, and fail on every mutant (at least 3, or the number in the kit's `min_mutants` file). This is the design version of the stress test.
```bash
#!/usr/bin/env bash
# Usage: exercise_kit_check.sh [exercises-root] [reference-root] [mutants-root]
# A kit is any folder under <exercises-root> that contains test.sh. Its path relative to the root is <rel>
# (for example L2.1/ex-3, or L2.1/ladder/rung-2 for one rung of a change ladder).
#   <exercises-root>/<rel>/test.sh       run as: bash test.sh <absolute-solution-dir>; exit 0 = all tests pass
#   <exercises-root>/<rel>/starter/      compiling stubs (for rung k > 1: the reference of rung k-1)
#   <exercises-root>/<rel>/min_mutants   optional; a number (default 3)
#   <reference-root>/<rel>/              the reference solution
#   <mutants-root>/<rel>/<name>/         deliberately wrong solutions
# Checks: tests FAIL on the starter, PASS on the reference, and FAIL on every mutant; enough mutants exist.
set -euo pipefail
EX="$(cd "${1:-exercises}" && pwd)"; REF="$(cd "${2:-reference}" && pwd)"
MUT="${3:-reference-mutants}"; mkdir -p "$MUT"; MUT="$(cd "$MUT" && pwd)"
fail=0
while IFS= read -r t; do
  kit="$(dirname "$t")"; rel="${kit#"$EX"/}"
  ref="$REF/$rel"
  [ -d "$kit/starter" ] || { echo "MISSING starter: $rel"; fail=1; continue; }
  [ -d "$ref" ] || { echo "MISSING reference: $rel"; fail=1; continue; }
  if bash "$t" "$kit/starter" > /dev/null 2>&1; then echo "FAIL: tests pass on the starter: $rel"; fail=1; fi
  bash "$t" "$ref" > /dev/null 2>&1 || { echo "FAIL: reference does not pass: $rel"; fail=1; }
  min=3; [ -f "$kit/min_mutants" ] && min="$(tr -dc '0-9' < "$kit/min_mutants")"
  count=0
  for m in "$MUT/$rel"/*/; do
    [ -d "$m" ] || continue
    count=$((count+1))
    if bash "$t" "${m%/}" > /dev/null 2>&1; then echo "FAIL: tests pass on mutant $rel/$(basename "$m") (tests too weak)"; fail=1; fi
  done
  [ "$count" -ge "$min" ] || { echo "FAIL: $count mutants for $rel, need $min"; fail=1; }
done < <(find "$EX" -name test.sh | sort)
[ "$fail" -eq 0 ] && echo "All exercise kits consistent" || exit 1
```
Tested on: a passing kit; a reference that fails; a starter that passes (tests too weak); a mutant that passes; too few mutants; a ladder rung with `min_mutants` set to 1; and a root given with a trailing slash.

**Change ladders:** each rung is its own kit (`exercises/L2.1/ladder/rung-k/`). The starter of rung k is a copy of the reference of rung k − 1, and rung k's tests include all earlier rungs' tests plus the new ones. Because the check requires the tests to fail on the starter, it also proves that every rung adds tested behaviour. Rungs set `min_mutants` to 2.

### 9.9 What is not tested by code, and how it is checked instead
- Diagrams: each Mermaid block must render at build time (Section 12, D10) and is checked against the code by eye in the pipeline's self-review step.
- Facts about real systems (`cited` claims): checked by opening the source (PLAN.md rule 1).
- Rubrics: checked by calibration (Section 10.7).

---

## 10. Exercise bank and reference solutions

Design has no online judge, so the exercises are authored here, and each ships with its own checker.

### 10.1 Types and allowed checkers
| Track | Type | What the learner does | `checkers` (exactly these) |
|---|---|---|---|
| LLD | `recognise` | Reads a requirement set; names the force and the card, or "none" | `[]` (the `answer` is revealed) |
| LLD | `refactor` | Fixes a smelly program (at most 80 lines) without breaking its tests | `[kit]` |
| LLD | `build` | Implements a small system against an interface | `[kit]`, or `[kit, rubric]` when used as a checkpoint |
| LLD | `change_ladder` | One rung of an evolving system | `[kit]` |
| LLD | `mock` | Timed build from a vague prompt | `[kit, rubric]` |
| HLD | `recognise` | Reads a prompt with numbers; names the need and component, or "none" | `[]` |
| HLD | `estimate` | Computes QPS, storage, bandwidth, machines | `[numeric]` (one or more) |
| HLD | `deep_dive` | Designs one subsystem (for example, a rate limiter) | `[rubric]` or `[numeric…, rubric]` |
| HLD | `scale_ladder` | One rung of a prompt scaled up | `[numeric…]`; the last rung adds `rubric` |
| HLD | `failure` | Given a design and a failure, predicts behaviour and the fix | `[rubric]` |
| HLD | `mock` | Timed full design | `[rubric]` or `[numeric…, rubric]` |

### 10.2 Ladders: one evolving scenario
- **Change ladder (LLD).** One system (for example, parking fees) that grows by one requirement per rung. Each rung has a statement, its one `new_force`, and a kit (Section 9.8). The learner commits after each rung (tags `rung-1`, `rung-2`, …) and can run `git diff --numstat rung-1 rung-2` to see his own edit cost. Each rung's reference shows the plain and the patterned approach where they differ, and the ladder's last reference says at which rung the patterned approach started to pay, and why.
- **Scale ladder (HLD).** One prompt (for example, a photo-sharing service). Rung 1 is the smallest honest version (one database, one server). Each later rung multiplies one number by about 10 or adds one constraint (global users, stricter availability, a hot key). Every rung has at least one numeric answer and the **threshold**: the number at which the previous design stops being enough, from a calc unit. Rungs where the previous design is still enough are required (`needs_new_structure: false`).

### 10.3 Exercise kits (LLD)
```
exercises/L2.1/ex-3/
├── README.md        # the prompt (own words) and the public interface contract
├── test.sh          # bash test.sh <absolute-solution-dir>; exit 0 means all tests pass
├── starter/         # compiling stubs that throw NotImplementedException
├── tests/           # xUnit tests, behaviour only, through the public interface
└── min_mutants      # optional; default 3
reference/L2.1/ex-3/                         # reference solution
reference/L2.1/ex-3/wrong-1.md … wrong-3.md  # full wrong answers, for rubric calibration (Section 10.7)
reference-mutants/L2.1/ex-3/{m1,m2,m3}/      # deliberately wrong solutions
```
- `README.md` describes behaviour and the public interface, not the internal design. The learner chooses the design.
- Tests check behaviour only, through the public interface, so any sound design passes. A test that only one design can pass is a bug in the kit.
- `bash scripts/exercise_kit_check.sh` must pass.
- Reference folders are not rendered on the site until the learner records an attempt (Section 11.2). They are in the repository because it is Saurabh's own; he is trusted not to peek.

### 10.4 Reference solutions
Each exercise's reference contains `SOLUTION.md`: the design in 10–25 lines; a Mermaid diagram; the **decision record** (Section 2.4); at least one alternative with *when it is better*; the three most common wrong approaches with why each fails. Plus code (LLD) or `calc`/`claim` units (HLD), tested. Mock references add an "ideal timeline" showing what is done in each time slice.

### 10.5 Clarifying questions
Real design rounds begin with questions. Every `build`, `deep_dive`, `scale_ladder`, and `mock` exercise has a `clarifying` list of at least 4 entries, at least 2 marked `critical: true` (the design changes with the answer). On the site, the learner first types his own questions, then reveals the list, then ticks the critical ones he asked. The count feeds the rubric criterion "asked the questions that change the design".

### 10.6 Sources
- **LLD:** the Gang of Four book (cite by pattern name and intent), Fowler's refactoring catalogue, the C# and .NET documentation, and the Liskov and Liskov–Wing papers for the substitution principle. Open each before citing.
- **HLD:** primary sources for facts about real systems. Candidate anchors, **to be verified** (open each; record the exact title, URL, and `accessed` date; drop any you cannot open): Dynamo (Amazon, 2007); Bigtable (Google, 2006); the Google File System (2003); MapReduce (2004); Spanner (2012); the Raft paper (2014); the Kafka paper (2011); "Scaling Memcache at Facebook" (2013); TAO (2013); Lamport, "Time, Clocks, and the Ordering of Events" (1978); Karger et al. on consistent hashing (1997); Flajolet et al. on HyperLogLog (2007); Shapiro et al. on CRDTs (2011); the Google SRE book; and the documentation of any real system a lesson names.
- Never copy figures. Never state a number about a real product from memory.
- Common interview prompts (URL shortener, news feed, parking lot) are common knowledge; write every prompt in your own words. `inspired_by` is optional and is a link, never copied text.

### 10.7 Rubrics
`src/data/rubrics.yaml` defines exactly these rubrics (extend only with Saurabh's approval):

| id | Used by | Criteria (weight; ★ = critical) |
|---|---|---|
| `rubric-lld-build-v1` | LLD `build` checkpoints, `mock` | requirements and assumptions (10); entities and responsibilities (20 ★); extensibility under the stated changes (20 ★); correctness: kit tests pass (20 ★); pattern use justified, no over-engineering (10); concurrency or state safety (10; ★ only when the prompt involves concurrency); readability (10) |
| `rubric-hld-mock-v1` | HLD `mock` | requirements and scope (10); estimation (15 ★); API and data model (15); high-level design (20 ★); deep dive (20 ★); bottlenecks and failure (10); trade-offs and decision record (10) |
| `rubric-hld-deep-dive-v1` | HLD `deep_dive`, last `scale_ladder` rung | requirements and the critical questions (15); numbers (20 ★); mechanism and data (30 ★); failure behaviour (20 ★); trade-offs and decision record (15) |
| `rubric-hld-failure-v1` | HLD `failure` | correct prediction of behaviour (40 ★); detection (20); mitigation with its cost (40 ★) |

```yaml
- id: rubric-hld-mock-v1
  criteria:
    - id: estimation
      name: "Estimation"
      weight: 15
      critical: true
      anchors:
        0: "No numbers, or numbers more than 10x from the reference, or no working shown"
        1: "Working shown; key numbers within 10x of the reference"
        2: "Working shown; key numbers within 3x of the reference; the numbers are used to choose components"
    # … every criterion has anchors 0, 1, 2 describing observable evidence
```
Rules:
- Weights sum to 100. Anchors describe **observable evidence** (something that can be pointed at in the learner's work), never "good" or "bad".
- Score = Σ weight × (score ÷ 2). The learner records a one-line evidence note for every criterion; notes are required on critical criteria for a pass.
- **Numeric checkers** use `factor` (default 2): an answer passes if answer ÷ reference is between 1/factor and factor. Single-number estimate exercises use factor 2; rubric estimation anchors use 3 and 10 because a full design involves several numbers.
- **Calibration** (before a rubric is first used by an exercise): score the exercise's reference and its three full wrong answers (`wrong-1.md` … `wrong-3.md`, each a complete answer, not a one-liner). The reference must score at least 90% and each wrong answer below 60%. If your environment allows starting a separate agent, have it score them seeing only the rubric and the answers; otherwise record `calibration: self` in `notes/design/{topic}.md`, and Saurabh spot-checks one calibrated exercise per phase at the phase gate.
- **Export for review** (Section 11.2) lets Saurabh paste his answer and rubric into a Claude conversation for a second reading. It is an option, not a gate.

### 10.8 Practice and reserved sets
As in `PROBLEM_BANK_PLAN.md`: the **practice set** (`role: ladder | worked_example`) is visible; the **reserved set** (`drill | checkpoint | review | exam`) must stay unseen until used, because a drill or mock already seen tests memory, not recognition. Reserved items are not written into any page's HTML: the build emits them to `/data/reserved/{topic}.json`, and only the Drill, Checkpoint, Review, and Exam components fetch them, on demand. Reviews use **transfer prompts**: a different domain from the topic's own examples, needing the same card.

### 10.9 Counts per topic
| Item | `measured` / `standard` | `light` |
|---|---|---|
| Cards | 1–4 | 1–2 |
| Ladder (one evolving scenario) | 4–6 rungs, ≥ 1 per card | 3–4 rungs |
| Worked examples | 2 | 1 |
| Recognition drill | 6–8 | 6 |
| Checkpoint | 1 | none |
| Review sets | 2 (each 3 items: ≥ 1 recognise, ≥ 1 short design or estimate) | 1 |
| Self-test | 4–6 | 3–4 |
| Look-alike pairs | 1–3 (0 allowed for a track's first topic) | 0–2 |
| Phase exam | 6–8 items per phase, mixed, topics hidden | |

Expected total across both tracks: about 1 900 items, of which about two thirds are short recognition or estimate items (at most 100 words each). Record the actual totals in the D0 inventory.

### 10.10 Exercise inventory (milestone D0)
Before any lesson is written, produce `src/data/exercises/INVENTORY.yaml` and a readable `notes/design/INVENTORY.md`. For every topic: the planned card ids and names; the ladder scenario's title and rung list (each rung's `new_force` and `needs_new_structure`); one-line stubs for drill items (intended card, as `{topic, card}`, or "none"); the checkpoint title and type; review stubs. No solutions, kits, or sources yet. Checks (run by a script): every card named in a stub is planned in the same or an earlier topic of the same track; every topic meets the quotas of Section 8.10; no ladder scenario is reused within a track. This is Saurabh's chance to see the whole road ahead (gate in Section 14).

---

## 11. Site additions

Everything inherits `PLAN.md` Section 10 (storage module, try/catch rule, look and feel).

### 11.1 Navigation
The sidebar adds two groups after the CP phases: **LLD** (Phases L0–L7; each phase: intro, lessons, exam) and **HLD** (Phases H0–H8). The dashboard gains a track filter and shows the current topic **per track**, due reviews across tracks, and the three cards with the most recognition misses. `cp:v1:settings` becomes `{ currentTopic: { cp, lld, hld } }`; migrate the old shape when reading it.

### 11.2 Exercise page and components
- `Exercises` (the ladder list) links to one page per exercise, which shows:
  - The prompt and the **Ask first** box (Section 10.5).
  - A timer: optional for ladders; required for checkpoints, exams, and mocks. Timed rounds show phases as shares of the total: HLD full design: requirements 10%, estimation 10%, API and data 20%, high-level design 25%, deep dive 25%, bottlenecks 10%. HLD deep dive: requirements 15%, mechanism 60%, failure and trade-offs 25%. LLD build or mock: clarify 10%, entities and interfaces 20%, code 55%, extend and test 15%.
  - Three hints (practice set only), one at a time, with the struggle-budget reminder (20 minutes in L0–L1 and H0–H1; 30 minutes after).
  - An answer area (text, saved locally) and **rubric scoring** where the exercise has a rubric: each criterion with its anchors, a score selector, and an evidence field.
  - **Reference reveal**, available only after an attempt is saved.
  - An attempt log: date, minutes, score, hints opened, mistake category (*Missed a requirement*, *Wrong structure*, *Over-engineered*, *Under-engineered*, *Numbers wrong*, *Missed a failure case*, *Concurrency or state bug*, *Implementation bug*), and a note.
  - **Export for review:** copies a Markdown block (prompt, rubric, his answer, his scores and evidence) to the clipboard, with the fallback of PLAN.md 14.2.
- `Drill` accepts "none" as an answer and requires a one-sentence property or force before the reveal.
- Storage: `cp:v1:design-attempts` = `{ [globalExerciseId]: [ { date, minutes, hints, scores: { [criterionId]: { score, evidence } }, mistake, note } ] }` (keys like `L2.1/ex-3`); `cp:v1:numbers` for flashcards. Both are included in export and import.

### 11.3 Numeric answers
For `estimate` exercises and scale-ladder rungs: an input for the number and a free-text unit. The site checks the number with the exercise's `factor` (Section 10.7), then shows the reference derivation and both numbers.

### 11.4 Number flashcards (HLD)
Built from `constants.yaml`: the front shows the quantity; the learner places a guess on a log-scale slider; the back shows the value, source, and caveat. A guess within one order of magnitude counts as correct. Spaced repetition: 1, 3, 7, 21 days.

### 11.5 Handbooks
- **LLD Pattern Handbook** (`/lld/handbook`): by symptom (from decision maps), by topic, an "as of topic X" filter, and flashcards (front: a requirement set; back: card, force, cost, kill signal).
- **HLD Component Handbook** (`/hld/handbook`): by need and number, by topic, "as of topic X", flashcards.
- **Numbers sheet** (`/hld/numbers`): every constant with source and caveat, plus the formulas used in lessons.

### 11.6 Reviews
Same schedule as PLAN.md 10.4 (3 and 14 days after `checkpointPassedOn` for the two review sets; light topics: one set at 14 days). Reviews show transfer prompts and use the rubric self-score for the design item.

---

## 12. Build-time validation

Additions to `PLAN.md` Section 12. Each failure names the file and id.

- **D1. Schemas.** Topic, exercise, rubric, constants, inventory, and `unit.yaml` files match their schemas (Sections 7 and 9.3).
- **D2. Counts.** As Section 10.9, by topic `kind`. Claims: at least one per card, and every card's `from_claim` exists in `claims`. `clarifying`: at least 4 entries, at least 2 critical, on every `build`, `deep_dive`, `scale_ladder`, and `mock` exercise.
- **D3. Order and quotas.** Every `{topic, card}` reference, `techniques`, `uses`, and `requires` entry resolves within the same track and has `order` ≤ the current topic's. Drill quotas of Section 8.10 hold. Ladders: each rung has exactly one `new_force`; at least one rung has `needs_new_structure: false`.
- **D4. `uses` completeness.** As `PLAN.md` Section 12 item 10.
- **D5. Evidence.** Each claim's `evidence` units exist and have the right kind: `proved` (HLD) and `simulated` → a `claim-*` unit; `proved` (LLD) → a solution unit with tests; `computed` → a `calc-*` unit; `measured` → at least two pattern units (`unit.yaml` with `kind: pattern`) with different `domain`s, each with `measured-*.tsv`; `cited` → `source` with `title`, `url`, `accessed` (`YYYY-MM-DD`), and `section`. Every `measured` topic has at least one `measured` claim; no `standard` or `light` topic needs one.
- **D6. Constants.** Every constant id referenced anywhere exists in `constants.yaml` with a source; `code/_shared/constants.json` equals a fresh export.
- **D7. Checkers.** Each exercise's `checkers` list is exactly one of the combinations allowed for its type (Section 10.1). Every `numeric` checker's `calc` unit exists and prints a line with its `key`. Every `kit` path exists under `exercises/` and `reference/`. Every `rubric` id exists in `rubrics.yaml`.
- **D8. Quotes.** In MDX prose, no blockquote and no text in quotation marks attributed to a source is longer than 15 words. (YAML prompts are the course's own words and are not checked by this rule.)
- **D9. No products in cards.** HLD card text (every field) contains no name from `src/data/product-names.yaml` (a list you create: common database, queue, cache, search, and cloud product names). Lessons may name products only inside `:::example[Real systems]` blocks that contain a cited claim.
- **D10. Diagrams.** Every Mermaid block renders at build time with a renderer that needs no network at runtime (pin a version at least two weeks old; no runtime CDN scripts).
- **D11. Keywords.** Run the keyword search of PLAN.md Section 4 per track. `scripts/keyword_collisions.mjs` (run in D0 and in the build) fails if any keyword of a topic appears inside a keyword of an earlier topic of the same track, or inside any required heading of the Section 8 template.
- **D12. Rubrics.** Weights sum to 100; at least one critical criterion; anchors 0, 1, 2 exist for every criterion.
- **D13. Headings.** Lesson headings match Section 8 exactly, in order; an optional final `## See also` is the only extra level-2 heading allowed.
- **D14. Reserved items stay out of HTML.** The built HTML of every page contains none of the ids or titles of reserved exercises; they exist only in `/data/reserved/*.json`.

---

## 13. Per-topic pipeline

Run in order. After each step, update `PROGRESS.md` and commit (format of PLAN.md 14.0, e.g., `topic(L2.1): step 4 reference designs`).

1. **Scope.** Branch, lesson from the template, data file, exercise file, `notes/design/{topic}.md`, code folders. Record in `PROGRESS.md`: allowed topics, new terms, forbidden keywords, glossary already defined, planned cards (from the inventory).
2. **Principles and claims.** Lesson Sections 1–4. Fill `uses` and `claims`. Write every evidence unit first, derive its expected output by hand or independent reasoning, then run it. `measured` topics: build both pattern units now.
3. **Recognition Cards.** Force or need, property, how to test, shapes with arithmetic, weak signals as form plus shape, kill signals (including over-engineering), `in_action`, trade-off or capacity tables (from units), positive and negative examples (inline numbers from units).
4. **Reference designs.** Lesson Section 6: diagrams, tested code, capacity and failure tables.
5. **Mistake catalogue.** Write the wrong versions, run them, record the symptoms; reuse suitable ones as kit mutants.
6. **Exercises.** From the inventory: prompts, clarifying lists, kits, references, full wrong answers, mutants, numeric answers, sources (open each). Run `exercise_kit_check.sh` and `test_design.sh`. Calibrate rubrics (Section 10.7). Revise card signals from what the prompts looked like.
7. **Worked examples.** Lesson Section 8, six-step format, tested units.
8. **Drill, look-alikes, self-test, checkpoint, reviews.** Fill the data files.
9. **Decision map.** Add entries; check the handbook renders them in the right groups.
10. **Self-review and merge.** `npm run build`, `bash scripts/test_design.sh code`, and `bash scripts/exercise_kit_check.sh` pass; keyword search clean; read the lesson as a beginner would; **honesty check** (for every card, point to where the lesson shows the technique costing more than it saves); reading test of Section 8.4; merge; tag `topic-{id}`.

---

## 14. Milestones and review gates

Every block below includes the phase intros and phase exams for the phases it completes.

| Milestone | Work | Gate |
|---|---|---|
| **D0** | Infrastructure: curriculum rows (99 topics), schemas, components (Section 11), the three scripts of Section 9 (copied exactly and run on a synthetic example before first use), `constants_export.mjs`, `keyword_collisions.mjs`, CI (pinned .NET SDK and Python), `product-names.yaml`, Mermaid rendering, `rubrics.yaml`, `design.config.yaml`, `global.json`. Then the **exercise inventory** for all 99 topics (Section 10.10). | ⏸ "D0 review" → `waiting`; continue on `approved`. At this gate Saurabh also confirms `lld_language` and may change the order of blocks below. |
| **DL1** | **L2.1 Strategy as the LLD exemplar**, all 10 steps; earlier topics appear as "coming soon" links. | ⏸ |
| **DH1** | **H4.2 Quorums as the HLD exemplar**, all 10 steps. | ⏸ |
| **L-A** | L0.1–L0.8 | ⏸ |
| **H-A** | H0.1–H0.7 | ⏸ |
| **L-B** | L1.1–L1.6 | ⏸ |
| **H-B** | H1.1–H1.5 | ⏸ |
| **L-C** | L2.2–L2.5, then revise L2.1 to match L0–L1 (links, terms, claims) | ⏸ |
| **H-C** | H2.1–H2.5, H3.1–H3.5 | ⏸ |
| **L-D** | L3, L4 | ⏸ |
| **H-D** | H4.1, H4.3–H4.5, then revise H4.2 to match H2–H4.1 | ⏸ |
| **L-E** | L5, L6 | ⏸ |
| **H-E** | H5, H6 | ⏸ |
| **L-F** | L7.1–L7.7 | ⏸ |
| **H-F** | H7, H8.1–H8.10 | ⏸ Final review |

The default order alternates LLD and HLD blocks. The PLAN.md pacing rule applies per track.

---

## 15. Progress and feedback

- `PROGRESS.md` (PLAN.md 16.1) gets two lines under "Saurabh is studying" (`LLD topic`, `HLD topic`) and the new gates.
- `FEEDBACK.md` types add: `wrong number | unrealistic scenario | rubric unfair | pattern misapplied | kit test too strict`. Handling: **wrong number**: recompute from the calc unit, fix constants if needed, rerun everything that depends on them. **Rubric unfair**: adjust anchors and recalibrate (Section 10.7); do not rescore past attempts. **Kit test too strict**: a test that only one design passes is a bug; fix it and rerun `exercise_kit_check.sh`.
- Repeated misses on one card mean: rewrite that card's signals, kill signals, and examples, and add drill items for it.

---

## 16. Definition of Done

### 16.1 Topic
- [ ] `npm run build`, `bash scripts/test_design.sh code`, and `bash scripts/exercise_kit_check.sh` pass.
- [ ] All 14 lesson sections complete; claims follow Section 8.4 with evidence of the right kind; `measured` topics have two pattern units from different domains, including a scenario where the pattern is not better.
- [ ] Every card: shapes with arithmetic, signals as form plus shape, `in_action`, a trade-off or capacity table from units (where applicable), ≥ 2 positive and ≥ 2 negative examples, an over-engineering kill signal with numbers; look-alikes by card name; HLD cards contain no product names.
- [ ] Mistake catalogue includes the over-engineered version; every wrong version was actually run.
- [ ] Ladder: one new force per rung, at least one "no new structure" rung. Drill: quotas of Section 8.10.
- [ ] Every exercise has an allowed checker combination; kits pass the kit check; numeric answers come from calc units; rubrics calibrated; every cited source was opened (`accessed` set).
- [ ] No later-topic reference outside "does not cover"; header "Builds on" and "What you need" identical.
- [ ] Every abbreviation expanded on first use on the page; every term defined before use; every C# or Python construct explained in plain words.
- [ ] Hints, timers, rubric scoring, reveal gating, export, and review dates work in the browser (desktop and a narrow mobile width).
- [ ] Honesty check and reading test done; `PROGRESS.md` updated; merged and tagged.

### 16.2 Phase
- [ ] All topics done; phase intro and exam (6–8 mixed items, topics hidden, remediation map) complete.
- [ ] "Coming soon" links resolved; tagged `phase-L{n}` or `phase-H{n}`; gate set to `waiting`.

---

## 17. Failure handling

| Situation | Action |
|---|---|
| A pattern unit shows the patterned design is not better | Keep it. It is a finding: the lesson says when the pattern does not pay, with the numbers. Do not tune scenarios to favour the pattern; add a scenario that favours it only if it is a realistic change request. |
| Only one domain fits a `measured` claim | Change the topic's claim to `proved` or an illustrated example, say in the lesson that the measurement is a single example, and change the topic's `kind` to `standard` in `curriculum.yaml` with a note in `PROGRESS.md`. |
| A claim check disagrees with the hand-derived expected output | Treat it as an error in the claim, the proof, or the program. Resolve it before anything else. |
| A constant cannot be sourced | Do not use it. Use a stated assumption labelled as one ("assume 1 ms"), or drop the example. |
| A source cannot be opened | Drop the claim or the source; note it under "Blocked". |
| Kit tests pass a mutant | The tests are too weak: add a test that fails on the mutant. Never delete the mutant. |
| Kit tests fail a valid alternative design | The tests depend on internal structure: rewrite them against the public interface. |
| A rubric reference scores below 90%, or a wrong answer scores 60% or more | Rewrite the anchors and recalibrate. |
| .NET or Python missing in your environment | Install it (CI: setup actions; locally: README). If impossible, stop code work for that track, note it under "Blocked", and continue only with prose that does not depend on running code. Never ship untested code. |
| A look-alike or kill signal needs a later topic | Describe the condition without naming the later tool, or move the pair to the later topic's lesson. |
| A prompt closely resembles a copyrighted exam or book exercise | Rewrite it in a different domain with different numbers. |

---

## Appendix A: sample LLD Recognition Card (Strategy), with measured numbers

The numbers below were measured by running `change_cost.sh` on an equivalent **Java** implementation of the pricing example, because the workspace used to write this plan had no .NET SDK. The C# pattern unit must be re-measured, and its numbers replace these; expect the same shape, not identical line counts. This is one domain; the lesson needs a second (Section 9.3).

**Base designs** (same behaviour: hourly plan at 20 per started hour, daily plan at 100 per started day).

| Design | Files | Non-blank lines |
|---|---|---|
| Plain: one `FeeCalculator` with a `switch` on the plan name | 2 | 18 |
| Strategy: interface, two plan classes, calculator with a lookup table, wiring in `Main` | 5 | 32 |

Overhead of Strategy for two plans: **+3 files, +14 lines.**

**Change scenarios**, applied in order to both designs; the tests pass after each.

| Scenario | Design | Files modified / added | Lines added / removed in modified files | Lines in new files | Blast radius (other behaviours in an edited function or class) |
|---|---|---|---|---|---|
| 1. Add a weekend plan (double hourly) | Plain | 1 / 0 | 2 / 0 | 0 | 2: HOURLY and DAILY share `FeeCalculator.fee` |
| 1. Add a weekend plan | Strategy | 1 / 1 | 2 / 1 | 5 | 0: the modified file (`Main`) is wiring only |
| 2. First 30 minutes free on hourly | Plain | 1 / 0 | 1 / 0 | 0 | 2: DAILY and WEEKEND share `FeeCalculator.fee` |
| 2. First 30 minutes free on hourly | Strategy | 1 / 0 | 1 / 0 | 0 | 0: only `HourlyPricing` changes |

**What the numbers say.**
- In **lines**, the plain design wins here: 3 lines for both scenarios, against 9 for Strategy (scenario 1: 3 lines changed in wiring plus 5 in the new class; scenario 2: 1 line).
- In **blast radius**, Strategy wins: every edit to the plain design sits in a function that holds every other plan, so each edit can break plans nobody meant to touch (2 others here, growing by one per plan added). Strategy keeps each edit inside one class.
- There is no single break-even number, because lines and behaviours-at-risk are different units. Strategy pays when plans are added or changed **repeatedly** and are **tested or owned separately**. For two plans that will never change, it costs 14 lines and 3 files for nothing.

```yaml
- id: strategy
  name: "Strategy"
  force: "Behaviour that varies independently of the code that uses it, with variants added or changed over time."
  decisive_property: "All variants fit one method signature, and callers do not need to know which one runs."
  from_claim: "L2.1.2"
  how_to_test: "List the variants and write the one signature they could all share. If the inputs differ per variant, the property does not hold yet."
  trade_off_table:
    units: ["L2.1/strategy-fee", "L2.1/strategy-notify"]
    overhead: "+3 files and +14 non-blank lines for two plans (fee unit, measured)."
    per_change: "About 8 lines touched per added plan, against 2 for a switch case (fee unit)."
    blast_radius: "Switch: grows by one other behaviour per plan added. Strategy: 0 for plan logic."
    verdict: "No single break-even: Strategy costs lines and buys isolation. It pays when plans change repeatedly and are tested or owned separately."
  constraint_shapes:
    - "3 or more variants now, or 2 variants plus a stated expectation of more; each variant longer than one or two lines"
  weak_signals:
    - form: "The prompt says 'support different' pricing, payment, discount, routing, or sorting rules"
      shape: "At least 3 named kinds, or 'new kinds will be added', and the kinds differ in a calculation or decision, not only in stored data"
    - form: "The prompt says 'depending on the type, plan, or mode, calculate…'"
      shape: "The chosen kind can change per request or per customer"
  kill_signals:
    - "Two variants, no expected change, one line each: a plain conditional is 14 lines shorter (measured)"
    - "Variants differ in the data they carry (a car has a plate, a truck has a weight), not in what they do: use fields or subtypes"
    - "Each variant needs different inputs: there is no shared signature yet, so fix that first"
  in_action:
    statement: "A parking system charges by an hourly or a daily plan; marketing says weekend plans and promotions will follow."
    constraints: "2 plans now, at least 2 more planned this quarter, each plan tested separately by the finance team"
    budget: "At least 4 expected edits to pricing per year. In a shared switch, each edit touches a function that holds every plan."
    candidates:
      - {tool: "Plain conditional (switch on plan name)", verdict: rejected, because: "Blast radius grows with each plan; every edit puts the other plans at risk."}
      - {tool: "Strategy", verdict: chosen, because: "The property holds: every plan is fee(minutes) returning an amount."}
    property_check: "Write the signature: long Fee(long minutes). Hourly, daily, and weekend all fit it. Yes."
    decision: "Strategy, with a lookup table keyed by plan name, filled in the composition root."
  examples:
    positive:
      - inline: {input: "Plans: hourly, daily, weekend, free-first-30-minutes; each tested alone; more promised", answer: "Strategy", why: "All fit Fee(minutes); plans are added and changed often and tested separately."}
      - inline: {input: "Notification channels: email, SMS, push, each with its own sending logic; channels get added", answer: "Strategy", why: "All fit Send(message); each channel is added, replaced, and tested on its own."}
    negative:
      - inline: {input: "Two plans (hourly, daily) fixed by regulation; no change expected", answer: "Plain conditional", why: "Strategy adds 3 files and 14 lines and saves nothing when nothing changes."}
        correct_tool: {simplest: "plain conditional"}
      - inline: {input: "Vehicle kinds differ only in the data they carry (plate, weight)", answer: "Fields or subtypes", why: "No behaviour differs, so there is nothing to put behind a shared signature."}
        correct_tool: {topic: "L0.3", card: subtype-per-variant}
  lookalikes:
    - description: "One subclass per variant (inheritance, from L0.3)"
      tool: {topic: "L0.3", card: subtype-per-variant}
      flipping_difference: "Subclasses fix the variant when the object is created; Strategy lets the caller choose or change it at run time and keeps variants separate from the class that uses them."
  cost: "Time: one extra method call per use. Code: see trade_off_table."
```

## Appendix B: sample HLD Recognition Card (replication quorum), with checked numbers

Checked by running code in the workspace used to write this plan: for every replica count N from 1 to 5 and every write quorum W and read quorum R from 1 to N, a write set and a read set always intersect exactly when W + R > N (exhaustive check, no mismatches). The availability numbers come from the binomial formula below and were recomputed by script.

**Claim H4.2.1 (proved).** Suppose a write to a key is acknowledged after W of that key's N replicas have stored it durably, and a read of the key that **starts after the acknowledgement** contacts R of the same N replicas. If W + R > N, at least one replica the read contacts holds that write.
*In plain words:* if the group that confirmed the write and the group that answers the read together have more members than the whole replica set, they must share a member, and that member has the write.
*Tiny instance:* N = 3, W = 2, R = 2. The write reached {A, B}. Any 2 of {A, B, C} that a read picks ({A, B}, {A, C}, or {B, C}) includes A or B.
*Proof:* (1) The write set has W members. (2) The read set has R members. (3) If they shared no member, they would need W + R different replicas. (4) Only N exist, and W + R > N, so that is impossible. (5) So some replica is in both sets. (6) It stored the write before the acknowledgement, and the read started later, so it holds the write when the read asks.
:::note[This claim needs]
1. A fixed set of N replicas for the key, the same for the write and the read.
2. A write is acknowledged only after W replicas have stored it durably.
3. The read starts after the write was acknowledged.
4. No replica outside the set stands in for a missing one (this rules out sloppy quorums).
:::
**What the claim does not give.** It says a contacted replica *holds* the write. Returning it also needs the read to pick the newest of the R replies, which requires versions that are totally ordered per key (for example, assigned by one coordinator for that key). Timestamps from different machines' clocks do not guarantee this (H4.1). It also says nothing about writes still in flight when the read runs, or about a write that reached fewer than W replicas and failed: one read may see it and a later read may not. Topics after this one deal with those cases.

The tested unit (`check.py`, run with `python3 -I`, and its `expected.txt`, derived from the proof before running):
```python
import itertools
for n in range(1, 6):
    bad = 0
    for w in range(1, n + 1):
        for r in range(1, n + 1):
            ok = all(set(a) & set(b) for a in itertools.combinations(range(n), w)
                     for b in itertools.combinations(range(n), r))
            if ok != (w + r > n):
                bad += 1
    print(f"N={n}: mismatches with W+R>N rule = {bad}")
```
```
N=1: mismatches with W+R>N rule = 0
N=2: mismatches with W+R>N rule = 0
N=3: mismatches with W+R>N rule = 0
N=4: mismatches with W+R>N rule = 0
N=5: mismatches with W+R>N rule = 0
```

**Availability (computed).** Each replica is up with probability 0.999, independently. The probability that at least k of n are up is the sum of C(n, i) × 0.999^i × 0.001^(n−i) for i from k to n.
| Setup | Probability an operation can proceed | Expected downtime per 30-day month |
|---|---|---|
| 1 machine | 0.999 | 43.2 minutes |
| N = 3, W = R = 2 (needs 2 of 3) | 0.999997 | about 0.13 minutes (8 seconds) |
| N = 5, W = R = 3 (needs 3 of 5) | 0.99999999 | about 0.0004 minutes (0.03 seconds) |

Independence is an assumption: machines in the same rack or zone fail together. The lesson states this, and a kill signal covers it.

```yaml
- id: quorum-replication
  name: "Quorum replication"
  need: "Acknowledged writes must survive machine failures and be visible to reads that start after the acknowledgement, while reads and writes keep working with a minority of replicas down."
  decisive_property: "W + R > N over a fixed replica set; writes acknowledged after W durable copies; reads start after the write's acknowledgement and return the newest of R replies by a per-key total order of versions; no substitute replicas."
  from_claim: "H4.2.1"
  how_to_test: "Write down N, W, and R and check W + R > N. Then check the four conditions in the claim's box, and how versions are ordered."
  capacity_table:
    units: ["H4.2/calc-quorum-table"]
    threshold: "Needed when the availability target exceeds what one machine gives: 0.999 is 43.2 minutes down per month."
    price: "Each write waits for the W-th fastest of N replies and each read for the R-th fastest. N = 3, W = R = 2 survives 1 failure for both."
  constraint_shapes:
    - "Availability target of 99.99% or more (at most about 4.3 minutes down per month) for single-key reads and writes"
  weak_signals:
    - form: "The prompt says 'no single point of failure' and 'a read after a successful write must see it'"
      shape: "Operations touch one key at a time; the write rate fits within one replica group"
    - form: "The prompt says 'keep working when one data centre zone is down'"
      shape: "Three or more zones; single-key operations"
  kill_signals:
    - "Operations must change several keys together: quorums give per-key guarantees only"
    - "Every read must agree on one order of writes even while writes are in flight: W + R > N alone does not give that"
    - "One primary with synchronous replication already meets the availability target and its failover time is acceptable: that is simpler"
    - "Replicas share a failure domain (one rack or zone): the independence behind the availability table is false"
  in_action:
    statement: "Store user session records. An acknowledged write must not be lost; a machine may die at any time; reads are 5 times as frequent as writes."
    constraints: "20 000 writes per second, 100 000 reads per second, three zones, 99.999% availability for single-key operations; the store gives each write of a key a version number larger than every earlier one (stated assumption)"
    budget: "One machine gives 0.999 (43.2 minutes down per month). 99.999% allows about 0.43 minutes per month."
    candidates:
      - {tool: "Single machine", verdict: rejected, because: "0.999 is below the target."}
      - {tool: "Quorum replication, N = 3, W = 2, R = 2", verdict: chosen, because: "0.999997 by the table, above 0.99999; W + R = 4 > 3."}
    property_check: "Fixed set of 3 replicas, one per zone; writes acknowledged after 2 durable copies; reads take the newest of 2 replies by the per-key version number; no substitute replicas. All conditions hold."
    decision: "N = 3, W = 2, R = 2, one replica per zone."
  examples:
    positive:
      - inline: {input: "N = 3, W = 2, R = 2", answer: "Every read set meets every write set", why: "W + R = 4 > 3."}
      - inline: {input: "N = 5, W = 3, R = 3", answer: "Every read set meets every write set, and 2 failures are tolerated", why: "W + R = 6 > 5; 3 of 5 still form both quorums."}
    negative:
      - inline: {input: "N = 3, W = 1, R = 1 (fast, 'eventually consistent')", answer: "A read can miss the write", why: "W + R = 2 is not greater than 3: a write that reached {A} and a read that asks {B} share nothing."}
        correct_tool: {topic: "H2.3", card: leader-follower-replication}
      - inline: {input: "Two keys must be updated together; N = 3, W = 2, R = 2", answer: "Quorums do not make the pair atomic", why: "The guarantee is per key; a read can see one key updated and the other not."}
        correct_tool: {topic: "H1.3", card: transaction-isolation}
  lookalikes:
    - description: "Leader–follower replication with asynchronous followers"
      tool: {topic: "H2.3", card: leader-follower-replication}
      flipping_difference: "Follower reads can lag the leader, and writes stop while a failed leader is replaced; quorum reads and writes continue with a minority of replicas down, but need W + R > N for reads to meet writes."
  cost: "Write latency is set by the W-th fastest of N replies, read latency by the R-th fastest. A smaller W lowers write latency and raises the chance that a read misses the write unless R grows to match."
```
