# DESIGN_TRACKS_PLAN.md: Low Level Design (LLD) in C++23 and High Level Design (HLD) in Go

**Audience:** the same autonomous coding agent that follows `PLAN.md`, in the same repository.
**Learner:** Saurabh, a working backend engineer preparing for design rounds at product-based companies and for deeper systems work. He has production experience but little formal practice in design interviews and little formal vocabulary for design trade-offs.
**What this adds:** two new tracks on the existing site, built the same way as the competitive-programming (CP) programme in `PLAN.md`: strict dependency order, one idea at a time, recognition first, everything checkable checked by code.

- **LLD track** (low level design), **in C++23**: designing the classes, interfaces, ownership, and object interactions of one program. Interview names: "machine coding", "object-oriented design".
- **HLD track** (high level design, also called system design), **in Go, and practical**: every topic is learned by *building* the mechanism as a running Go program, breaking it on purpose (killed nodes, cut links, overload), and measuring what happens. Interview-style estimation and design rounds remain, but they sit on top of things Saurabh has built and run.

Read this whole file, then `PLAN.md` Sections 0, 2, 4, 5, 6, 7, 8, 10, 12, 14, 16, and 17 (as revised by its Revision 2). If you believe something here is wrong, write the concern in `PROGRESS.md` under "Questions for Saurabh" and continue with work that doesn't depend on it.

**Revision 3.** LLD code is now C++20 (it was C#), and HLD code is now Go (it was Python). HLD was made practical: each topic has a Go lab with tests on a deterministic simulated network, real multi-process runs with fault injection, and load experiments; the H8 family topics are end-to-end systems on real infrastructure under Docker Compose. Section 11.7 now specifies every site component and page, and where each comes from. Revision 2's fixes (scripts, schemas, quotas, ordering, scope) are kept.

**Revision 5.** Fixes from a review of revision 4, each re-tested:
1. Go's `./...` pattern skips folders whose names start with `_` or `.`, so `code/_shared` tests never ran. The folder is now `code/shared` (Section 9.5 adds the rule).
2. `labserver.sh sync` refuses to touch a folder without the `.labserver-mirror` marker that `init` creates, `init` refuses home and system folders and non-empty folders, and every `results` folder at any depth survives a sync (Section 9.13).
3. One mechanism selects the thread sanitizer everywhere: a file named `sanitizer` containing `thread`, read by `code/shared/cpp/cxxflags.sh`, which every C++ `test.sh` uses (Section 9.2).
4. Exercise ids and kit paths follow one naming rule (Section 0.2); the token-bucket kit is `H5.6/lab/rung-1`.
5. `infra` is a plain list of stacks; notes live in the lab text.
6. Each stack is its own Compose project (`se-<stack>`), and `integration` stops only the stacks it started.
7. The generated routes were rebuilt on Astro 7.4.0 with Starlight 0.42.6, inside Starlight's page layout, and `[track]/reserved.astro` has `getStaticPaths`; the reserved page was checked in a real browser.
8. Validation checks are numbered in order.
9. Toolchain targets moved to the newest releases (Section 3.1).

**Revision 4.** All Docker stacks (PostgreSQL, MySQL, Redis, Kafka), integration tests, service-backed kits, multi-process lab runs, and full experiments now run on Saurabh's **LAN lab server** through `scripts/labserver.sh` (Section 9.13). Labs use MySQL and Kafka where they teach something (H1.3, H5.1, H8). New Section 18 is the recipe for generating every exercise, kit, lab rung, and page, with scaffolding scripts, templates, a finished sample of each item type, and the generated page routes.

---

## Table of contents

0. Relationship to PLAN.md
1. Goal and quality bar
2. The design recognition procedure
3. Toolchains and settings
4. Repository layout additions
5. LLD curriculum (48 topics, C++)
6. HLD curriculum (52 topics, Go labs)
7. Data files: schemas
8. Lesson page: template and section rules
9. Code, labs, experiments, and measurement
10. Exercise bank and reference solutions
11. Site additions, including every component and page
12. Build-time validation
13. Per-topic pipeline
14. Milestones and review gates
15. Progress and feedback
16. Definition of Done
17. Failure handling
18. Generating the content: exercises, kits, labs, and pages
- Appendix A: sample LLD card (Strategy), measured in C++
- Appendix B: sample HLD claim and lab (replication quorum), in Go
- Appendix C: sample HLD lab kit (token bucket), in Go

---

## 0. Relationship to PLAN.md

### 0.1 Inherited unchanged
Everything in `PLAN.md` not listed in 0.2 applies as written. In particular:
- Section 0 operating rules 1–9, with "problem" read as "exercise, lab, or cited source" where relevant. Rule 1 becomes: never state a link, title, version, or fact about a real system from memory; open the source first.
- Tech stack (Section 2), self-hosting and deployment (14.2), git workflow (14.0), CI (14.1), `PROGRESS.md` and `FEEDBACK.md` (Section 16), writing rules (Section 7), the storage module and progress page (Section 10).
- Copyright rule: never copy text, diagrams, or code from books, blogs, or papers. Summaries are one line in your own words. Diagrams are drawn fresh in Mermaid.

### 0.2 Overrides and additions
| Topic | Change |
|---|---|
| Curriculum | `curriculum.yaml` rows get a `track` field (`cp`, `lld`, `hld`). `order` is per track. Strict dependency order applies **within a track**. There are **no cross-track dependencies**. |
| Ids | LLD topics `L{phase}.{n}`, HLD topics `H{phase}.{n}` (e.g., `L2.1`, `H4.2`; `L0.0` is the first LLD topic). File naming follows PLAN.md Section 3: `L2.1` → data file `L2-1.yaml`, lesson `lld/phase-2/L2-1-strategy.mdx`. Exercise ids are globally unique as `{topic}/{local-id}`. Local ids: `rung-N` (ladder rungs), `ex-N` (worked examples and other build exercises), `est-N` (estimates), `r-N` (drill), `mock-N` / `cp-N` (checkpoints), `rev-S-N` (review set S, item N), `exam-N`. Kit paths: `{topic}/lab/rung-N` (HLD lab rungs), `{topic}/ladder/rung-N` (LLD change-ladder rungs), `{topic}/{local-id}` (all other kits). |
| Lesson template | Section 8 of this file replaces PLAN.md Section 6 for LLD and HLD topics. |
| "Problems" | Replaced by **exercises** and **labs** (Section 10). There is no online judge for design, so each ships with its own checker: a test kit, a numeric answer, or an evidence-based rubric. |
| Code | LLD: C++23 with g++ (Section 9.2). HLD: Go, one Go module under `code/` (Section 9.5). Tested with the scripts in Section 9, not with `stress.sh`. |
| Validation | Section 12 of this file adds to PLAN.md Section 12. |
| Definition of Done | Section 16 of this file replaces PLAN.md Section 17.1 for these tracks. |

### 0.3 Order of work
1. Finish whatever PLAN.md milestone is in progress. Do not interleave.
2. Run milestone **D0** (Section 14) before any design lesson: toolchains, shared lab tools, site components, then the exercise inventory.
3. Design lessons are written at the pace Saurabh studies (PLAN.md pacing rule, per track).

---

## 1. Goal and quality bar

### 1.1 Goal
Take Saurabh from "I can build services that work" to "given an unfamiliar design prompt, I can quickly name the forces in it, choose a structure for a stated reason, defend the trade-off with numbers or measurements, and I have built and broken each mechanism myself". As in the CP programme, the special emphasis is **recognition**: knowing where to look, by checking a structural property rather than matching surface words.

### 1.2 Quality properties, in priority order
1. **Correct:** every claim is proved, computed, simulated, measured, or cited to a source that was opened. Every code sample compiles, passes its tests, and (for concurrent code) passes the race detector or thread sanitizer.
2. **Practical:** every HLD mechanism is built and run; every LLD pattern is written, changed, and measured in real C++.
3. **Honest about cost:** every technique is taught with its price and with the situations where it should **not** be used.
4. **Builds recognition:** each technique is tied to the force or need it answers, a decisive property, and kill signals.
5. **Sticks:** spaced re-design of related prompts, recognition drills, number drills, and re-running labs with a twist.
6. **Calibrated:** exercises and lab rungs rise in small steps, each adding one force or one failure.
7. **Readable for Saurabh:** terms defined before use; abbreviations expanded on first use on each page; code or a diagram for every mechanism; **every C++ and Go construct that is not obvious explained in plain words**, with extra care for macros, templates, pointers and ownership, function objects, goroutines, channels, and interfaces. No pattern or architecture is explained by metaphor alone.

### 1.3 How CP ideas map to design
| In CP | In LLD (C++) | In HLD (Go) |
|---|---|---|
| Constraints → complexity budget | Expected changes → edit cost and blast radius | Traffic and data size → QPS, bytes, machines, latency budget |
| Question form → weak signals | Requirement wording → weak signals | Prompt wording → weak signals |
| Structural property = precondition of the proof | Force = the pressure the structure relieves, with a measurable symptom | Property = the assumption under which a guarantee or capacity argument holds |
| Kill signal | Over-engineering signal | Premature-complexity signal |
| Look-alike pairs | Similar class diagrams, different forces (State vs Strategy) | Similar jobs, different guarantees (queue vs log; cache vs replica) |
| Ladder, one twist per rung | Change ladder: one new requirement per rung | Lab ladder: one new failure, load, or requirement per rung |
| Brute-force stress test | Behaviour tests, sanitizers, mutants, change-cost measurement | Deterministic simulation tests, race detector, fault injection, load experiments |
| Checkpoint | Timed build with tests plus rubric | Timed design plus rubric, on a mechanism he has built |

### 1.4 Pedagogical inspiration
- **LLD:** the Gang of Four's *Design Patterns* (patterns as named solutions to forces); Fowler's *Refactoring*; Liskov's substitution principle (Liskov 1987; Liskov and Wing 1994), stated with Meyer's design-by-contract rules for preconditions and postconditions; the C++ Core Guidelines (ownership, resource management); test-driven design.
- **HLD:** Kleppmann's *Designing Data-Intensive Applications*; the Google *Site Reliability Engineering* book; the classic papers (Section 10.6); queueing theory; and the habit of "build it small, then break it" that distributed-systems courses use (labs with fault injection).
- Read these to check your understanding. Do not copy their text, figures, or code.

---

## 2. The design recognition procedure

Every lesson teaches its techniques through this procedure, the design version of PLAN.md Section 11.1.

### 2.1 Layer 1: numbers first
- **LLD:** list what is *expected to change* and how often, from the prompt and the clarifying answers: how many variants exist, how many more are plausible, which dimensions vary independently, who tests and owns each part. This gives the **trade-off table** (2.3).
- **HLD:** compute the **load**: requests per second (QPS), reads versus writes, stored bytes per year, bandwidth, peak factor, latency target, availability target. Then the **budget**: machines, memory, whether one machine can do it. From H0.1 on, Saurabh checks his estimates against his own measurements: the labs print the throughput and latency of what he built.

### 2.2 Layer 2: wording → candidates (weak signals)
Wording only raises candidates; it never decides. A weak signal is a pair: how the requirement is worded, and the shape of the numbers or variants around it.

### 2.3 Layer 3: the decisive property → decision
- **LLD force:** a named pressure with a measurable symptom:
  - **Blast radius** of a change: the number of *other* pre-existing, separately tested behaviours whose code sits in the same function or class body as an edited line (exact rule in Section 9.3).
  - **Edit cost:** files and lines touched per change request (measured by `change_cost.sh`).
  - **Branch growth**, and **testability** (can a class be tested without its real collaborators?).
  
  The **trade-off table** shows overhead, edit cost, and blast radius for the plain and the patterned design. There is usually no single break-even number, because lines and behaviours-at-risk are different units; the lesson states the trade in words and numbers (Appendix A).
- **HLD property:** the assumption under which a guarantee or capacity argument holds ("reads tolerate 1 second of staleness"; "W + R > N and the read starts after the write was acknowledged"). The lab shows the guarantee holding when the property holds and **breaking when it does not** (a test that produces the stale read, the lost update, or the overload collapse).

Every card states the property, **how to test it** in one check, and its **kill signals**, including the over-engineering case with a concrete instance.

### 2.4 Decision records
Every worked example, lab, and reference solution ends with a **decision record**: the choice, the numbers or measurements behind it, the two best alternatives, and the change in numbers that would flip the decision. LLD teaches the format in L1.1, HLD in H0.2; earlier topics write a two-line version (choice and reason).

---

## 3. Toolchains and settings

Create `src/data/design.config.yaml`:

```yaml
lld:
  language: cpp
  standard: c++23
  compiler: g++               # GCC 16 (the newest release line; Section 3.1)
  flags: "see code/shared/cpp/cxxflags.sh (the single source of compiler flags)"
  sanitizers_default: "-fsanitize=address,undefined -fno-sanitize-recover=all"
  sanitizers_concurrency: "-fsanitize=thread"      # L6 units and kits; cannot be combined with address
hld:
  language: go
  go_version: "1.27"          # the go directive in code/go.mod (Section 3.1)
  module: selfengine/code
  allowed_modules: []         # third-party Go modules, each added only through Section 9.5's process
  lab_server: true            # every Docker stack and service-backed test runs on the LAN lab server (Section 9.13)
```

- **C++:** GCC 16 with C++23 (`std::expected` and the C++23 library are available); tests use the project's own `check.hpp` (Section 9.2), so there is no third-party test framework to install. Address and undefined-behaviour sanitizers run on every LLD test; the thread sanitizer runs on concurrency units (L6) instead.
- **Go:** the version in `code/go.mod` and CI must match. Confirm the current stable release on go.dev at D0, use it, and record it in `docs/design/TOOLCHAINS.md`. The standard library is the default. A third-party module may be added only when the standard library cannot do the job (for example, a PostgreSQL driver), through the approval process in Section 9.5.
- **Docker and services:** PostgreSQL, MySQL, Redis, and Kafka run as Docker Compose stacks **on the LAN lab server** (Section 9.13), never on the machine where you edit. Pin every image by version and digest at D0, after checking the image's official page and licence, and record them in `.env.labserver` and `TOOLCHAINS.md`.
- **Changing a language** is a project change, not a setting: record it under "Questions for Saurabh" and wait for approval.

**Cross-track links:** a lesson may link to another track only in an optional final `## See also` section. These links are never prerequisites.

### 3.1 Versions: use the newest releases
Target the newest stable release of everything. The versions below were current when this plan was written (October 2026). At D0, check each again at its official source, use whatever is newest then, and record the result in `docs/design/TOOLCHAINS.md`.

| Tool | Target | How it was checked | Tested in this plan with |
|---|---|---|---|
| Go | 1.27 (1.27.1 is the newest patch) | Go release announcements | Go 1.24.7 (the newer toolchain could not be downloaded where this plan was written); D0 re-runs every script and test on 1.27 |
| GCC | 16 (16.2 is the newest release; GCC 16 defaults to C++20, so pass `-std=c++23`) | GCC release announcements | GCC 13.3 with `-std=c++23`; D0 re-runs on GCC 16 |
| C++ standard | C++23 | Latest published ISO standard with full compiler support | as above |
| Astro | 7.4.0 | `npm view astro version` | 7.4.0 |
| Starlight | 0.42.6 | `npm view @astrojs/starlight version` | 0.42.6 |
| `yaml` (npm) | 2.9.1 | `npm view yaml version` | 2.9.1 |
| Node.js | the current LTS release | nodejs.org | Node 22 |
| Docker images (PostgreSQL, MySQL, Redis, Kafka) | newest stable tag of each official image, pinned by digest | each image's official page | `docker compose config` only |

If a newer release breaks something in this plan, prefer the newer release and fix the plan's code, recording the change under "Questions for Saurabh".

---

## 4. Repository layout additions

```
.
├── DESIGN_TRACKS_PLAN.md
├── docs/design/TOOLCHAINS.md         # versions confirmed at D0 (g++, Go, Docker images with digests, Go modules)
├── code/
│   ├── go.mod                        # one Go module for all HLD code: module selfengine/code
│   ├── shared/
│   │   ├── cpp/check.hpp             # C++ test helper (Section 9.2)
│   │   ├── go/simnet/                # deterministic simulated network (Section 9.6)
│   │   ├── go/faultproxy/            # TCP proxy for real fault injection (Section 9.7)
│   │   ├── go/loadgen/               # open-loop load generator with percentiles (Section 9.7)
│   │   ├── go/capcalc/               # estimation calculator used by calc units (Section 9.8)
│   │   └── constants.json            # generated from src/data/constants.yaml
│   ├── L2.1/
│   │   ├── strategy-fee/             # C++ pattern unit (Section 9.3)
│   │   └── caller-unchanged/         # C++ solution unit (Section 9.2)
│   └── H4.2/
│       ├── claim-1/                  # Go claim program: main.go + expected.txt (Section 9.8)
│       ├── calc-quorum-table/        # Go calc program: main.go + expected.txt (Section 9.8)
│       └── lab-quorumkv/             # Go lab: package, tests, cmd/, experiments/ (Section 9.6)
├── exercises/                        # kits Saurabh works in (Section 10.3): L…/ in C++, H…/ in Go
├── reference/                        # reference solutions, same relative paths as the kits
├── reference-mutants/                # deliberately wrong solutions, same relative paths
├── labserver/stacks/                  # compose stacks run on the LAN lab server: postgres, mysql, redis, kafka (Section 9.13)
├── .env.labserver.example            # server address and pinned images; copy to .env.labserver (gitignored)
├── templates/                        # scaffolding templates for topics and kits (Section 18.3)
├── work/                             # Saurabh's attempts (gitignored)
├── notes/design/                     # private notes per topic (never rendered)
├── scripts/
│   ├── change_cost.sh                # Section 9.4 (exact; tested)
│   ├── test_design.sh                # Section 9.9 (exact; tested)
│   ├── exercise_kit_check.sh         # Section 9.10 (exact; tested)
│   ├── new_attempt.sh                # Section 9.11 (exact; tested)
│   ├── labserver.sh                  # Section 9.13 (exact; tested)
│   ├── new_topic.mjs                 # Section 18.3 (exact; tested)
│   ├── new_kit.mjs                   # Section 18.3 (exact; tested)
│   ├── inventory_check.mjs           # Section 18.2
│   ├── constants_export.mjs          # Section 9.8
│   └── keyword_collisions.mjs        # Section 12, D11
└── src/
    ├── components/design/            # Section 11.7
    ├── pages/{lld,hld}/              # Section 11.7
    ├── data/
    │   ├── design.config.yaml
    │   ├── constants.yaml
    │   ├── rubrics.yaml
    │   ├── product-names.yaml
    │   ├── topics/                   # L2-1.yaml, H4-2.yaml, …
    │   ├── exercises/                # one file per topic + INVENTORY.yaml
    │   └── experiments/              # recorded experiment results (Section 9.7)
    └── content/docs/{lld,hld}/phase-*/
```

`.gitignore`: add `**/.build/`, `code/**/bin/`, `*.test`, `.cache/`, `work/`, `.env.labserver`.

---

## 5. LLD curriculum (48 topics, C++)

Topics are ordered by `order` within the track; "requires" is explicit. Keywords work as in PLAN.md Section 4 (case-insensitive whole-phrase search). A lesson may not use a later topic's keyword outside "What this topic does not cover".

**Topic kinds** (column `kind` in `curriculum.yaml`):
- `measured`: has at least one `measured` claim and therefore two pattern units from different domains (Section 9.3). Section 1 of the lesson shows `change_cost.sh` numbers.
- `standard`: claims are proved, demonstrated by tested code, or cited; no pattern units required.
- `light`: recognition-focused coverage of a less common pattern: 1–2 cards, a ladder of 3–4 rungs, a drill of 6, no pattern units, no checkpoint (drill items join the phase exam pool).
- `capstone`: no new technique (L7.7).

### Phase L0: Object foundations in C++
| order | id | slug | kind | title | requires | keywords |
|---|---|---|---|---|---|---|
| 1 | L0.0 | cpp-for-design | standard | C++ for object design: headers, constructors and destructors, RAII, references and `const`, value vs reference semantics, `std::unique_ptr` and `std::shared_ptr`, the course's `check.hpp` | — | raii, move semantics, smart pointer |
| 2 | L0.1 | classes-invariants | standard | Classes, encapsulation, invariants, immutability | L0.0 | class invariant, immutable object |
| 3 | L0.2 | polymorphism | standard | Interfaces as abstract classes, virtual functions, virtual destructors, how a virtual call works (the vtable); static polymorphism with templates, briefly | L0.1 | dynamic dispatch, virtual function, vtable |
| 4 | L0.3 | relationships | standard | Association, aggregation, composition, inheritance; ownership in diagrams and in code; composition over inheritance | L0.1, L0.2 | composition over inheritance, aggregation |
| 5 | L0.4 | uml | standard | Reading and drawing class and sequence diagrams (Mermaid) | L0.3 | class diagram, sequence diagram |
| 6 | L0.5 | srp-ocp | measured | Single Responsibility and Open/Closed principles, measured with change scenarios | L0.3 | single responsibility principle, open/closed principle, blast radius |
| 7 | L0.6 | lsp-isp-dip | standard | Liskov Substitution (as contracts), Interface Segregation, Dependency Inversion | L0.2, L0.5 | liskov substitution, interface segregation, dependency inversion |
| 8 | L0.7 | smells | standard | Code smells and safe refactoring steps | L0.5, L0.6 | code smell, refactoring step |
| 9 | L0.8 | testable-design | standard | Unit tests with `check.hpp`, test doubles (stubs, fakes, spies) through interfaces, testability as a design criterion | L0.6 | test double, stub object, fake object |

### Phase L1: From requirements to a model
| order | id | slug | kind | title | requires | keywords |
|---|---|---|---|---|---|---|
| 10 | L1.1 | requirements | standard | Clarifying requirements: scope, assumptions, use cases, what to ask; decision records | L0.5 | functional requirement, non-functional requirement |
| 11 | L1.2 | entities | standard | Entities from nouns, behaviour from verbs, assigning responsibility | L1.1, L0.5 | information expert, responsibility assignment |
| 12 | L1.3 | state-modelling | standard | State, lifecycle, `enum class`, illegal transitions, invariants over time | L1.2, L0.1 | object lifecycle, transition table |
| 13 | L1.4 | api-design | standard | Function signatures, errors (exceptions vs `std::optional` vs `std::expected`), validation, idempotency | L1.2, L0.6 | result type, idempotent method |
| 14 | L1.5 | data-in-memory | standard | Choosing standard containers for the operations an object must support (`std::unordered_map`, `std::map`, `std::priority_queue`, `std::list` with iterators) | L1.4 | data structure choice, operation cost table |
| 15 | L1.6 | machine-coding-round | standard | How a machine-coding round runs: time-boxing, narrating, extending under pressure, a C++ project skeleton you can type from memory | L1.1, L1.2, L0.8 | machine coding round |

### Phase L2: Varying behaviour
| order | id | slug | kind | title | requires | keywords |
|---|---|---|---|---|---|---|
| 16 | L2.1 | strategy | measured | Strategy (with virtual interfaces; `std::function` as the lightweight alternative) | L0.5, L0.6, L1.2 | strategy pattern |
| 17 | L2.2 | template-method | measured | Template Method (and when inheritance is fine) | L0.3, L2.1 | template method |
| 18 | L2.3 | state | measured | State | L1.3, L2.1 | state pattern |
| 19 | L2.4 | command | measured | Command, undo and redo | L2.1, L0.8 | command pattern, undo stack |
| 20 | L2.5 | observer | measured | Observer and event models (push vs pull); dangling observers and `std::weak_ptr` | L0.6, L1.4 | observer pattern, event listener |

### Phase L3: Creating objects
| order | id | slug | kind | title | requires | keywords |
|---|---|---|---|---|---|---|
| 21 | L3.1 | factory | measured | Simple Factory and Factory Method; registries instead of switch | L2.1 | factory method, simple factory |
| 22 | L3.2 | abstract-factory | measured | Abstract Factory | L3.1 | abstract factory, product family |
| 23 | L3.3 | builder | measured | Builder; telescoping constructors; immutable construction | L0.1, L1.4 | builder pattern, telescoping constructor |
| 24 | L3.4 | singleton-di | measured | Singleton (and the static-initialisation-order problem) and its costs; dependency injection and the composition root | L0.6, L0.8, L3.1 | singleton pattern, dependency injection, composition root |
| 25 | L3.5 | prototype | light | Prototype and copying objects (shallow vs deep; virtual `clone`) | L0.1, L3.1 | prototype pattern, deep copy |

### Phase L4: Structuring objects
| order | id | slug | kind | title | requires | keywords |
|---|---|---|---|---|---|---|
| 26 | L4.1 | adapter | measured | Adapter | L0.6 | adapter pattern |
| 27 | L4.2 | decorator | measured | Decorator | L0.3, L2.1 | decorator pattern |
| 28 | L4.3 | composite | measured | Composite | L0.2, L0.3 | composite pattern |
| 29 | L4.4 | facade | measured | Facade | L0.5 | facade pattern |
| 30 | L4.5 | proxy | measured | Proxy (virtual, protection, caching) | L4.1, L0.6 | proxy pattern, lazy loading |
| 31 | L4.6 | bridge-flyweight | light | Bridge (and the pimpl idiom) and Flyweight | L2.1, L4.2 | bridge pattern, flyweight pattern |
| 32 | L4.7 | data-access | measured | Repository, Unit of Work, and Null Object | L0.6, L0.8, L4.4 | repository pattern, unit of work, null object |

### Phase L5: Collaboration between objects
| order | id | slug | kind | title | requires | keywords |
|---|---|---|---|---|---|---|
| 33 | L5.1 | chain | measured | Chain of Responsibility | L2.1, L4.2 | chain of responsibility |
| 34 | L5.2 | mediator | measured | Mediator | L2.5 | mediator pattern |
| 35 | L5.3 | iterator | measured | Iterator: writing a C++ iterator type and range-based `for`; lazy sequences | L0.2, L4.3 | iterator pattern, lazy sequence |
| 36 | L5.4 | memento | light | Memento and snapshots | L2.4 | memento pattern |
| 37 | L5.5 | visitor | light | Visitor and double dispatch; `std::variant` with `std::visit` as the closed-set alternative | L0.2, L4.3 | visitor pattern, double dispatch |

### Phase L6: Concurrency in designs
Units in this phase run under the thread sanitizer.
| order | id | slug | kind | title | requires | keywords |
|---|---|---|---|---|---|---|
| 38 | L6.1 | races-locks | standard | Data races (undefined behaviour in C++), `std::thread`, `std::mutex`, `std::scoped_lock`, deadlock and lock ordering | L0.1 | data race, deadlock, lock ordering |
| 39 | L6.2 | thread-safe-objects | standard | Thread-safe objects: immutability, confinement, lock granularity, `std::atomic` and compare-and-swap, optimistic concurrency with version numbers | L6.1, L1.5 | lock granularity, compare-and-swap, optimistic concurrency |
| 40 | L6.3 | producer-consumer | standard | Producer–consumer with `std::condition_variable`, bounded blocking queues, thread pools | L6.2 | blocking queue, thread pool, condition variable |
| 41 | L6.4 | futures-cancellation | standard | Futures, timeouts, and cancellation: `std::future`, `std::async`, `std::jthread`, `std::stop_token` | L6.3 | std::future, stop_token |

### Phase L7: Whole systems (integration)
Each L7 lesson opens with "This topic combines X and Y." linking both. Each family lesson teaches a **family skeleton** (the base design most prompts of that family share) plus the three mistakes that recur in that family; its ladder is one evolving C++ system (Section 10.2).
| order | id | slug | kind | title | requires | keywords |
|---|---|---|---|---|---|---|
| 42 | L7.1 | family-allocation | standard | Allocation systems: parking lot, locker, hotel and seat booking | L2.1, L2.3, L6.2 | allocation system |
| 43 | L7.2 | family-state-machines | standard | State-machine systems: vending machine, ATM, elevator, traffic light | L2.3, L2.5, L6.1 | state-machine system |
| 44 | L7.3 | family-caches | standard | Cache and store systems: LRU and LFU cache, key-value store with expiry, rate limiter | L1.5, L2.1, L6.2 | eviction policy, token bucket |
| 45 | L7.4 | family-games | standard | Game systems: tic-tac-toe, snake and ladder, chess | L2.1, L2.3, L4.3 | game system |
| 46 | L7.5 | family-events | standard | Event-driven systems: notification service, logger, in-memory pub/sub, order book | L2.5, L5.1, L6.3 | event-driven system, order book |
| 47 | L7.6 | family-hierarchy-and-marketplace | standard | Hierarchies and marketplaces: file system, spreadsheet, expense splitting, ride matching | L4.3, L5.5, L6.2 | expense splitting, ride matching |
| 48 | L7.7 | lld-recognition | capstone | Recognition: mixed prompts, family and pattern not given | all LLD topics, expanded | (none) |

Notes:
- "all LLD topics" is expanded to explicit ids in `curriculum.yaml`.
- L0.0 exists because C++ ownership decides many designs: who owns an object (`std::unique_ptr`), who only uses it (reference or raw pointer), and when it is destroyed (RAII). Every later lesson relies on it.
- Anti-patterns are taught inside the topic that prevents them: God class in L0.5, inappropriate inheritance in L0.3, Singleton overuse in L3.4, owning raw pointers in L0.0, and pattern overuse in every pattern lesson's kill signals.

---

## 6. HLD curriculum (52 topics, Go labs)

Every HLD topic except H0.7 and H8.10 has a **lab**: a mechanism Saurabh builds in Go, tests on the deterministic simulated network (`simnet`), runs as real processes, breaks with `faultproxy`, and measures with `loadgen` (Section 9). The "Lab" column says what is built. "Infra" is the plain list of stacks the lab needs on the LAN lab server (Section 9.13); `—` means none. Notes about how a stack is used are in the "Lab" column. Labs use only the Go standard library unless a module is approved under Section 9.5 (the PostgreSQL and Redis-protocol clients and a WebSocket library are the expected ones).

Numbers in lessons come from `constants.yaml`, calc programs, and recorded experiments, never from memory. All HLD topics are `kind: standard` except H8.10 (`capstone`).

### Phase H0: Numbers, vocabulary, and the design round
| order | id | slug | title | requires | Lab (built in Go) | Infra | keywords |
|---|---|---|---|---|---|---|---|
| 1 | H0.1 | latency-throughput | Latency, throughput, percentiles, tail latency, Little's law | — | Open-loop load generator with exact percentiles; measure an HTTP service and check Little's law against the measured number of in-flight requests; show how a closed-loop generator hides latency | — | tail latency, little's law, coordinated omission |
| 2 | H0.2 | estimation | Back-of-envelope estimation: QPS, storage, bandwidth, machines, error bounds; decision records | H0.1 | Estimation calculator (`capcalc`) driven by `constants.json`; compare one estimate with a measured run of the H0.1 service | — | back-of-envelope, peak factor |
| 3 | H0.3 | availability | Availability math: nines, serial and parallel composition, MTBF, MTTR, SLI, SLO, SLA | H0.1 | Health prober measuring availability of a service that `faultproxy` makes flaky; compare measured availability of serial and redundant setups with the formulas | — | mean time between failures, service level objective |
| 4 | H0.4 | queueing | Queueing basics: utilisation and latency, why systems fall over near full load | H0.1 | Server with a fixed worker pool and a queue; sweep offered load from 50% to 99% of capacity and plot p50 and p99; compare with the M/M/1 formula; add a queue bound and show what it changes | — | utilisation, queueing delay |
| 5 | H0.5 | networking | Networking for designers: DNS, TCP vs UDP, HTTP versions, TLS cost, L4 vs L7 load balancers, WebSocket, gRPC | H0.1 | Measure connection setup cost: new TCP and TLS connection per request versus keep-alive, HTTP/1.1 versus HTTP/2 multiplexing, on loopback with `faultproxy` adding 20 ms of delay; server-sent events stream | — | tcp handshake, websocket, grpc |
| 6 | H0.6 | api-design | API design: REST resources, idempotency keys, pagination (offset vs cursor), versioning, errors | H0.5 | REST service with idempotency keys (a retried POST creates one resource) and cursor pagination that stays correct while rows are inserted; tests for both | — | cursor pagination, idempotency key |
| 7 | H0.7 | design-round | How a system design round runs: scoping, time-boxing, narrating, handling pushback | H0.2, H0.6 | none (timed mock rounds) | — | system design round |

### Phase H1: Data on one machine
| order | id | slug | title | requires | Lab (built in Go) | Infra | keywords |
|---|---|---|---|---|---|---|---|
| 8 | H1.1 | data-models | Data models by access pattern: relational, document, key-value, wide-column, graph, time-series; transactional (OLTP) vs analytical (OLAP) workloads | H0.2 | Model one feature (orders and their items) three ways (normalised tables, a JSON document column, key-value records), run the same five queries on each, and record time and code size | postgres | document store, wide-column store, olap |
| 9 | H1.2 | indexes | Indexes: B-tree vs log-structured merge tree (LSM), read/write/space amplification | H1.1 | Mini LSM store: write-ahead log, in-memory table, sorted on-disk tables, merge on read, compaction; measure write amplification; compare a B-tree index's query plans in PostgreSQL | postgres | b-tree, lsm tree, write amplification |
| 10 | H1.3 | transactions | Transactions, ACID, isolation levels, anomalies (lost update, write skew) | H1.1 | Reproduce a lost update and write skew with concurrent goroutines at different isolation levels, on both PostgreSQL and MySQL (their default isolation levels differ, and so do the anomalies you get); fix each (row lock, serializable with retry); tests that fail before the fix | postgres, mysql | isolation level, write skew, lost update |
| 11 | H1.4 | schema-design | Schema design from access patterns; normalisation vs denormalisation | H1.1, H1.2 | Design a schema for given access patterns; measure with query plans before and after an index and after denormalising one read path; keep both consistent in tests | postgres | denormalization, denormalisation |
| 12 | H1.5 | single-node-cache | Caching on one machine: cache-aside, write-through, write-back, eviction, hit-rate math | H0.2, H1.2 | In-process LRU cache with TTL and request coalescing in front of a slow store; measure hit rate against cache size under a skewed (Zipf) workload; compare with the computed expectation | — | cache-aside, write-through, hit rate |

### Phase H2: Scaling reads and splitting services
| order | id | slug | title | requires | Lab (built in Go) | Infra | keywords |
|---|---|---|---|---|---|---|---|
| 13 | H2.1 | stateless-lb | Stateless services, horizontal scaling, load-balancing algorithms | H0.4, H0.5 | L7 load balancer (`net/http/httputil`) with round robin, least connections, and power of two choices; one backend made slow with `faultproxy`; compare tail latency per algorithm | — | horizontal scaling, least connections, power of two choices |
| 14 | H2.2 | caching-at-scale | Caches at scale: CDN, shared cache, TTL, invalidation, stampede control | H1.5, H2.1 | Shared cache in front of PostgreSQL with TTL jitter; expire a hot key under 1 000 concurrent readers and count database queries with and without coalescing; an HTTP caching proxy honouring `Cache-Control` | postgres, redis | content delivery network, cache stampede |
| 15 | H2.3 | replication | Replication: leader–follower, lag, read-your-writes, monotonic reads, failover | H1.3, H2.1 | Leader–follower key-value store shipping its log over HTTP; synchronous vs asynchronous; measure lag; a test that shows a read-your-writes violation and the fix; manual failover | — | replication lag, read-your-writes, failover |
| 16 | H2.4 | read-scaling | Read-scaling patterns: replicas, materialised views, fan-out on write vs on read | H2.2, H2.3 | Timeline service built both ways (fan-out on write, fan-out on read); measure read and write cost against follower count, including one account with 100 000 followers | — | materialized view, fan-out on write |
| 17 | H2.5 | service-architecture | Monolith vs services, API gateway, service discovery | H2.1, H0.6 | Split a small monolith into two services behind a gateway with routing and authentication; a registry with heartbeats and expiry; measure latency added per hop and behaviour when the registry is down | — | api gateway, service discovery, microservices |

### Phase H3: Scaling writes and data
| order | id | slug | title | requires | Lab (built in Go) | Infra | keywords |
|---|---|---|---|---|---|---|---|
| 18 | H3.1 | partitioning | Partitioning (sharding): range vs hash, hot spots, rebalancing | H2.3, H1.4 | Sharded key-value router with range and hash partitioning; skewed workload; move a range to rebalance and measure moved keys | — | partition key, rebalancing |
| 19 | H3.2 | consistent-hashing | Consistent hashing and virtual nodes | H3.1 | Hash ring with virtual nodes; measure keys moved when a node joins (against modulo hashing) and load spread against the number of virtual nodes | — | consistent hashing, virtual node |
| 20 | H3.3 | sharded-indexes | Secondary indexes on sharded data: local vs global, scatter–gather | H3.1, H1.2 | Local and global secondary indexes over the H3.1 shards; scatter–gather query whose p99 rises with shard count (measured with `faultproxy` adding random delay) | — | scatter-gather, global secondary index |
| 21 | H3.4 | ids-ordering | Unique ids and ordering: UUID, ticket server, Snowflake-style ids, clock caveats | H3.1 | Snowflake-style id service; tests for uniqueness across nodes under concurrency, ordering within a node, and refusal when the clock moves backwards | — | snowflake id, k-sortable |
| 22 | H3.5 | hot-keys | Hot keys and skew: salting, splitting, request coalescing | H3.1, H2.2 | Detect hot keys by counting; split a hot key across salted sub-keys and merge on read; measure per-shard load before and after | — | hot key, key salting, request coalescing |

### Phase H4: Consistency and coordination
| order | id | slug | title | requires | Lab (built in Go) | Infra | keywords |
|---|---|---|---|---|---|---|---|
| 23 | H4.1 | time-ordering | Time and ordering: clocks, Lamport clocks, vector clocks, happened-before | H3.4, H0.5 | Lamport and vector clock library; simulated message exchange on `simnet` with seeded delays; detect concurrent updates | — | lamport clock, vector clock, happened-before |
| 24 | H4.2 | quorums | Replication with quorums: N, W, R; sloppy quorums; read repair; anti-entropy | H2.3, H3.2, H4.1 | Quorum key-value store on `simnet` (Appendix B), then as three processes over HTTP with `faultproxy`; read repair; a test that finds a stale read when W + R ≤ N | — | read quorum, write quorum, read repair, sloppy quorum |
| 25 | H4.3 | conflicts | Multi-leader and leaderless conflicts: last-write-wins pitfalls, version vectors, CRDT basics | H4.1, H4.2 | Two-leader store showing a lost update under last-write-wins; version vectors keeping both versions; a counter and a set CRDT with seeded tests that merging is commutative, associative, and idempotent | — | last-write-wins, version vector, crdt |
| 26 | H4.4 | cap-consistency | CAP and PACELC stated precisely; the spectrum of consistency models | H4.2, H4.3 | A small linearizability checker for short histories; run it on histories recorded from the H4.2 store under concurrent writes and partitions, and find a non-linearizable one | — | cap theorem, linearizability, eventual consistency |
| 27 | H4.5 | consensus | Consensus: leader election and log replication (Raft level), leases, fencing tokens | H4.4 | Raft subset (election and log replication, no snapshots or membership change) on `simnet` with deterministic tests: at most one leader per term, logs agree on committed entries; a lock service with fencing tokens and a store that rejects stale tokens | — | raft, leader election, fencing token |

### Phase H5: Asynchronous work and overload
| order | id | slug | title | requires | Lab (built in Go) | Infra | keywords |
|---|---|---|---|---|---|---|---|
| 28 | H5.1 | queues-logs | Queues and logs: partitions, consumer groups, ordering, delivery semantics, retries, dead-letter queues | H4.2, H3.1 | Partitioned append-only log with segment files, consumer groups, and committed offsets over HTTP; crash a consumer between processing and commit to show duplicate delivery; a dead-letter queue; a last rung repeating the same experiments against Kafka and comparing what it guarantees with what you built | kafka | consumer group, at-least-once, dead-letter queue |
| 29 | H5.2 | distributed-transactions | Distributed transactions: two-phase commit, sagas, transactional outbox, change data capture, idempotent consumers | H1.3, H4.5, H5.1 | Order, payment, and inventory services: a saga with compensation; a transactional outbox in PostgreSQL relayed to Kafka; an idempotent consumer with a de-duplication table; kill each process mid-flow and check final state | postgres, kafka | two-phase commit, saga, transactional outbox, change data capture |
| 30 | H5.3 | stream-batch | Batch vs stream processing; event time vs processing time; windows | H5.1 | Windowed aggregation over a Kafka topic with event time and watermarks; late and out-of-order events; a batch job over the same data whose result must match | kafka | stream processing, event time |
| 31 | H5.4 | pubsub-push | Pub/sub, notification fan-out, webhooks, push channels | H5.1, H2.4 | Notification service: subscriptions, webhook delivery with signed payloads (HMAC), retries with backoff; server-sent events to browsers | — | publish-subscribe, webhook, notification fan-out |
| 32 | H5.5 | scheduling | Job scheduling, delayed jobs, workflows | H5.1, H4.5 | Delayed-job scheduler on PostgreSQL with leases (`FOR UPDATE SKIP LOCKED`); kill a worker mid-job and show the job re-runs after the lease expires, with an idempotent effect | postgres | job scheduler, delayed job, workflow engine |
| 33 | H5.6 | overload | Overload control: rate limiting, backpressure, load shedding, retries with jitter, circuit breakers | H0.4, H5.1 | Token bucket (Appendix C), concurrency-limit load shedding, retries with exponential backoff and jitter, a circuit breaker; measure a retry storm's load amplification and its fix | — | rate limiting, load shedding, circuit breaker, retry storm |

### Phase H6: Specialised structures and services
| order | id | slug | title | requires | Lab (built in Go) | Infra | keywords |
|---|---|---|---|---|---|---|---|
| 34 | H6.1 | probabilistic | Probabilistic structures: Bloom filter, count-min sketch, HyperLogLog | H0.2 | All three, from scratch; measure error against the formulas over seeded data | — | bloom filter, count-min sketch, hyperloglog |
| 35 | H6.2 | search | Search: inverted index, ranking basics, sharded search, typeahead | H1.2, H3.3 | Inverted index with tokenising and TF-IDF ranking; typeahead trie returning top suggestions; sharded search with scatter–gather | — | inverted index, typeahead |
| 36 | H6.3 | geo | Geospatial indexing: geohash, quadtree, cell ids | H3.1 | Geohash encoding and neighbour search; a quadtree; nearby-query benchmark against brute force | — | geohash, quadtree |
| 37 | H6.4 | blob-storage | Blob storage and large files: chunking, deduplication, resumable upload, metadata vs data | H3.1, H2.2 | Upload service with content-defined chunking (rolling hash), de-duplication by SHA-256, resumable uploads, metadata in PostgreSQL and chunks on disk | postgres | resumable upload, content-defined chunking |

### Phase H7: Running it for real
| order | id | slug | title | requires | Lab (built in Go) | Infra | keywords |
|---|---|---|---|---|---|---|---|
| 38 | H7.1 | resilience | Failure modes, timeouts, bulkheads, graceful degradation, multi-zone and multi-region, recovery point and time objectives | H4.4, H5.6 | Add timeouts, bulkheads (separate pools), and a degraded mode to a two-dependency service; inject failures with `faultproxy` and measure the impact on the healthy path | — | bulkhead, recovery point objective, multi-region |
| 39 | H7.2 | observability | Metrics, logs, traces; SLO-based alerting; capacity planning | H0.3, H5.3 | Instrument a service: counters and histograms in the Prometheus text format (written by hand), structured logs with `log/slog`, trace ids propagated across calls; compute SLO burn rate from recorded metrics | — | error budget, distributed tracing |
| 40 | H7.3 | deployment | Deployments: rolling, blue/green, canary, feature flags, schema migrations without downtime | H7.1, H1.4 | Weighted routing for canary and blue/green in the H2.1 balancer; an expand-and-contract migration on PostgreSQL under live load with zero failed requests (measured) | postgres | canary release, blue/green deployment, expand and contract |
| 41 | H7.4 | security-tenancy | Security basics and multi-tenancy: authentication vs authorisation, tokens, encryption, tenant isolation, abuse | H0.5, H0.6 | HMAC-signed token verification middleware and role checks; per-tenant rate limits; a noisy-neighbour experiment with and without per-tenant isolation | — | oauth, multi-tenancy, noisy neighbour |
| 42 | H7.5 | build-vs-buy | Build vs buy and cost models | H7.1 | Cost-per-request calculator over designs built so far (machine hours, storage, transfer) using `capcalc` | — | build vs buy, cost per request |

### Phase H8: Whole systems (integration)
Each H8 lesson opens with "This topic combines X and Y." Each family lesson teaches a **family skeleton**, a scale ladder (Section 10.2), and the three mistakes that recur in that family. Each H8 lab is an **end-to-end system** run on the LAN lab server, load-tested with `loadgen` (from the server, and once from another LAN machine to include real network latency), and broken with `faultproxy`, with a written decision record.
| order | id | slug | title | requires | Lab: end-to-end system in Go | Infra | keywords |
|---|---|---|---|---|---|---|---|
| 43 | H8.1 | family-lookup | Read-heavy lookup: URL shortener, paste service, key-value store | H2.2, H3.2, H3.4 | URL shortener: id service, PostgreSQL, shared cache, redirect path measured to its p99 at a target load | postgres, redis | url shortener |
| 44 | H8.2 | family-feeds | Feeds: social timeline, news feed, activity stream | H2.4, H3.5, H5.4 | Feed service with hybrid fan-out (push for most accounts, pull for very large ones) and the threshold chosen from measurements | postgres, redis, kafka | news feed |
| 45 | H8.3 | family-realtime | Real-time collaboration: chat, presence, live comments, collaborative editing (basic) | H0.5, H5.4, H4.3 | Chat over WebSocket (served by the Go service) with presence (heartbeats and expiry, in Redis), message ordering per room, and offline delivery | postgres, redis | chat system, presence service, collaborative editing |
| 46 | H8.4 | family-storage-media | Storage and media: file sync, video upload and streaming, object store | H6.4, H5.5 | File sync built on the H6.4 chunk store, with a change log clients poll, and a background job pipeline for derived files | postgres, kafka | file sync, video pipeline |
| 47 | H8.5 | family-search-discovery | Search and discovery: typeahead, web crawler, trending and top-K | H6.1, H6.2, H5.3 | Polite crawler (robots rules, per-host rate limits, Bloom-filter de-duplication) over a local fake web; trending top-K with count-min sketch over a Kafka topic | kafka | web crawler, top-k |
| 48 | H8.6 | family-geo-matching | Geo and matching: nearby places, ride hailing, delivery dispatch | H6.3, H5.4, H3.5 | Driver location updates at a target rate, geohash index, matching with leases so one driver gets one ride | redis, kafka | ride hailing, nearby search |
| 49 | H8.7 | family-money-booking | Money and booking: payments, wallets and ledgers, ticket booking, flash sales | H5.2, H1.3, H5.6 | Double-entry ledger in PostgreSQL with idempotency keys and a reconciliation job; seat booking with time-limited holds; a flash sale that never oversells (checked under concurrent load) | postgres, redis | double-entry ledger, flash sale |
| 50 | H8.8 | family-integration | Data integration: multi-tenant ETL and ERP sync, idempotent upserts, dedupe by external key, reconciliation | H5.5, H5.2, H7.4 | Multi-tenant ingest that upserts by external key under a unique constraint (resubmits never duplicate), per-tenant isolation, and a reconciliation report; the "ERP" side is a MySQL database and changes flow through Kafka | postgres, mysql, kafka | etl pipeline, reconciliation job |
| 51 | H8.9 | family-infra | Infrastructure services: rate limiter, distributed cache, distributed lock, id generator, message queue, metrics system | H5.6, H4.5, H3.2, H7.2 | Distributed rate limiter over a shared store, compared with per-node limits; lock service with fencing tokens from H4.5 used by two competing workers | redis | distributed lock service |
| 52 | H8.10 | hld-recognition | Recognition: mixed prompts, family and components not given | all HLD topics, expanded | none (mock rounds) | — | (none) |

Notes:
- Product names (PostgreSQL, the Redis-compatible server, and so on) may appear in labs and in `:::example[Real systems]` blocks with cited claims (Section 12, D9). **Cards** name properties and numbers, never products.
- Labs build mechanisms from scratch first (H0–H7). Off-the-shelf services are used where building them would teach nothing new for that topic (PostgreSQL as a database), and everywhere in H8.
- "all HLD topics" is expanded to explicit ids in `curriculum.yaml`.

---

## 7. Data files: schemas

### 7.1 Curriculum rows
Append the LLD and HLD rows to `src/data/curriculum.yaml` with `track` (`lld` or `hld`), `phase`, `order` (per track), `id`, `slug`, `kind`, `title`, explicit `requires`, `keywords`, and, for HLD, `lab` (one line, from the table) and `infra` (a list of stack names from `labserver/stacks/`, empty for none). Add `track: cp` to existing rows. Zod: `track` is one of `cp | lld | hld`; every `requires` id exists in the same track with a smaller `order`; the first topic of each track has empty `requires`.

### 7.2 Topic data file: `src/data/topics/{id-with-dash}.yaml`
Same top-level structure as `PLAN.md` Section 5 (as revised), with these fields:

```yaml
id: "L2.1"
track: lld

uses:                               # every earlier topic relied on (same track); drives the header and "What you need"
  - {topic: "L0.5", what: "Change scenarios and blast radius"}
  - {topic: "L0.6", what: "Depending on an interface instead of a concrete class"}
  - {topic: "L1.2", what: "Assigning a responsibility to one class"}

claims:                             # one entry per numbered claim in the lesson (Section 8.4)
  - id: "L2.1.1"
    kind: measured                  # proved | computed | simulated | measured | experimented | cited
    title: "Adding a pricing plan edits no existing pricing logic, at a cost in lines"
    plain_words: "With one class per plan, a new plan is a new class plus one line of wiring; the old plans are untouched."
    evidence: ["L2.1/strategy-fee", "L2.1/strategy-notify"]   # code units under code/
    source: null                    # cited only: {title, url, accessed: YYYY-MM-DD, section}
  - id: "L2.1.2"
    kind: proved
    title: "Callers that depend only on the shared signature never change when a variant is added"
    plain_words: "If the calling code only knows the interface, a new class that implements it cannot require edits to that calling code."
    evidence: ["L2.1/caller-unchanged"]
    source: null

cards:                              # 1–4 per topic (light topics: 1–2)
  - id: strategy
    name: "Strategy"
    force: "Behaviour that varies independently of the code that uses it, with variants added or changed over time."   # HLD: `need`
    decisive_property: "All variants fit one function signature, and callers do not need to know which variant runs."
    from_claim: "L2.1.2"
    how_to_test: "List the variants and write the one signature they could all share. If the inputs differ per variant, the property does not hold yet."
    trade_off_table:                # LLD measured topics: from pattern units via change_cost.sh, never by hand
      units: ["L2.1/strategy-fee", "L2.1/strategy-notify"]
      overhead: "…"
      per_change: "…"
      blast_radius: "…"
      verdict: "…"
    constraint_shapes: ["…"]        # 1–3, each with arithmetic
    weak_signals:                   # 2–4, each {form, shape}
      - {form: "…", shape: "…"}
    kill_signals: ["…"]             # ≥ 2; at least one over-engineering signal with numbers
    in_action: {statement: "…", constraints: "…", budget: "…", candidates: [{tool: "…", verdict: rejected, because: "…"}, {tool: "…", verdict: chosen, because: "…"}], property_check: "…", decision: "…"}
    examples:                       # ≥ 2 positive, ≥ 2 negative; ≥ 1 of each inline with numbers
      positive: [{inline: {input: "…", answer: "…", why: "…"}}]
      negative: [{inline: {input: "…", answer: "…", why: "…"}, correct_tool: {simplest: "plain conditional"}}]
    lookalikes:                     # structured references to this or earlier topics only
      - {description: "…", tool: {topic: "L0.3", card: subtype-per-variant}, flipping_difference: "…"}
    cost: "…"
```

**HLD cards** use the same shape with these replacements:
- `force` → `need`: the requirement the technique answers, with its number.
- `trade_off_table` → `capacity_table`: `{units: [calc programs or experiments], threshold: "the number at which the technique becomes necessary", price: "extra machines, staleness, latency, failure modes"}`.
- Each HLD card also names its **lab evidence**: `lab: {unit: "H4.2/lab-quorumkv", holds_test: "TestReadMeetsAcknowledgedWrite", breaks_test: "TestW1R1CanReturnStale"}`: one test where the property holds and the guarantee is observed, and one where the property is violated and the guarantee visibly fails.

**Claim kinds:** `proved` (a proof plus an exhaustive check), `computed` (a calc program), `simulated` (a seeded simulation on `simnet` or in a claim program, with a tolerance), `measured` (LLD pattern units), `experimented` (HLD: a scripted experiment on real processes; the claim is about the **shape** of the result, checked by the experiment program, Section 9.7), `cited` (an opened source).

### 7.3 Exercise file: `src/data/exercises/{id-with-dash}.yaml`

```yaml
topic: "H4.2"
exercises:
  - id: rung-2                      # global id "H4.2/rung-2"; kit path "H4.2/lab/rung-2" (Section 0.2)
    role: ladder                    # ladder | worked_example | drill | checkpoint | review | exam
    type: lab                       # LLD: recognise | refactor | build | change_ladder | mock
                                    # HLD: recognise | estimate | lab | deep_dive | scale_ladder | failure | mock
    title: "Quorum store: survive one replica down"
    prompt: "Own words, at most 150 words. States the task and the acceptance tests, nothing about the internal design."
    inspired_by: null
    card: quorum-replication        # ladder rungs and worked examples: the card exercised (null on a no-new-structure rung)
    rung: 2
    new_force: "One replica is down during writes and reads."       # exactly one per rung
    needs_new_structure: true
    review_set: null
    answer: null                    # recognise only (Section 7.3 below)
    clarifying: [{q: "…", a: "…", critical: true}]   # build, lab (rung 1), deep_dive, scale_ladder, mock: ≥ 4, ≥ 2 critical
    checkers:                       # allowed combinations per type in Section 10.1
      - {kind: kit, path: "H4.2/lab/rung-2"}
      # - {kind: numeric, calc: "H0.2/calc-photo-uploads", key: "peak_reads_per_second", unit: "requests per second", factor: 2}
      # - {kind: rubric, id: "rubric-hld-deep-dive-v1"}
    run: "docs: how to run the real three-process version and the fault-injection script (Section 9.7)"   # labs only
    reference: "reference/H4.2/lab/rung-2"
    alternatives: ["…"]
    hints: ["…", "…", "…"]          # practice set only; exactly 3, progressive
    time_limit_minutes: null        # required for checkpoint, exam, and mock items
    techniques: ["H4.2", "H2.3"]
    checked_on: "2026-10-20"
```

`answer` for `recognise` exercises is one of:
```yaml
answer: {kind: card, card: {topic: "L2.1", card: strategy}, property: "All plans fit fee(minutes)", why_others_fail: "…"}
answer: {kind: none, simplest: "plain conditional", why: "Two fixed plans; Strategy would add files and lines for no expected change"}
```

### 7.4 Rubrics: `src/data/rubrics.yaml`
Section 10.7.

### 7.5 Planning constants: `src/data/constants.yaml` (HLD)
```yaml
- id: ssd-random-read
  quantity: "SSD random read latency"
  value: 1.0e-4                     # a number in the unit below
  unit: "s"                         # s | bytes | bytes/s | requests/s | count | ratio
  display: "about 100 microseconds"
  source: {title: "…", url: "…", accessed: "2026-10-20", section: "…"}
  caveat: "Hardware-dependent. Use for order-of-magnitude reasoning only."
```
Every constant used in a lesson, calc program, or exercise comes from this file, with a source you opened and a caveat. Where a lab can measure the quantity on Saurabh's machine (loopback round trip, disk sync time, a database query), the lesson shows both the constant and the measurement.

### 7.6 Experiment records: `src/data/experiments/{topic}/{name}.yaml`
```yaml
experiment: "H0.4/queue-sweep"
program: "code/H0.4/lab-queue/experiments/sweep"   # a Go main package
machine: {cpu: "…", cores: 8, os: "…", go: "1.27.x"}   # printed by the program itself
run_on: "2026-10-21"
shape_checks:                       # printed by the program as PASS/FAIL lines; all must PASS
  - "p99 at 90% load is at least 3 times p99 at 50% load"
results_file: "results/2026-10-21-agent.tsv"   # committed next to the program
```

---

## 8. Lesson page: template and section rules

Lesson file: `src/content/docs/{lld|hld}/phase-{n}/{id-dash}-{slug}.mdx`. Required headings, in this order, with this exact text (an optional final `## See also` is allowed for cross-track links):

```mdx
---
title: "H4.2 Replication with quorums"
sidebar:
  order: 24
topic: "H4.2"
---
import { Code } from '@astrojs/starlight/components';
import TopicHeader from '../../../../components/TopicHeader.astro';
import WhatYouNeed from '../../../../components/WhatYouNeed.astro';
import ClaimEvidence from '../../../../components/design/ClaimEvidence.astro';
import TradeOffTable from '../../../../components/design/TradeOffTable.astro';
import LabRunner from '../../../../components/design/LabRunner.astro';
import ExperimentResult from '../../../../components/design/ExperimentResult.astro';
import Cards from '../../../../components/Cards.astro';
import Exercises from '../../../../components/design/Exercises.tsx';
import Drill from '../../../../components/Drill.tsx';
import LookalikePairs from '../../../../components/LookalikePairs.astro';
import SelfTest from '../../../../components/SelfTest.astro';
import Checkpoint from '../../../../components/Checkpoint.tsx';
import DecisionMapUpdate from '../../../../components/DecisionMapUpdate.astro';

<TopicHeader topic="H4.2" />

## 1. Why this topic exists
## 2. Prerequisites and scope
### What you need
<WhatYouNeed topic="H4.2" />
### What this topic does not cover
## 3. Definitions
## 4. Principles and claims
## 5. Recognition Cards
<Cards topic="H4.2" />
## 6. Reference designs
<LabRunner unit="H4.2/lab-quorumkv" />
## 7. Mistake catalogue
## 8. Worked examples
## 9. Exercise ladder
<Exercises topic="H4.2" client:load />
## 10. Recognition drill
<Drill topic="H4.2" client:load />
## 11. Look-alike pairs
<LookalikePairs topic="H4.2" />
## 12. Self-test questions
<SelfTest topic="H4.2" />
## 13. Checkpoint
<Checkpoint topic="H4.2" client:load />
## 14. Decision map update
<DecisionMapUpdate topic="H4.2" />
```
Adjust the relative import depth to the folder depth. `light` topics keep heading 13 with the text "This topic has no checkpoint; its drill items join the phase exam pool."

### 8.1 Section 1: Why this topic exists
- **LLD `measured` topics:** a naive C++ program of at most 40 lines that works, then one realistic change request that hurts it, with the numbers from the pattern unit (edit cost from `change_cost.sh`, blast radius from `unit.yaml`).
- **LLD `standard` and `light` topics:** a naive program of at most 40 lines and its concrete problem, shown by a failing test, a sanitizer report, a broken invariant, or a class that cannot be tested.
- **HLD:** a running problem, not only a calculation: the lab's simplest version under a load or a failure where it breaks (for example, "one replica is killed and writes stop"; "at 90% load p99 is 12 times p50"), with the output shown, plus the computed budget for a prompt-sized load.
- Then one plain paragraph with the key idea. No new code or diagram yet.

### 8.2 Section 2: Prerequisites and scope
As `PLAN.md` 6.2: `<WhatYouNeed>` from `uses`; "What this topic does not cover" is the only place later keywords may appear.

### 8.3 Section 3: Definitions
As `PLAN.md` 6.3. LLD definitions include a 3–8 line C++ example. HLD definitions include a number, a tiny diagram, or a 3–8 line Go example.

### 8.4 Section 4: Principles and claims
Every claim is numbered `Claim {topic}.{n}`, has an entry in `claims` (Section 7.2), and uses this layout:
1. **Statement,** precise.
2. **In plain words** (`:::tip[In plain words]`).
3. **A tiny instance with real numbers** before any argument.
4. **Reasoning,** as numbered steps (at most 8, each at most two lines), by kind:
   - `proved`: a proof (rules of `PLAN.md` 6.4). HLD evidence: a claim program (Go) that checks the statement exhaustively on all small cases. LLD evidence: a C++ solution unit whose tests demonstrate the claim.
   - `computed`: a derivation with units on every line; evidence: a calc program (Go).
   - `simulated`: what is simulated, the seed, the runs, the tolerance; evidence: a seeded simulation (Go).
   - `measured` (LLD `measured` topics): the two variants and the change scenarios; evidence: two C++ pattern units with different `domain`s, rendered by `<TradeOffTable>`.
   - `experimented` (HLD): the experiment's setup (processes, load, faults), the **shape** claimed, the recorded result with the machine it ran on, and the shape checks the program printed. Absolute numbers are labelled "on this machine".
   - `cited`: the source (title, URL, accessed date, section), the claim in your own words, and what the source does **not** say.
5. **Preconditions box**, exactly:
   ```mdx
   :::note[This claim needs]
   1. …
   :::
   ```
6. **Evidence:** `<ClaimEvidence claim="…" />` (or `<ExperimentResult experiment="…" />` for `experimented`).
7. **Cost line:** one or two sentences stating the price.

Reading test (Definition of Done): every step must be followable with the track's Phase 0 knowledge plus this page.

### 8.5 Section 5: Recognition Cards
As `PLAN.md` 6.5 (as revised), with the field names of Section 7.2. Also:
- LLD cards in `measured` topics have a `trade_off_table` from units; HLD cards with a capacity argument have a `capacity_table` from calc programs or experiments. Never typed by hand.
- **HLD cards point to their lab tests**: the test where the property holds, and the test where it is broken and the guarantee fails.
- At least one kill signal per card is an **over-engineering** signal with a concrete instance and numbers.
- HLD cards name properties and numbers, never products. LLD cards name forces and symptoms, never frameworks.

### 8.6 Section 6: Reference designs
- **LLD:** for each pattern or principle: a class diagram (Mermaid); a sequence diagram of one call; the plain design, then the designed version, both as tested C++ via `<Code>` imports of the unit files; **How it works** (walk through the names); **C++ details explained**: every construct beyond earlier lessons in plain words: `virtual`, `override`, `final`, `= 0`, `= default`, virtual destructors, `std::unique_ptr` and `std::make_unique`, `std::move`, references versus pointers, `const` member functions, templates, `std::function`, lambdas and captures, `std::variant`/`std::visit`, iterators, and every macro (with what it expands to). "None beyond earlier topics" only if true. **Tested:** the commands and result, including the sanitizers used.
- **HLD:** `<LabRunner unit="…">` shows, in order: a Mermaid diagram of the lab's processes and messages; the key Go code (`<Code>` imports from the lab package, not the whole package); **Go details explained** (every construct beyond earlier lessons: goroutines, channels, `select`, `sync.Mutex`, `sync.WaitGroup`, `context.Context` and cancellation, interfaces and type switches, `errors.Is`, `defer`, struct embedding, generics); the test list (which test shows the property holding, which shows it breaking); **Run it**: the exact commands to run the real multi-process version, the fault-injection steps, and the expected output; the recorded experiment results. Then the read path and write path as numbered steps, the data model, the capacity table, and the failure table (what happens when each component fails, how it is detected, what the user sees, **and which test or experiment shows it**).
- Always show the simplest alternative first, then the designed version, then the measured or computed difference.

### 8.7 Section 7: Mistake catalogue
4–8 entries (light topics: 2–3), each `### Mistake: {short name}`:
- **LLD:** the wrong C++ (a compiling copy of the reference with the mistake), its symptom (a failing test, a sanitizer report, a worse `change_cost.sh` row, or a smell), and the fix with why. Ownership mistakes (dangling references, double ownership, missing virtual destructor) must be shown with the sanitizer output that catches them.
- **HLD:** the wrong Go (a copy of the lab with the mistake: no lock, no timeout, retry without jitter, commit before processing, missing fencing check), and the failing test, race report, or experiment output that shows it. These double as kit mutants (Section 10.3).
- At least one mistake per lesson is the over-engineered version.
- If a deliberately wrong version passes every test, investigate (PLAN.md 8.5): strengthen the tests, or document it as a valid alternative.

### 8.8 Section 8: Worked examples
2 examples (light topics: 1), each an exercise with `role: worked_example`, headed `### Example {n}: {Title}`, then these level-4 headings exactly:
1. `#### Step 1: Numbers`
2. `#### Step 2: Wording → candidate structures` (at least two candidates, one of which is **the simplest thing that could work**)
3. `#### Step 3: Property check → decision`
4. `#### Step 4: Design`
5. `#### Step 5: Code or calculation` (a tested C++ unit, Go lab excerpt, or calc program)
6. `#### Step 6: Decision record`

### 8.9 Section 9: Exercise ladder
- **LLD:** one evolving C++ system (a change ladder) of 4–6 rungs (light: 3–4), at least one rung per card.
- **HLD:** the **lab ladder**: the topic's lab built in 4–6 rungs, each a kit (Section 10.3), each adding exactly one requirement, failure, or load level. Typical shape: rung 1 the basic mechanism; then a failure it must survive; then a concurrency or ordering hazard; then a load target; then a "no new structure" rung where the measurement shows the current design is enough. After the lab rungs, 2–3 `estimate` items tie the lab to prompt-sized numbers.
- Each rung has exactly one `new_force`; at least one rung per ladder has `needs_new_structure: false`.

### 8.10 Section 10: Recognition drill
6–8 items of type `recognise` (light: 6), from the reserved set. Quotas, used identically everywhere in this file:
- **"None" quota:** at least 20% of items, rounded up, have `answer.kind: none`.
- **Earlier-card quota:** at least min(3, E) items are answered by a card from an earlier topic, where E is the number of cards in earlier topics of the same track.

### 8.11 Section 11: Look-alike pairs
1–3 pairs (0 allowed for a track's first topic), as `PLAN.md` 6.11. Both sides within the same or earlier topics of the track. HLD pairs cite a lab test for each side where possible ("queue: message gone after ack (test X); log: message re-readable from offset 0 (test Y)").

### 8.12 Section 12: Self-test questions
4–6 questions with concrete counterexamples or numbers. At least one asks for the **cost** of the technique, one asks when **not** to use it, and (HLD) one asks to predict a lab result before running it.

### 8.13 Section 13: Checkpoint
One timed exercise from the reserved set (`role: checkpoint`). None for `light` topics.
| Track and phase | Checkpoint | Minutes |
|---|---|---|
| LLD L0–L1 | `build` in C++ (kit plus `rubric-lld-build-v1`) | 45 |
| LLD L2–L6 | `build` in C++ | 60 |
| LLD L7 | `mock` | 90 |
| HLD H0–H3 | `lab` rung on an unseen variant of the topic's mechanism (kit) plus a short written decision record | 45 |
| HLD H4–H7 | `deep_dive` (rubric) that must cite numbers from his own lab runs | 40 |
| HLD H8 | `mock` (full design) | 45 |
Pass rule: kit tests passing where there is a kit; rubric score at least 70% with every `critical` criterion at least 1 and an evidence note; and at least 75% of this topic's drill items correct. Record `checkpointPassedOn`.

### 8.14 Section 14: Decision map update
As `PLAN.md` 6.14. LLD groups are **symptoms**; HLD groups are **needs with numbers**. HLD entries link the lab test that demonstrates the choice.

---

## 9. Code, labs, experiments, and measurement

### 9.1 General rules
- Every unit lives under `code/{topic}/{unit-name}/`. Every expected output, measured table, or recorded experiment is produced by running it and **checked against hand-derived values or independent reasoning before it is committed**. Never commit an `expected.txt`, `measured-*.tsv`, or results file you have not understood.
- Seeds are fixed and written in the code; simulations and experiments print their seed.
- Code uses only constructs explained in earlier lessons of the same track; new constructs are explained where first used (Section 8.6).
- Comments that state a problem use a multi-line block without a leading asterisk on each line.

### 9.2 C++ (LLD): style, the test helper, and solution units
**Style:** C++23; `-Wall -Wextra -Wpedantic -Werror`; no `using namespace std;` in headers; one class per header unless the classes are tiny and inseparable; `override` on every overriding function; `final` on classes not designed for inheritance; `explicit` single-argument constructors; `const` member functions wherever possible; ownership with `std::unique_ptr` (shared ownership with `std::shared_ptr` only when the lesson explains why), non-owning access by reference or raw pointer; never `new` or `delete` outside a lesson that is explaining them; the rule of zero by default; an interface (abstract class) has a public virtual destructor.

**Flags and sanitizers: one source.** Every C++ `test.sh` (solution units, pattern units, kits) gets its flags from `code/shared/cpp/cxxflags.sh`, passing its own folder. The default is address and undefined-behaviour sanitizers with `-fno-sanitize-recover=all`, so any report fails the test. A unit or kit folder that contains a file named `sanitizer` with the word `thread` gets the thread sanitizer instead (the two cannot be combined); every L6 unit and kit has that file, and nothing else selects a sanitizer. `code/shared/cpp/cxxflags.sh` (use exactly; tested, including a kit whose lock-free mutant was caught only by the thread sanitizer):
```bash
#!/usr/bin/env bash
# Usage: cxxflags.sh <unit-or-kit-dir>
# Prints the g++ flags every C++ unit and kit uses. The one switch: a file named "sanitizer" in that folder,
# containing the word "thread", selects the thread sanitizer (concurrency units and kits, Phase L6);
# without the file, the address and undefined-behaviour sanitizers are used. The two cannot be combined.
set -euo pipefail
D="${1:?usage: cxxflags.sh <dir>}"
BASE="-std=c++23 -O1 -g -Wall -Wextra -Wpedantic -Werror -pthread -fno-sanitize-recover=all"
SAN="-fsanitize=address,undefined"
if [ -f "$D/sanitizer" ]; then
  case "$(tr -d '[:space:]' < "$D/sanitizer")" in
    thread) SAN="-fsanitize=thread" ;;
    *) echo "cxxflags.sh: $D/sanitizer must contain the word: thread" >&2; exit 2 ;;
  esac
fi
echo "$BASE $SAN"
```

**The test helper** `code/shared/cpp/check.hpp` (use exactly; tested). L0.0 explains it line by line, including what each macro expands to and why it must be a macro.
```cpp
// check.hpp: a minimal test helper used by every LLD unit and kit.
// CHECK(expr) records a failure (with file and line) if expr is false; it does not stop the test.
// CHECK_THROWS(expr) records a failure if expr does not throw.
// main() in each test file calls RUN(name) for each test function and returns report().
#pragma once
#include <cstdio>
#include <string>

namespace check {
inline int failures = 0;   // C++17 inline variable: one shared counter across all files
inline void fail(const char* file, int line, const char* text) {
    std::printf("FAIL %s:%d: %s\n", file, line, text);
    ++failures;
}
inline int report() {
    if (failures == 0) std::printf("all checks passed\n");
    return failures == 0 ? 0 : 1;
}
}  // namespace check

// The macros capture the expression's source text (#expr) and the location (__FILE__, __LINE__),
// which a normal function cannot do. That is the only reason they are macros.
#define CHECK(expr) \
    do { if (!(expr)) check::fail(__FILE__, __LINE__, #expr); } while (0)
#define CHECK_THROWS(expr) \
    do { bool threw_ = false; try { (void)(expr); } catch (...) { threw_ = true; } \
         if (!threw_) check::fail(__FILE__, __LINE__, "expected exception: " #expr); } while (0)
#define RUN(test_function) \
    do { std::printf("- %s\n", #test_function); test_function(); } while (0)
```

**A solution unit** is a folder with headers, a `tests.cpp` whose `main` calls `RUN` for each test, a `unit.yaml` (`kind: solution`, `claims: […]`), an optional `sanitizer` file, and a `test.sh`:
```bash
#!/usr/bin/env bash
# usage: bash test.sh <dir>   Builds and runs the unit's tests.cpp against the code in <dir>.
set -euo pipefail
D="$(cd "$1" && pwd)"
HERE="$(cd "$(dirname "${BASH_SOURCE[0]}")" && pwd)"
S="$HERE"; while [ "$S" != "/" ] && [ ! -f "$S/shared/cpp/check.hpp" ]; do S="$(dirname "$S")"; done
[ -f "$S/shared/cpp/check.hpp" ] || { echo "code/shared/cpp/check.hpp not found" >&2; exit 2; }
B="$(mktemp -d)"; trap 'rm -rf "$B"' EXIT
mapfile -t SRCS < <(find "$D" -maxdepth 1 -name '*.cpp' ! -name 'tests.cpp' ! -name 'main.cpp')
g++ $(bash "$S/shared/cpp/cxxflags.sh" "$HERE") -I"$S/shared/cpp" -I"$D" "$D/tests.cpp" "${SRCS[@]}" -o "$B/tests"
"$B/tests"
```
Each unit has at least 6 checks, including edge cases and one check per behaviour a mistake-catalogue entry breaks. Appendix A's `caller-unchanged` unit is a complete small example.

### 9.3 C++ pattern units (the measured comparison)
Required only in LLD `measured` topics: at least two units with different `domain`s, at least one with 3 or more scenarios.
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
domain: parking-fees
variants: [naive, patterned]
claims: ["L2.1.1"]
scenarios:
  - name: 01-weekend
    request: "Add a weekend plan at double the hourly rate."
    blast_radius:
      naive: {count: 2, behaviours: ["HOURLY", "DAILY"], where: "FeeCalculator::fee"}
      patterned: {count: 0, behaviours: [], where: "make_calculator (wiring only)"}
```
- **Blast radius of a change:** the number of **other** pre-existing behaviours whose code sits in the same function or class body as any edited line. The behaviours being changed or added do not count. Test files do not count. A composition root or registration list counts 0 if it only constructs and registers objects.
- **Overhead** and **edit cost** come from `change_cost.sh` (all files in the unit, including tests and `main.cpp`, so both variants are counted the same way).
- Each variant's `test.sh` builds and runs the same assertions; it must pass on the base and after every scenario. Patches apply cumulatively in file-name order; create them with `git diff` from a working copy, never by hand.
- At least one scenario must be one where the patterned design is **not** better (Appendix A's scenario 3, a signature change). The lesson must show it.

### 9.4 `scripts/change_cost.sh` (use exactly; tested)
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
Tested on: the Appendix A C++ unit (both variants, three scenarios); a `test.sh` that prints build output (excluded from the table); a file without a final newline; a rename (one deletion plus one addition); a failing `test.sh` (exits non-zero with the log on standard error).

### 9.5 Go (HLD): module, style, and third-party modules
- **One module** at `code/go.mod` (`module selfengine/code`, `go 1.27`), so shared packages are imported as `selfengine/code/shared/go/simnet`.
- **Never name a Go folder starting with `_` or `.`**: the `./...` pattern used by `go vet`, `go test`, and `test_design.sh` silently skips such folders and everything under them. (Revision 4 used `code/_shared`, and its tests never ran.) The D0 check below includes a test in `code/shared` to prove it runs. Directory names such as `H4.2` and `lab-quorumkv` are valid in Go import paths; package names inside them are plain identifiers (`package quorumkv`).
- **Style:** `gofmt`-clean; `go vet` clean; errors returned and wrapped with `%w`, checked with `errors.Is`/`errors.As`; every blocking call takes a `context.Context` or a timeout; no goroutine is started without a way for it to end; shared state behind a `sync.Mutex` or owned by one goroutine; tests run with `-race`.
- **Third-party modules:** the standard library is the default. To add a module (the expected ones are a PostgreSQL driver, a Redis-protocol client, and a WebSocket library), first open its repository and confirm the module path, licence, latest release, and that it is maintained; record this in `docs/design/TOOLCHAINS.md`; add it to `allowed_modules` in `design.config.yaml`; pin it in `go.mod`; run `go mod tidy` and `go mod verify`. Never add a module for something the lab is meant to teach (no consensus, rate-limit, or cache libraries).

### 9.6 Go labs and the simulated network
A lab is a folder `code/{topic}/lab-{name}/`:
```
lab-quorumkv/
├── lab.yaml            # read by <LabRunner>: title, packages, holds/breaks tests, run commands, experiments
├── quorumkv.go         # the mechanism, as a library package
├── quorumkv_test.go    # deterministic tests on simnet, run with -race
├── cmd/node/main.go    # the same mechanism as a real process (HTTP), for "Run it"
├── cmd/client/main.go
├── run.md              # exact commands: start 3 nodes, start faultproxy, kill or cut, observe
└── experiments/{name}/main.go   # optional; Section 9.7
```
```yaml
# lab.yaml
title: "Quorum key-value store"
holds: ["TestSurvivesOneReplicaDown", "TestReadMeetsAcknowledgedWrite"]
breaks: ["TestW1R1CanReturnStale"]
run: "run.md"
experiments: []
stacks: []             # server stacks the lab needs, e.g. [postgres, kafka] (Section 9.13)
```
**Rules:**
1. The mechanism is written against an interface for sending messages, so the same code runs on `simnet` in tests and over HTTP in `cmd/`.
2. Deterministic tests on `simnet` cover: the normal path; every failure named in the lesson (down node, cut link, delayed or reordered message where the lab uses the asynchronous mode); at least one test where the card's property is violated and the guarantee visibly fails (`breaks`).
3. `go test -race` passes. A lab with goroutines has at least one test that runs many of them at once.
4. `run.md` commands are run by you before merging, and their output is pasted into the lesson's "Run it" block with the date.

**`code/shared/go/simnet`** (built in D0, tested): a deterministic in-memory network. Version 1 (use exactly; tested; Appendix B uses it): synchronous calls with nodes going down and links being cut. In D0, extend it with an **asynchronous mode** for labs that need message delay and reordering (H4.1, H4.5, H5.x): messages go into a queue ordered by a virtual clock; delays come from a seeded random source; the test advances the clock explicitly (`net.Step()`, `net.RunUntilIdle()`); timers used by the mechanism (election timeouts, lease expiry) read the virtual clock through an injected `Clock` interface. Add tests showing that two runs with the same seed produce identical message orders, and a different seed produces a different order.```go
// Package simnet is a deterministic in-memory network for HLD labs.
// Nodes register a handler; Call delivers a request to a node and returns its reply,
// unless the destination is down or the two nodes are partitioned from each other.
// Tests control failures explicitly, so every run behaves the same way.
package simnet

import (
	"errors"
	"sync"
)

// ErrUnreachable is returned when the destination is down or partitioned from the caller.
var ErrUnreachable = errors.New("simnet: unreachable")

// Handler answers one request. It may be called from many goroutines at once.
type Handler func(from string, req any) any

type Net struct {
	mu       sync.Mutex
	handlers map[string]Handler
	down     map[string]bool
	cut      map[[2]string]bool // cut[{a,b}] means a and b cannot talk (stored both ways)
}

func New() *Net {
	return &Net{handlers: map[string]Handler{}, down: map[string]bool{}, cut: map[[2]string]bool{}}
}

// Register installs the handler for node id. It accepts a plain func so that packages using
// simnet do not need to import the Handler type.
func (n *Net) Register(id string, h func(from string, req any) any) {
	n.mu.Lock()
	defer n.mu.Unlock()
	n.handlers[id] = h
}

func (n *Net) SetDown(id string, down bool) {
	n.mu.Lock()
	defer n.mu.Unlock()
	n.down[id] = down
}

// Partition cuts (or, with cut=false, heals) the link between a and b in both directions.
func (n *Net) Partition(a, b string, cut bool) {
	n.mu.Lock()
	defer n.mu.Unlock()
	n.cut[[2]string{a, b}] = cut
	n.cut[[2]string{b, a}] = cut
}

// Call sends req from one node (or client) to another and returns the reply.
func (n *Net) Call(from, to string, req any) (any, error) {
	n.mu.Lock()
	h, ok := n.handlers[to]
	blocked := !ok || n.down[to] || n.down[from] || n.cut[[2]string{from, to}]
	n.mu.Unlock() // never hold the lock while the handler runs
	if blocked {
		return nil, ErrUnreachable
	}
	return h(from, req), nil
}
```
Version 1's own test (`code/shared/go/simnet/simnet_test.go`, tested; it runs under `go test ./...` from `code/`):
```go
package simnet

import (
	"errors"
	"testing"
)

func TestDownAndPartition(t *testing.T) {
	n := New()
	n.Register("A", func(from string, req any) any { return req })
	if r, err := n.Call("c", "A", 7); err != nil || r != 7 {
		t.Fatalf("got %v, %v; want 7", r, err)
	}
	n.SetDown("A", true)
	if _, err := n.Call("c", "A", 1); !errors.Is(err, ErrUnreachable) {
		t.Fatalf("down node: got %v, want ErrUnreachable", err)
	}
	n.SetDown("A", false)
	n.Partition("c", "A", true)
	if _, err := n.Call("c", "A", 1); !errors.Is(err, ErrUnreachable) {
		t.Fatalf("cut link: got %v, want ErrUnreachable", err)
	}
	n.Partition("c", "A", false)
	if _, err := n.Call("c", "A", 1); err != nil {
		t.Fatalf("healed link: got %v", err)
	}
}
```

### 9.7 Real processes: fault injection, load, Docker Compose, and experiments
Shared tools, built and tested in D0 under `code/shared/go/`:
- **`faultproxy`**: a TCP proxy placed between two processes. `go run ./shared/go/faultproxy -listen :7001 -upstream 127.0.0.1:8001 -control :9001 -seed 1`. Control by HTTP on the control port: `POST /delay?ms=200&jitter=50`, `POST /drop?p=0.1` (close new connections with probability p), `POST /blackhole` (accept and never forward, so callers hit their timeouts), `POST /heal`, `POST /close-all`. Tests against a local echo server: added delay is at least the requested delay; a blackholed call times out at the caller's deadline; `/heal` restores normal behaviour.
- **`loadgen`**: an **open-loop** HTTP load generator: requests are sent on a fixed schedule (`-rate`, `-duration`, optional seeded Poisson arrivals) whether or not earlier ones have returned, and latency is measured from each request's *scheduled* time, so a stalled server shows up as many slow requests instead of being hidden (coordinated omission). A `-closed` mode exists only for H0.1's comparison. Output: a TSV summary (sent, ok, errors, timeouts, achieved rate, p50, p90, p99, p99.9, max) and optionally the raw latencies. Tests: against a server that sleeps 10 ms, p50 is within 10–15 ms on loopback; against a server that stalls once for 1 s, open-loop p99 is much larger than closed-loop p99.
- **`capcalc`**: the estimation library used by calc programs (Section 9.8).
- **Services:** labs that need PostgreSQL, MySQL, Redis, or Kafka put `//go:build integration` on the tests that use them, read connection details from the `LAB_*` environment variables, and run on the LAN lab server with `bash scripts/labserver.sh integration <stacks> -- <packages>` (Section 9.13).
- **Experiments:** a Go `main` package under `lab-*/experiments/{name}/`. It prints the machine (CPU model if available, `runtime.NumCPU()`, `runtime.GOOS`, `runtime.GOARCH`, `runtime.Version()`), the seed, a TSV of results, and one `PASS shape: …` or `FAIL shape: …` line per shape check, and exits non-zero if any check fails. It has a `-quick` flag (small and fast, with generous thresholds) used in CI, and a full mode you run **on the lab server** before merging (`bash scripts/labserver.sh experiment <package>`); commit the full-mode output under `experiments/{name}/results/` and describe it in `src/data/experiments/` (Section 7.6). **Lessons state absolute numbers only as "on this machine"; claims are about shapes** ("p99 grows at least 3 times between 50% and 90% load"), which the program checks on any machine.

### 9.8 Go claim and calc programs
- **Claim program** (`code/{topic}/claim-{n}/main.go` + `expected.txt`): checks a claim exhaustively over small cases (kind `proved`) or by seeded simulation (kind `simulated`) and prints one labelled line per case; at most 80 lines. `expected.txt` is derived from the proof **first** and compared with the program's output; a mismatch means the claim, proof, or program is wrong. Appendix B has a complete example.
- **Calc program** (`code/{topic}/calc-{name}/main.go` + `expected.txt`): uses `capcalc` and `code/shared/constants.json` (generated from `src/data/constants.yaml` by `scripts/constants_export.mjs`, run by `npm run build`, which fails if the committed JSON differs from a fresh export). It prints `key = value unit` lines, one per quantity, with formulas as comments, rounding only in the printed value.

### 9.9 `scripts/test_design.sh` (use exactly; tested)
Runs `gofmt`, `go vet`, and `go test -race` over the Go module; every Go program that has an `expected.txt`; every C++ solution unit; and every pattern unit.
```bash
#!/usr/bin/env bash
# Usage: test_design.sh [code-root]   (default: code)
# Runs every design code unit under the root:
#   1. Go module (code/go.mod): gofmt check, go vet, go test -race on every package (HLD labs, shared packages)
#   2. Go claim/calc units: folders with main.go and expected.txt; `go run` output must equal expected.txt
#   3. C++ solution units: unit.yaml with "kind: solution"; `bash test.sh <dir>` must pass
#   4. Pattern units: unit.yaml with "kind: pattern"; change_cost.sh output must equal measured-<variant>.tsv
set -euo pipefail
ROOT="$(cd "${1:-code}" && pwd)"
HERE="$(cd "$(dirname "$0")" && pwd)"
fail=0

if [ -f "$ROOT/go.mod" ]; then
  unformatted="$(cd "$ROOT" && gofmt -l .)"
  [ -z "$unformatted" ] || { echo "FAIL (gofmt): $unformatted"; fail=1; }
  log="$(mktemp)"
  if ! (cd "$ROOT" && go vet ./... && go test -race -count=1 ./...) > "$log" 2>&1; then
    echo "FAIL (go vet / go test):"; grep -E -- '^(--- FAIL|FAIL|panic|WARNING: DATA RACE)|\.go:[0-9]+' "$log" | head -40; fail=1
  fi
  rm -f "$log"
  while IFS= read -r m; do
    d="$(dirname "$m")"
    [ -f "$d/expected.txt" ] || continue
    if ! (cd "$ROOT" && go run "./${d#"$ROOT"/}") | diff -q - "$d/expected.txt" > /dev/null; then
      echo "FAIL (output differs from expected.txt): $d"; fail=1
    fi
  done < <(find "$ROOT" -name main.go | sort)
fi

while IFS= read -r y; do
  d="$(dirname "$y")"
  if grep -q '^kind: solution' "$y"; then
    log="$(mktemp)"
    bash "$d/test.sh" "$d" > "$log" 2>&1 || { echo "FAIL (tests): $d"; tail -20 "$log"; fail=1; }
    rm -f "$log"
  elif grep -q '^kind: pattern' "$y"; then
    variants="$(sed -n 's/^variants: \[\(.*\)\]/\1/p' "$y" | tr -d ' ' | tr ',' ' ')"
    [ -n "$variants" ] || { echo "MISSING variants in $y"; fail=1; continue; }
    for v in $variants; do
      out="$(mktemp)"; err="$(mktemp)"
      if ! bash "$HERE/change_cost.sh" "$d/$v" > "$out" 2> "$err"; then echo "FAIL (change_cost): $d/$v"; cat "$err"; fail=1
      elif ! diff -q "$out" "$d/measured-$v.tsv" > /dev/null; then echo "FAIL (measured-$v.tsv is out of date): $d"; fail=1; fi
      rm -f "$out" "$err"
    done
  fi
done < <(find "$ROOT" -name unit.yaml | sort)

[ "$fail" -eq 0 ] && echo "All design code units passed" || exit 1
```
Tested on: a clean tree (C++ solution unit, C++ pattern unit, Go claim program, Go lab); a broken C++ unit; a wrong `expected.txt`; and a broken Go lab (the failing test's name and message are printed).

CI also runs `go test -tags experiment -run Quick ./...` (experiment quick modes wrapped as tests). Integration tests run on the LAN lab server, not in GitHub-hosted CI (Section 9.13).

### 9.10 `scripts/exercise_kit_check.sh` (use exactly; tested)
Language-neutral: each kit's own `test.sh` builds and tests. Checks that tests fail on the starter, pass on the reference, and fail on every mutant.
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
#   <exercises-root>/<rel>/needs_docker  optional marker: the kit's tests start containers. Such kits are
#                                        skipped (and reported) when Docker is unavailable, unless REQUIRE_DOCKER=1.
# Checks: tests FAIL on the starter, PASS on the reference, and FAIL on every mutant; enough mutants exist.
set -euo pipefail
EX="$(cd "${1:-exercises}" && pwd)"; REF="$(cd "${2:-reference}" && pwd)"
MUT="${3:-reference-mutants}"; mkdir -p "$MUT"; MUT="$(cd "$MUT" && pwd)"
fail=0
docker_ok=0; docker info > /dev/null 2>&1 && docker_ok=1
while IFS= read -r t; do
  kit="$(dirname "$t")"; rel="${kit#"$EX"/}"
  ref="$REF/$rel"
  if [ -f "$kit/needs_docker" ] && [ "$docker_ok" -eq 0 ]; then
    if [ "${REQUIRE_DOCKER:-0}" = "1" ]; then echo "FAIL: Docker unavailable for $rel"; fail=1; else echo "SKIPPED (Docker unavailable): $rel"; fi
    continue
  fi
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
Tested on: a Go kit (Appendix C) whose three mutants are caught (one only by the race detector); a C++ thread-sanitizer kit (a counter shared by 8 threads) whose lock-free mutant is caught only by the thread sanitizer; a reference that fails; a starter that passes; a mutant that passes; too few mutants; a ladder rung with `min_mutants`; a Docker kit with and without `REQUIRE_DOCKER=1` when Docker is not available.

**Change and lab ladders:** each rung is its own kit (`exercises/H4.2/lab/rung-k/`). The starter of rung k is the reference of rung k − 1, and rung k's tests include all earlier rungs' tests plus the new ones, so the check proves each rung adds tested behaviour. Rungs set `min_mutants` to 2.

### 9.11 `scripts/new_attempt.sh` (use exactly; tested)
How Saurabh starts an exercise: it copies the kit's starter (or his own previous rung) into `work/` (gitignored) and prints the test command.
```bash
#!/usr/bin/env bash
# Usage: new_attempt.sh <kit-path> [start-from-dir]
#   e.g. new_attempt.sh H5.6/lab/rung-1
#        new_attempt.sh H4.2/lab/rung-3 work/H4.2/lab/rung-2     (continue a ladder from your own previous rung)
# Copies the kit's starter (or start-from-dir) into work/<kit-path>/ (work/ is gitignored) and prints the test command.
set -euo pipefail
K="${1:?usage: new_attempt.sh <kit-path> [start-from-dir]}"
ROOT="$(cd "$(dirname "$0")/.." && pwd)"
SRC="${2:-$ROOT/exercises/$K/starter}"
DST="$ROOT/work/$K"
[ -f "$ROOT/exercises/$K/test.sh" ] || { echo "no such kit: exercises/$K" >&2; exit 1; }
[ -d "$SRC" ] || { echo "no such folder: $SRC" >&2; exit 1; }
[ -e "$DST" ] && { echo "already exists: work/$K (delete it to start over)" >&2; exit 1; }
mkdir -p "$(dirname "$DST")"
cp -r "$SRC" "$DST"
echo "Edit work/$K, then run:  bash exercises/$K/test.sh work/$K"
```

### 9.12 What is not tested by code, and how it is checked instead
- Diagrams: rendered at build time (D10) and checked against the code by eye in self-review.
- Facts about real systems (`cited` claims): checked by opening the source.
- Absolute performance numbers: recorded with the machine; only shapes are checked.
- Rubrics: checked by calibration (Section 10.7).


### 9.13 The LAN lab server
Saurabh has a server on his local network (LAN) with Docker, and it can run PostgreSQL, MySQL, Redis, Kafka, and WebSocket services. **All Docker Compose stacks, integration tests, kit runs that need services, multi-process lab runs, and full experiments run on that server**, not on the machine where you edit code. Your own machine (or the CI runner) still runs the fast checks: C++ units, `go vet`, `go test -race` on `simnet`, kits without services, and the site build.

**Configuration.** `.env.labserver` (gitignored; copied from the committed `.env.labserver.example`):
```bash
# Copy to .env.labserver (gitignored) and fill in. It is copied to the server by `labserver.sh sync`.
LABSERVER_HOST=saurabh@192.168.1.50
LABSERVER_DIR=/home/saurabh/self-engine
# Bind address for lab service ports. 127.0.0.1 = only processes on the server can connect (default).
# Set to the server's LAN address only for experiments that run a client on another LAN machine.
LAB_BIND=127.0.0.1
LAB_DB_PASSWORD=change-me
# Pinned at D0 after checking each image's official page: name:version@sha256:digest
POSTGRES_IMAGE=postgres:VERSION@sha256:DIGEST
MYSQL_IMAGE=mysql:VERSION@sha256:DIGEST
REDIS_IMAGE=redis:VERSION@sha256:DIGEST
KAFKA_IMAGE=apache/kafka:VERSION@sha256:DIGEST
KAFKA_ADVERTISED_HOST=localhost
# Connection strings read by integration tests (go test -tags integration)
LAB_POSTGRES_DSN=postgres://lab:change-me@127.0.0.1:5432/lab?sslmode=disable
LAB_MYSQL_DSN=lab:change-me@tcp(127.0.0.1:3306)/lab
LAB_REDIS_ADDR=127.0.0.1:6379
LAB_KAFKA_BROKERS=127.0.0.1:9092
```
`labserver.sh sync` copies this file to the server too, because the stacks and the integration tests read it there. Choose a **dedicated** folder for `LABSERVER_DIR` (for example `/home/saurabh/self-engine-mirror`): `sync` replaces its contents.

**Reaching the server.** You need SSH access from where you run (key-based, `BatchMode`, no password prompts). At D0, run `bash scripts/labserver.sh init` once (it creates `LABSERVER_DIR` with a `.labserver-mirror` marker, and refuses `/`, home and system folders, folders that contain the home folder, and non-empty folders that are not already mirrors), then `bash scripts/labserver.sh check`, and record its output in `docs/design/TOOLCHAINS.md`. **If you cannot reach the server** (for example, you run in a cloud environment outside his network), do not pretend: put "Run `bash scripts/labserver.sh check` and paste the output" under "Questions for Saurabh", set gate "Lab server reachable" to `waiting`, and do the server-dependent steps as a list of exact commands he can run, whose outputs he pastes into `FEEDBACK.md`.

**Server prerequisites** (checked by `labserver.sh check`): Go of the version in `code/go.mod`, g++ 13 or newer, Docker with the Compose plugin and a reachable daemon, git, tar, and enough memory for the largest stack (about 4 GB free for PostgreSQL, MySQL, Redis, and Kafka together).

**`scripts/labserver.sh`** (use exactly; tested in its `local` mode, where `LABSERVER_HOST=local` runs everything on the current machine, and with a stand-in `docker` command that records calls; the SSH path differs only in wrapping the same commands in `ssh`, and was not tested). What the tests covered: `sync` and `exec` refuse a folder without the marker; `init` refuses `/`, `/home`, the home folder, a parent of the home folder, and a non-empty non-mirror folder (whose files were left untouched); after `sync`, a stale file is gone and a `results` file three folders deep is kept; `integration postgres kafka` with PostgreSQL already running starts and stops only Kafka; a failing integration test returns non-zero and still stops the stacks it started.
```bash
#!/usr/bin/env bash
# Run lab work on Saurabh's LAN server. Configuration comes from .env.labserver (gitignored):
#   LABSERVER_HOST   ssh destination, e.g. saurabh@192.168.1.50, or "local" to run on this machine
#   LABSERVER_DIR    folder on the server that mirrors this repository, e.g. /home/saurabh/self-engine-mirror
# Commands:
#   init                       create LABSERVER_DIR with the marker file .labserver-mirror (only if it is missing or empty)
#   check                      print the server's tool versions and resources
#   sync                       replace the mirror with the working tree; every folder named "results" is kept
#   up <stack>... / down <stack>...   start or stop stacks; each stack is its own compose project "se-<stack>"
#   integration <stack>... -- <go packages>   sync, start the stacks that are not running, run
#                              go test -tags integration, then stop only the stacks this command started
#   kit <kit-path> <solution-dir>             sync, run the kit's test.sh on the server
#   experiment <go package> [args]            sync, run an experiment in full mode, copy its result file back
#   exec <command>                            run a command in LABSERVER_DIR
set -euo pipefail
ROOT="$(cd "$(dirname "$0")/.." && pwd)"
[ -f "$ROOT/.env.labserver" ] && . "$ROOT/.env.labserver"
HOST="${LABSERVER_HOST:?set LABSERVER_HOST in .env.labserver}"
DIR="${LABSERVER_DIR:?set LABSERVER_DIR in .env.labserver}"
MARK=".labserver-mirror"
RES="/tmp/.labserver-results-$(printf %s "$DIR" | cksum | cut -d" " -f1).tgz"   # results saved here during a sync

remote() {   # run a shell command inside DIR on the server (DIR must already exist)
  if [ "$HOST" = "local" ]; then (cd "$DIR" && bash -c "$1")
  else ssh -o BatchMode=yes "$HOST" "cd '$DIR' && bash -c $(printf '%q' "$1")"; fi
}
remote_raw() {   # run a shell command on the server, outside DIR
  if [ "$HOST" = "local" ]; then bash -c "$1"
  else ssh -o BatchMode=yes "$HOST" "bash -c $(printf '%q' "$1")"; fi
}
require_mirror() {   # refuse to touch a folder that init did not create
  remote_raw "test -f '$DIR/$MARK'" || {
    echo "refusing: $DIR has no $MARK file. Run 'labserver.sh init' (it only initialises a missing or empty folder)." >&2; exit 1; }
}
is_running() { remote "docker compose -p se-$1 ps -q 2>/dev/null | grep -q ."; }
start() { remote "docker compose -p se-$1 -f labserver/stacks/$1.yaml --env-file .env.labserver up -d --wait"; }
stop()  { remote "docker compose -p se-$1 -f labserver/stacks/$1.yaml --env-file .env.labserver down -v"; }

cmd="${1:-}"; shift || true
case "$cmd" in
  init)
    remote_raw "d=\$(realpath -m '$DIR'); h=\$(realpath -m ~)
                case \"\$d\" in /|/home|/root|/tmp|/usr|/usr/*|/etc|/etc/*|/var|/opt|\"\$h\") echo \"refusing: \$d is not a dedicated folder\" >&2; exit 1 ;; esac
                case \"\$h/\" in \"\$d\"/*) echo \"refusing: \$d contains your home folder\" >&2; exit 1 ;; esac
                if [ -e \"\$d\" ] && [ -n \"\$(ls -A \"\$d\")\" ] && [ ! -f \"\$d/$MARK\" ]; then
                  echo \"refusing: \$d exists, is not empty, and is not a mirror\" >&2; exit 1; fi
                mkdir -p \"\$d\" && touch \"\$d/$MARK\" && echo \"initialised \$d\"" ;;
  check)
    remote_raw 'v() { printf "%-15s " "$1"; shift; "$@" 2>&1 | head -1 || echo MISSING; }
            v go go version; v g++ g++ --version; v docker docker --version; v compose docker compose version
            v git git --version; v tar tar --version
            docker info >/dev/null 2>&1 && echo "docker daemon: reachable" || echo "docker daemon: NOT reachable"
            echo "cpus: $(getconf _NPROCESSORS_ONLN)"; free -h 2>/dev/null | sed -n 2p || true; df -h ~ | tail -1' ;;
  sync)
    require_mirror
    # Save every "results" folder, replace everything else with the working tree, then restore the results.
    remote "find . -type d -name results -prune -print0 | tar --null -T - -czf '$RES'
            find . -mindepth 1 -maxdepth 1 ! -name '$MARK' -exec rm -rf {} +"
    tar -C "$ROOT" --exclude=.git --exclude=node_modules --exclude=dist --exclude='.build' --exclude='results' -czf - . \
      | remote "tar -xzf - && touch '$MARK'"
    remote "tar -xzf '$RES' && rm -f '$RES'"
    echo "synced to $HOST:$DIR" ;;
  up)   require_mirror; for s in "$@"; do start "$s"; done ;;
  down) require_mirror; for s in "$@"; do stop "$s"; done ;;
  integration)
    stacks=(); while [ $# -gt 0 ] && [ "$1" != "--" ]; do stacks+=("$1"); shift; done; shift || true
    pkgs="${*:-./...}"
    "$0" sync
    started=()
    for s in "${stacks[@]}"; do
      if is_running "$s"; then echo "stack $s already running; leaving it as it is"
      else start "$s"; started+=("$s"); fi
    done
    rc=0; remote "cd code && set -a && . ../.env.labserver && set +a && go test -tags integration -race -count=1 $pkgs" || rc=$?
    for s in "${started[@]}"; do stop "$s"; done
    exit $rc ;;
  kit)
    k="${1:?kit path}"; sol="${2:?solution dir, relative to the repository}"
    "$0" sync
    remote "bash exercises/$k/test.sh $sol" ;;
  experiment)
    pkg="${1:?go package, e.g. ./H0.4/lab-queue/experiments/sweep}"; shift
    "$0" sync
    out="$(date +%F)-labserver.txt"
    remote "set -o pipefail; mkdir -p code/$pkg/results && cd code && go run $pkg $* | tee $pkg/results/$out"
    mkdir -p "$ROOT/code/$pkg/results"
    remote "tar -C code/$pkg/results -czf - $out" | tar -C "$ROOT/code/$pkg/results" -xzf -
    echo "results copied to code/$pkg/results/$out" ;;
  exec) require_mirror; remote "$*" ;;
  *) sed -n '2,17p' "$0"; exit 2 ;;
esac
```

**Stacks** live in `labserver/stacks/{postgres,mysql,redis,kafka}.yaml`. Each pins its image through `.env.labserver`, binds its port to `LAB_BIND` (default `127.0.0.1`, so only processes on the server can connect), sets a memory limit, and has a health check so `up --wait` returns only when the service is ready. All four files were validated with `docker compose config`. The PostgreSQL stack:
```yaml
# PostgreSQL for labs. Image pinned in .env.labserver (version and digest checked at D0).
services:
  postgres:
    image: ${POSTGRES_IMAGE:?set POSTGRES_IMAGE in .env.labserver}
    environment:
      POSTGRES_USER: lab
      POSTGRES_PASSWORD: ${LAB_DB_PASSWORD:?set LAB_DB_PASSWORD in .env.labserver}
      POSTGRES_DB: lab
    ports: ["${LAB_BIND:-127.0.0.1}:5432:5432"]
    mem_limit: 1g
    healthcheck:
      test: ["CMD-SHELL", "pg_isready -U lab -d lab"]
      interval: 2s
      timeout: 2s
      retries: 30
```
The Kafka stack runs one broker in KRaft mode (no ZooKeeper). Its environment variable names follow the official image's convention; **confirm them against the image's documentation at D0**, start it, and create and consume a topic once before any lab depends on it.

**Rules for the server:**
1. **Isolation:** each stack is its own Compose project, `se-<stack>` (`se-postgres`, `se-kafka`, …), so a stack started by `up` and the same stack requested by `integration` are the same project, never two projects fighting for one port. `integration` starts only stacks that are not running and stops only those it started; `down -v` removes their containers and volumes, so a stack started by `integration` starts from an empty database. A stack Saurabh started with `up` for a lab session keeps its data until he runs `down`.
2. **Nothing is exposed beyond the LAN.** Do not open router ports. Use `LAB_BIND` set to the server's LAN address only for experiments that run a client on another LAN machine (for example, H0.5's real-network latency, or `loadgen` on the laptop against a service on the server), and set it back afterwards.
3. **Secrets** stay in `.env.labserver` and never in committed files or logs.
4. **Results:** every experiment's full run happens on the server; `sync` never deletes any folder named `results`; the output file is named `{date}-labserver.txt` and records the server's machine description, so numbers from different days are comparable. Add the git commit (`git rev-parse --short HEAD`) to the experiment record (Section 7.6).
5. **Saurabh's own work** runs the same way: `bash scripts/labserver.sh kit {kit-path} work/{kit-path}` runs a kit on the server, and `bash scripts/labserver.sh up postgres` gives him a database for a lab session (he stops it with `down`).
6. **Site hosting:** the same server may host the static site (PLAN.md 14.2). Keep lab stacks on different ports and in their own Compose projects, and never run `down` on a project you did not start.

**CI and the server.** GitHub-hosted CI cannot reach the LAN, so the integration job does not run there. Before every merge you run `bash scripts/labserver.sh integration <stacks> -- <packages>` for each topic that has integration tests, and paste the summary into the merge message. Optionally, if the repository is **private**, Saurabh may install a GitHub Actions self-hosted runner on the server with the label `labserver` and the integration job runs there on pushes to his branches. Do not set this up for a public repository (code from pull requests by others would run on his machine); ask him first in either case.

---

## 10. Exercise bank and reference solutions

Design has no online judge, so the exercises are authored here, and each ships with its own checker.

### 10.1 Types and allowed checkers
| Track | Type | What the learner does | `checkers` (exactly these) |
|---|---|---|---|
| LLD | `recognise` | Reads a requirement set; names the force and the card, or "none" | `[]` (the `answer` is revealed) |
| LLD | `refactor` | Fixes a smelly C++ program (at most 80 lines) without breaking its tests | `[kit]` |
| LLD | `build` | Implements a small system in C++ against a header that declares the public interface | `[kit]`, or `[kit, rubric]` as a checkpoint |
| LLD | `change_ladder` | One rung of an evolving C++ system | `[kit]` |
| LLD | `mock` | Timed build from a vague prompt | `[kit, rubric]` |
| HLD | `recognise` | Reads a prompt with numbers; names the need and component, or "none" | `[]` |
| HLD | `estimate` | Computes QPS, storage, bandwidth, machines | `[numeric]` (one or more) |
| HLD | `lab` | One rung of the topic's Go lab | `[kit]`; a rung that ends in a measurement adds `numeric` (his measured value against the recorded range) |
| HLD | `deep_dive` | Designs one subsystem, citing his own lab results | `[rubric]` or `[numeric…, rubric]` |
| HLD | `scale_ladder` | One rung of a prompt scaled up (H8) | `[numeric…]`; the last rung adds `rubric` |
| HLD | `failure` | Given a design and a failure, predicts behaviour, then checks by running the lab with that fault | `[rubric]` |
| HLD | `mock` | Timed full design | `[rubric]` or `[numeric…, rubric]` |

### 10.2 Ladders: one evolving scenario
- **Change ladder (LLD).** One C++ system that grows by one requirement per rung, each rung a kit. Saurabh commits after each rung (tags `rung-1`, `rung-2`, …) and runs `git diff --numstat rung-1 rung-2` to see his own edit cost. The last rung's reference says at which rung the patterned approach started to pay, and why.
- **Lab ladder (HLD H0–H7).** The topic's lab, built in rungs (Section 8.9). Each rung has a kit with deterministic `simnet` tests and, where relevant, a short **run step** (start the real processes, inject the named fault with `faultproxy`, observe the stated behaviour) whose outcome he records in the attempt log.
- **Scale ladder (HLD H8).** One end-to-end system scaled up: rung 1 is the smallest honest version; each later rung multiplies one number by about 10 or adds one constraint; each rung has numeric answers and the **threshold** at which the previous design stops being enough, taken from a calc program **and checked against a `loadgen` run of his system**. Rungs where the previous design is still enough are required.

### 10.3 Exercise kits
```
exercises/{kit-path}/
├── README.md        # the prompt (own words), the public interface, the acceptance tests in words, how to run
├── test.sh          # bash test.sh <solution-dir>; exit 0 means all tests pass
├── starter/         # compiles; every function throws std::logic_error("not implemented") (C++) or panics "not implemented" (Go)
├── tests/           # C++: tests.cpp using check.hpp. Go: *_test.go in the solution's package
├── min_mutants      # optional; default 3 (ladder rungs: 2)
└── needs_docker     # optional marker for kits whose tests need server stacks; run them with labserver.sh kit
reference/{kit-path}/                   # reference solution (+ wrong-1.md … wrong-3.md for rubric calibration)
reference-mutants/{kit-path}/{m1,m2,m3}/  # deliberately wrong solutions
```
- `README.md` describes behaviour and the public interface (a C++ header or a Go package API), never the internal design.
- Tests check behaviour only, through the public interface, so any sound design passes. A test that only one design can pass is a bug in the kit.
- Go kits run `go vet` and `go test -race` in a throwaway module (Appendix C). C++ kits compile with the flags and sanitizers of Section 9.2.
- `bash scripts/exercise_kit_check.sh` must pass; run it on the lab server (`bash scripts/labserver.sh exec "REQUIRE_DOCKER=1 bash scripts/exercise_kit_check.sh"`) so kits marked `needs_docker` are included.
- Saurabh starts with `bash scripts/new_attempt.sh {kit-path}` and works in `work/` (Section 9.11). Reference folders are in the repository because it is his own; the site shows them only after an attempt is logged.

### 10.4 Reference solutions
`SOLUTION.md`: the design in 10–25 lines; a Mermaid diagram; the **decision record**; at least one alternative with *when it is better*; the three most common wrong approaches with why each fails. Plus tested code. Lab references add the "Run it" transcript and, where a rung measures something, the recorded result and machine.

### 10.5 Clarifying questions
Every `build`, first `lab` rung, `deep_dive`, `scale_ladder`, and `mock` exercise has a `clarifying` list of at least 4 entries, at least 2 marked `critical`. On the site the learner types his questions first, then reveals the list and ticks the critical ones he asked.

### 10.6 Sources
- **LLD:** the Gang of Four book (cite by pattern name and intent), Fowler's refactoring catalogue, cppreference.com for every standard-library facility a lesson uses, the C++ Core Guidelines, and the Liskov and Liskov–Wing papers. Open each before citing.
- **HLD:** primary sources for facts about real systems. Candidate anchors, **to be verified** (open each; record exact title, URL, and `accessed` date; drop any you cannot open): Dynamo (2007); Bigtable (2006); the Google File System (2003); MapReduce (2004); Spanner (2012); the Raft paper (2014), whose figure of server rules is the specification for the H4.5 lab subset (cite it; do not copy it); the Kafka paper (2011); "Scaling Memcache at Facebook" (2013); TAO (2013); Lamport (1978); Karger et al. (1997); Flajolet et al. on HyperLogLog (2007); Shapiro et al. on CRDTs (2011); the Google SRE book; the Go documentation (go.dev) for every standard-library package used; the PostgreSQL documentation for isolation levels and locking.
- Never copy figures or code. Never state a number about a real product from memory.
- Common interview prompts are common knowledge; write every prompt in your own words.

### 10.7 Rubrics
`src/data/rubrics.yaml` defines exactly these rubrics (extend only with Saurabh's approval):

| id | Used by | Criteria (weight; ★ = critical) |
|---|---|---|
| `rubric-lld-build-v1` | LLD `build` checkpoints, `mock` | requirements and assumptions (10); entities and responsibilities (20 ★); extensibility under the stated changes (20 ★); correctness: kit tests and sanitizers pass (20 ★); pattern use justified, no over-engineering (10); ownership and concurrency safety (10; ★ when the prompt involves concurrency); readability (10) |
| `rubric-hld-mock-v1` | HLD `mock` | requirements and scope (10); estimation (15 ★); API and data model (15); high-level design (20 ★); deep dive (20 ★); bottlenecks and failure (10); trade-offs and decision record (10) |
| `rubric-hld-deep-dive-v1` | HLD `deep_dive`, last `scale_ladder` rung | requirements and the critical questions (15); numbers, including at least one from his own lab run (20 ★); mechanism and data (30 ★); failure behaviour (20 ★); trade-offs and decision record (15) |
| `rubric-hld-failure-v1` | HLD `failure` | prediction of behaviour, written before running (40 ★); detection (20); mitigation with its cost (40 ★) |

Every criterion has anchors 0, 1, 2 describing **observable evidence**, for example:
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
```
Rules:
- Weights sum to 100. Score = Σ weight × (score ÷ 2). A one-line evidence note is recorded for every criterion; notes are required on critical criteria for a pass.
- **Numeric checkers** use `factor` (default 2): pass if answer ÷ reference is between 1/factor and factor. For a measured value on his machine, the reference is the recorded run and the factor is at least 3, because machines differ.
- **Calibration** (before a rubric is first used by an exercise): score the reference and three full wrong answers (`wrong-1.md` … `wrong-3.md`). The reference must score at least 90% and each wrong answer below 60%. If your environment can start a separate agent, have it score them seeing only the rubric and the answers; otherwise record `calibration: self` and Saurabh spot-checks one calibrated exercise per phase at the phase gate.
- **Export for review** lets Saurabh paste his answer and rubric into a Claude conversation for a second reading. It is an option, not a gate.

### 10.8 Practice and reserved sets
The **practice set** (`role: ladder | worked_example`) is visible. The **reserved set** (`drill | checkpoint | review | exam`) stays unseen until used. Reserved items are never written into page HTML: the build emits them to `/data/reserved/{topic}.json` (Section 11.7), and only the Drill, Checkpoint, Review, and Exam components fetch them, on demand. Reviews use **transfer prompts** (a different domain, the same card). Reserved lab kits (HLD checkpoints) live under `exercises/` like the others; the site shows their path only after the checkpoint starts.

### 10.9 Counts per topic
| Item | LLD `measured` / `standard` | LLD `light` | HLD |
|---|---|---|---|
| Cards | 1–4 | 1–2 | 1–4 |
| Ladder | change ladder, 4–6 rungs | 3–4 rungs | lab ladder, 4–6 rungs, plus 2–3 `estimate` items |
| Worked examples | 2 | 1 | 2 |
| Recognition drill | 6–8 | 6 | 6–8 |
| Checkpoint | 1 | none | 1 |
| Review sets | 2 (each 3 items: ≥ 1 recognise, ≥ 1 short build or estimate) | 1 | 2 (each 3 items: ≥ 1 recognise, ≥ 1 lab twist or estimate) |
| Self-test | 4–6 | 3–4 | 4–6 |
| Look-alike pairs | 1–3 (0 allowed for the track's first topic) | 0–2 | 1–3 |
| Phase exam | 6–8 items per phase, mixed, topics hidden | | |

Expected totals: about 1 900 items across both tracks, of which about two thirds are short recognition or estimate items; about 50 HLD labs (230 rung kits) and about 47 LLD ladders (220 rung kits). Record actual totals in the D0 inventory.

### 10.10 Exercise inventory (milestone D0)
Before any lesson is written, produce `src/data/exercises/INVENTORY.yaml` and `notes/design/INVENTORY.md`. For every topic: planned card ids and names; the ladder or lab rungs (each rung's `new_force` and `needs_new_structure`); for HLD, each rung's tests in one line ("kill one replica: Put and Get still succeed") and the experiment, if any; one-line drill stubs (intended card as `{topic, card}`, or "none"); the checkpoint; review stubs. No solutions or kits yet. A script checks: every card named in a stub is planned in the same or an earlier topic of the same track; the quotas of Section 8.10 hold; no ladder scenario is reused within a track. This is Saurabh's chance to see the whole road ahead (gate in Section 14).

---

## 11. Site additions, including every component and page

Everything inherits `PLAN.md` Section 10 (storage module, try/catch rule, look and feel).

### 11.1 Navigation
The sidebar adds **LLD** (Phases L0–L7; each: intro, lessons, exam) and **HLD** (Phases H0–H8), plus **Labs** (`/hld/labs`). The dashboard gains a track filter and shows the current topic per track, due reviews across tracks, the three cards with the most recognition misses, and the next lab rung. `cp:v1:settings` becomes `{ currentTopic: { cp, lld, hld } }`; migrate the old shape when reading it.

### 11.2 Exercise page behaviour
Each exercise page shows: the prompt; the **Ask first** box; for kits, **how to start** (`bash scripts/new_attempt.sh {kit-path}`) and **how to test** (`bash exercises/{kit-path}/test.sh work/{kit-path}`), with copy buttons; for lab rungs, the **run step** with the exact commands; a timer (required for checkpoints, exams, and mocks, with phases as shares of the total: HLD full design 10/10/20/25/25/10% for requirements, estimation, API and data, high-level, deep dive, bottlenecks; HLD deep dive 15/60/25% for requirements, mechanism, failure and trade-offs; LLD build or mock 10/20/55/15% for clarify, entities and interfaces, code, extend and test); three hints (practice set only) with the struggle-budget reminder (20 minutes in L0–L1 and H0–H1, 30 after); an answer area; **rubric scoring** where there is a rubric; a **numeric answer** box where there is a numeric checker; **"Tests pass" tick** for kits (he runs the tests locally; the site records his tick and the date); **reference reveal** after an attempt is saved; an attempt log (date, minutes, score, hints, mistake category, note); and **Export for review**.

Mistake categories for design: *Missed a requirement*, *Wrong structure*, *Over-engineered*, *Under-engineered*, *Numbers wrong*, *Missed a failure case*, *Concurrency or ownership bug*, *Implementation bug*.

Storage: `cp:v1:design-attempts` = `{ [globalExerciseId]: [ { date, minutes, hints, testsPassed, measured, scores: { [criterionId]: { score, evidence } }, mistake, note } ] }`; `cp:v1:numbers` for flashcards. Both are included in export and import.

### 11.3 Numeric answers
For `estimate` items, scale-ladder rungs, and measured lab rungs: an input for the number and a unit as free text. The check uses the exercise's `factor` (Section 10.7), then shows the reference derivation or recorded run, and both numbers.

### 11.4 Number flashcards (HLD)
From `constants.yaml`, plus quantities Saurabh measured in labs (his own loopback round trip, disk sync time, and so on, entered once on the Numbers page). Log-scale slider guess; correct within one order of magnitude; spaced 1, 3, 7, 21 days.

### 11.5 Handbooks
- **LLD Pattern Handbook** (`/lld/handbook`): by symptom (from decision maps), by topic, "as of topic X", flashcards.
- **HLD Component Handbook** (`/hld/handbook`): by need and number, by topic, "as of topic X", flashcards; each entry links to its lab test that shows the guarantee holding and breaking.
- **Numbers sheet** (`/hld/numbers`): constants with sources and caveats, his own measured values, and the formulas used in lessons.

### 11.6 Reviews
Two review sets per topic at 3 and 14 days after `checkpointPassedOn` (light topics: one set at 14 days). HLD review items include re-running a lab with a twist (a different fault or load).

### 11.7 Every component and page, and where it comes from
Nothing here is downloaded from elsewhere: **you build every component and page in this repository**. Components marked *extend* already exist from `PLAN.md` (CP track); change them so they work for all three tracks without breaking CP pages. Components marked *new* go in `src/components/design/`. Each reads its data at build time from the files named (through `src/lib/data.ts`) unless it says "client".

| File | New or extend | Reads | Behaviour |
|---|---|---|---|
| `src/components/TopicHeader.astro` | extend | `curriculum.yaml`, topic `uses` | Title, track and phase, "Builds on" from `uses`; for HLD shows the lab's one-line description and infra |
| `src/components/WhatYouNeed.astro` | extend | topic `uses` | Same list as the header, as Section 2 of the lesson |
| `src/components/Cards.astro` | extend | topic `cards` | Renders card fields in the order of PLAN.md 6.5 (as revised); LLD trade-off tables; HLD capacity tables and links to the lab's `holds` and `breaks` tests |
| `src/components/Drill.tsx` | extend | client: `/data/reserved/{topic}.json` | Adds "none" as an answer; requires a one-sentence property before reveal; records `shown` times |
| `src/components/Checkpoint.tsx` | extend | client: `/data/reserved/{topic}.json`, `rubrics.yaml` (built into the bundle) | Kit checkpoints show start and test commands after start; timer with phases; rubric scoring; pass rule of Section 8.13 |
| `src/components/LookalikePairs.astro`, `SelfTest.astro`, `DecisionMapUpdate.astro` | extend | topic file | Card names via `cardLabel`; HLD lab test links |
| `src/components/design/Exercises.tsx` | new | practice exercises of the topic (inlined at build), client storage | The ladder list: rung, title, `new_force`, status from attempts, link to the exercise page |
| `src/components/design/ClaimEvidence.astro` | new | claim `evidence` units | Shows the claim program or C++ test (via `<Code>` with `?raw` imports found by `import.meta.glob`) and its `expected.txt` or test output |
| `src/components/design/TradeOffTable.astro` | new | `measured-*.tsv`, `unit.yaml` | Renders the overhead, edit-cost, and blast-radius table for both variants |
| `src/components/design/LabRunner.astro` | new | `lab.yaml`, lab source files, `run.md` | Section 8.6's HLD block: diagram, key code, Go details, holds and breaks tests, "Run it" commands with copy buttons, recorded transcript |
| `src/components/design/ExperimentResult.astro` | new | `src/data/experiments/…`, results TSV | Machine, seed, results table, shape checks with PASS marks; "on this machine" label |
| `src/components/design/KitInstructions.astro` | new | exercise `checkers` | The `new_attempt.sh` and `test.sh` commands with copy buttons |
| `src/components/design/AskFirst.tsx` | new | exercise `clarifying` (client storage for his questions) | Type questions, reveal, tick critical ones asked |
| `src/components/design/RubricScorer.tsx` | new | rubric (inlined) | Criterion anchors, 0/1/2 selector, evidence field, score and pass/fail |
| `src/components/design/NumericAnswer.tsx` | new | checker `answer`, `factor` | Number and unit input, factor check, reveal |
| `src/components/design/PhaseTimer.tsx` | new | `time_limit_minutes`, exercise type | Countdown with phase shares (Section 11.2) |
| `src/components/design/ReferenceReveal.tsx` | new | reference `SOLUTION.md` (rendered at build, hidden until an attempt exists in storage) | Reveal gate |
| `src/components/design/ExportForReview.tsx` | new | attempt, rubric | Markdown to clipboard (fallback: selectable text) |
| `src/components/design/NumberFlashcards.tsx` | new | `constants.yaml`, client storage | Section 11.4 |
| `src/pages/[track]/exercise/[topic]/[id].astro` | new | practice exercises only (`getStaticPaths` over `src/data/exercises/*.yaml`, roles `ladder` and `worked_example`) | One generated page per practice exercise, assembling the components above |
| `src/pages/[track]/reserved.astro` | new | client: `?id=` and `/data/reserved/{topic}.json` | The same page layout for reserved items, rendered in the browser only, so they never appear in built HTML |
| `src/pages/data/reserved/[topic].json.ts` | new | reserved exercises | Static endpoint emitting each topic's reserved items as JSON |
| `src/pages/lld/handbook.astro`, `src/pages/hld/handbook.astro` | new | all topic files | Section 11.5 |
| `src/pages/hld/numbers.astro` | new | `constants.yaml`, client storage | Section 11.5 |
| `src/pages/hld/labs.astro` | new | every `lab.yaml` | Index of labs: topic, what is built, infra, rung count, his progress, link to the lesson's "Reference designs" |
| `src/content/docs/{lld,hld}/phase-*/index.mdx`, `exam.mdx` | new content | PLAN.md 11.2–11.3 | Phase intros and exams, using `Checkpoint` in exam mode |

Build each component with a small placeholder topic in D0 (as PLAN.md M0 did), check it at desktop width and 375 pixels, then delete the placeholder.

---

## 12. Build-time validation

Additions to `PLAN.md` Section 12. Each failure names the file and id.

- **D1. Schemas.** Topic, exercise, rubric, constants, inventory, experiment, `unit.yaml`, and `lab.yaml` files match their schemas.
- **D2. Counts.** As Section 10.9, by track and kind. Claims: at least one per card; every `from_claim` exists. `clarifying`: at least 4 entries, at least 2 critical, where required (Section 10.5).
- **D3. Order and quotas.** Every reference (`{topic, card}`, `techniques`, `uses`, `requires`) resolves within the same track with `order` ≤ the current topic's. Drill quotas of Section 8.10 hold. Each rung has exactly one `new_force`; each ladder has a rung with `needs_new_structure: false`.
- **D4. `uses` completeness.** As `PLAN.md` Section 12 item 10.
- **D5. Evidence.** Each claim's evidence exists and has the right kind: `proved` (HLD) or `simulated` → a Go claim program or a `simnet` test; `proved` (LLD) → a C++ solution unit; `computed` → a Go calc program; `measured` → at least two C++ pattern units with different `domain`s; `experimented` → an experiment record whose results file shows every shape check as PASS; `cited` → a source with `title`, `url`, `accessed`, `section`.
- **D6. Constants.** Every referenced constant exists with a source; `code/shared/constants.json` equals a fresh export.
- **D7. Checkers.** Each exercise's `checkers` list is one of the combinations of Section 10.1. Every `numeric` checker's `calc` program prints its `key`. Every `kit` path exists under `exercises/` and `reference/`. Every `rubric` id exists.
- **D8. Quotes.** In MDX prose, no blockquote or quoted text attributed to a source is longer than 15 words.
- **D9. No products in cards.** HLD card text contains no name from `src/data/product-names.yaml`. Lessons name products only in labs, "Run it" blocks, and `:::example[Real systems]` blocks with a cited claim.
- **D10. Diagrams.** Every Mermaid block renders at build time without network access at runtime.
- **D11. Keywords.** PLAN.md's keyword search, per track; `scripts/keyword_collisions.mjs` fails if a topic's keyword appears inside a keyword of an earlier topic of the same track or inside a required heading.
- **D12. Rubrics.** Weights sum to 100; at least one critical criterion; anchors 0, 1, 2 for every criterion.
- **D13. Headings.** Lesson headings match Section 8 exactly, in order; only `## See also` may be added at the end.
- **D14. Reserved items stay out of HTML.** No built HTML page contains the id or title of a reserved exercise.
- **D15. Labs.** Every HLD topic except H0.7 and H8.10 has a lab folder with `lab.yaml` and `run.md`; every test named in `holds` and `breaks`, and every HLD card's `lab.holds_test` and `lab.breaks_test`, exists as a `func Test…` in that lab's package.
- **D16. Go hygiene.** No Go folder name starts with `_` or `.`; `gofmt -l` is empty; `go vet` passes; `go mod tidy` leaves `go.mod` and `go.sum` unchanged; every module in `go.mod` is in `allowed_modules`.
- **D17. C++ hygiene.** Every C++ unit and kit compiles with the flags of Section 9.2; folders with a `sanitizer` file are exactly the L6 units and kits (and any later unit that uses threads), and no `test.sh` sets compiler flags except through `code/shared/cpp/cxxflags.sh`.
- **D18. No placeholders.** No file under `src/data/`, `src/content/docs/{lld,hld}/`, `exercises/`, or `reference/` contains the text `TODO` or an unfilled `{{…}}` template marker (the scaffolding scripts leave both on purpose).
- **D19. Server evidence.** Every experiment record names a results file produced on the lab server (`*-labserver.txt`) and a git commit; every topic with integration tests has a lab-server run summary in its merge message (checked by hand at merge).

---

## 13. Per-topic pipeline

Run in order. After each step, update `PROGRESS.md` and commit (PLAN.md 14.0 format, e.g., `topic(H4.2): step 4 lab and run transcript`).

1. **Scope.** Branch; run `node scripts/new_topic.mjs {id}` (lesson from the template, data file, exercise stubs from the inventory, `notes/design/{topic}.md`, code folder). Record allowed topics, new terms, forbidden keywords, glossary, planned cards and rungs (from the inventory).
2. **Principles and claims.** Lesson Sections 1–4; `uses` and `claims`. Write every evidence unit first, derive its expected output independently, then run it. LLD `measured` topics: build both C++ pattern units now.
3. **Lab or reference code.** HLD: build the lab (mechanism, `simnet` tests including the `breaks` test, `-race`), the `cmd/` processes, and `run.md`; on the lab server, run the real version with `faultproxy` and record the transcript, run the integration tests (`labserver.sh integration`), and run experiments in full mode (`labserver.sh experiment`). LLD: the reference C++ for each pattern or principle, with sanitizers.
4. **Recognition Cards.** Need or force, property, how to test, shapes with arithmetic, weak signals as form plus shape, kill signals (including over-engineering), `in_action`, trade-off or capacity tables from units, positive and negative examples, HLD lab test links.
5. **Reference designs.** Lesson Section 6 (`<LabRunner>` for HLD), with every C++ or Go construct explained.
6. **Mistake catalogue.** Write the wrong versions, run them, record the symptoms; reuse them as kit mutants.
7. **Exercises.** From the inventory, with the recipes of Section 18.4: rung kits via `node scripts/new_kit.mjs` (starter = previous rung's reference), references, mutants (Section 18.5), `exercise_kit_check.sh` on the lab server; estimate items with calc programs; recognition items; clarifying lists; sources (open each); rubric calibration.
8. **Worked examples.** Lesson Section 8, six-step format, tested units.
9. **Drill, look-alikes, self-test, checkpoint, reviews, decision map.** Fill the data files; check the handbooks render.
10. **Self-review and merge.** `npm run build`, `bash scripts/test_design.sh code`, and the experiment quick tests pass locally; `labserver.sh integration` and the kit check pass on the lab server (summary in the merge message); keyword search clean; read the lesson as a beginner; **honesty check** (point to where the lesson shows the technique costing more than it saves); **practicality check** (HLD: Saurabh could run every "Run it" block from a fresh clone with only the tools in `TOOLCHAINS.md`); reading test; merge; tag `topic-{id}`.

---

## 14. Milestones and review gates

Every block includes the phase intros and phase exams for the phases it completes.

| Milestone | Work | Gate |
|---|---|---|
| **D0** | Toolchains confirmed and recorded (`TOOLCHAINS.md`: g++, Go, Docker images by digest); `code/go.mod`; shared code with tests: `check.hpp`, `simnet` (synchronous and asynchronous modes), `faultproxy`, `loadgen`, `capcalc`; the toolchain versions of Section 3.1 confirmed, and every script, test, and appendix program of this plan re-run on them (newest Go and GCC included); the LAN lab server initialised and checked (`labserver.sh init`, then `labserver.sh check` output recorded; each stack started, health-checked, and stopped once; Kafka: create and consume one topic); the scripts of Section 9 (copied exactly and run on a synthetic example before first use), `constants_export.mjs`, `keyword_collisions.mjs`; CI jobs (C++ with sanitizers, Go with `-race`, experiment quick tests); `templates/`, `new_topic.mjs`, `new_kit.mjs`, `inventory_check.mjs`, and the Section 18.6 routes; curriculum rows (100 topics); schemas; every component and page of Section 11.7 on a placeholder topic; `rubrics.yaml`, `product-names.yaml`, `design.config.yaml`. Then the **exercise inventory** for all 100 topics. | ⏸ "Lab server reachable" and "D0 review" → `waiting`; continue on `approved`. Saurabh confirms the toolchain and image versions and may reorder the blocks below. |
| **DL1** | **L2.1 Strategy as the LLD exemplar**, all 10 steps; earlier topics appear as "coming soon" links. | ⏸ |
| **DH1** | **H4.2 Quorums as the HLD exemplar**, all 10 steps, including the real three-process run with `faultproxy`. | ⏸ |
| **L-A** | L0.0–L0.8 | ⏸ |
| **H-A** | H0.1–H0.7 | ⏸ |
| **L-B** | L1.1–L1.6 | ⏸ |
| **H-B** | H1.1–H1.5 | ⏸ |
| **L-C** | L2.2–L2.5, then revise L2.1 to match L0–L1 | ⏸ |
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

- `PROGRESS.md` gets `LLD topic` and `HLD topic` under "Saurabh is studying", plus the new gates.
- `FEEDBACK.md` types add: `wrong number | unrealistic scenario | rubric unfair | pattern misapplied | kit test too strict | lab does not run`. Handling: **wrong number**: recompute from the calc program or rerun the experiment, fix constants if needed, rerun everything that depends on them. **Rubric unfair**: adjust anchors, recalibrate. **Kit test too strict**: fix the test to use only the public interface, rerun the kit check. **Lab does not run**: reproduce from a fresh clone with the versions in `TOOLCHAINS.md`; fix `run.md` or the code; add the missing step to the lab's README.
- Repeated misses on one card: rewrite its signals, kill signals, and examples, and add drill items.

---

## 16. Definition of Done

### 16.1 Topic
- [ ] `npm run build`, `bash scripts/test_design.sh code`, `bash scripts/exercise_kit_check.sh`, and the experiment quick tests pass; Compose integration tests pass where the topic has them.
- [ ] All 14 lesson sections complete; claims follow Section 8.4 with evidence of the right kind.
- [ ] LLD: `measured` topics have two C++ pattern units from different domains, including a scenario where the pattern is not better; all C++ passes the sanitizers.
- [ ] HLD: the lab has `holds` and `breaks` tests on `simnet`, passes `-race`, runs as real processes on the lab server per `run.md` (transcript recorded with a date), integration tests pass on the lab server, and every experiment's full run on the lab server passes its shape checks; numbers are labelled "on the lab server".
- [ ] Every card: shapes with arithmetic, signals as form plus shape, `in_action`, trade-off or capacity table from units where applicable, ≥ 2 positive and ≥ 2 negative examples, an over-engineering kill signal with numbers; HLD cards link their lab tests and contain no product names.
- [ ] Mistake catalogue includes the over-engineered version; every wrong version was run.
- [ ] Ladder: one new force per rung; a "no new structure" rung. Drill: quotas of Section 8.10.
- [ ] Every exercise has an allowed checker combination; kits pass the kit check; rubrics calibrated; sources opened.
- [ ] No later-topic reference outside "does not cover"; header "Builds on" and "What you need" identical.
- [ ] Every abbreviation expanded on first use; every term defined before use; every C++ and Go construct explained in plain words.
- [ ] Components behave in the browser (desktop and 375 pixels).
- [ ] Honesty check, practicality check, and reading test done; `PROGRESS.md` updated; merged and tagged.

### 16.2 Phase
- [ ] All topics done; phase intro and exam complete with a remediation map.
- [ ] "Coming soon" links resolved; tagged `phase-L{n}` or `phase-H{n}`; gate set to `waiting`.

---

## 17. Failure handling

| Situation | Action |
|---|---|
| A pattern unit shows the patterned design is not better | Keep it; the lesson says when the pattern does not pay, with the numbers. Do not tune scenarios to favour the pattern. |
| Only one domain fits a `measured` claim | Change the claim to `proved` or an illustrated example, say so in the lesson, and change the topic's `kind` to `standard` with a note in `PROGRESS.md`. |
| A claim program disagrees with the hand-derived expected output | Treat it as an error in the claim, proof, or program. Resolve it before anything else. |
| A sanitizer reports something in reference code | It is a bug until proved otherwise. Fix it; never suppress a sanitizer report in reference code. |
| A `simnet` test is flaky | It must be deterministic: find the real source of nondeterminism (map iteration order, unseeded randomness, wall-clock time, goroutine scheduling without synchronisation) and remove it. Never add retries or sleeps to make it pass. |
| An experiment's shape check fails on some machines | Check whether the claim is really true or only true on fast hardware. Weaken the claim to what holds, or make the experiment control the variable (fixed service time, pinned load); record both runs. |
| The lab server cannot be reached | Build and test everything that does not need it; write the server steps as exact commands under "Questions for Saurabh"; the topic is not merged until he pastes passing output. |
| A stack fails to start on the server (port in use, disk full, memory) | Run `labserver.sh check`; free the resource or change the stack's port through `.env.labserver`; never stop a Compose project you did not start. |
| A Kafka or MySQL image changes its configuration conventions | Re-read the image's documentation, update the stack file and `TOOLCHAINS.md`, re-validate with `docker compose config`, and rerun the stack check. |
| A third-party Go module is abandoned or changes licence | Replace it through Section 9.5, or replace the dependency with standard-library code if the lab can do without it. |
| A constant or source cannot be verified | Do not use it; use a labelled assumption or a measurement from a lab. |
| Kit tests pass a mutant | Add a test that fails on it. Never delete the mutant. |
| Kit tests fail a valid alternative design | Rewrite the tests against the public interface. |
| A rubric's reference scores below 90%, or a wrong answer 60% or more | Rewrite the anchors and recalibrate. |
| A look-alike or kill signal needs a later topic | Describe the condition without naming the later tool, or move the pair to the later lesson. |
| A prompt closely resembles a copyrighted exam or book exercise | Rewrite it in a different domain with different numbers. |


---

## 18. Generating the content: exercises, kits, labs, and pages

This section is the recipe for producing every exercise ("problem") and every page. Sections 7–11 say *what* each item must contain; this section says *how to make it*, in what order, with which scripts and templates, and shows a finished sample of each item type.

### 18.1 Order of generation
1. **Inventory (D0, all topics).** `src/data/exercises/INVENTORY.yaml` (format in 18.2). No prose, no code.
2. **Per topic, in curriculum order**, when its block starts:
   1. `node scripts/new_topic.mjs {id}`: lesson skeleton, data file, exercise stubs, notes, code folder (18.3).
   2. Evidence units and the lab or reference code (Section 13, steps 2–3).
   3. Kits: one `node scripts/new_kit.mjs …` per kit (18.3), then tests, reference, and mutants, in that order (18.5).
   4. Exercise YAML: replace every `TODO` using the recipes in 18.4.
   5. Lesson prose: fill the skeleton section by section (Section 8).
   6. Pages appear by themselves from the data (18.6); check them in the browser.
3. **Never generate in bulk without checking.** Write one item of each type for a topic, run the checks (`npm run build`, `test_design.sh`, `exercise_kit_check.sh`, the server run), then write the rest.

### 18.2 Inventory format
```yaml
topics:
  "H4.2":
    cards: [{id: quorum-replication, name: "Quorum replication"}]
    ladder:                                   # lab rungs (HLD) or change-ladder rungs (LLD)
      - {rung: 1, card: quorum-replication, new_force: "Basic Put and Get over three replicas", needs_new_structure: true, tests: "Put then Get returns the value"}
      - {rung: 2, card: quorum-replication, new_force: "One replica is down", needs_new_structure: true, tests: "C down: Put and Get still succeed"}
      - {rung: 3, card: null, new_force: "Twice the read load", needs_new_structure: false, tests: "measured p99 stays under the target on the lab server"}
    drill:
      - {stub: "Session store, 3 zones, 99.999% for single-key operations", answer: {topic: "H4.2", card: quorum-replication}}
      - {stub: "Single-region admin tool, 50 requests a day", answer: none}
    checkpoint: {title: "Quorum store variant: read repair", type: lab}
    reviews:
      - {set: 1, stubs: ["Shopping cart across 3 zones: choose N, W, R", "Estimate: replication traffic for 20 000 writes/s at 1 KB"]}
```
A script you write in D0 (`scripts/inventory_check.mjs`) checks: every card in a stub is planned in the same or an earlier topic of the track; Section 8.10 quotas hold; each ladder has a `needs_new_structure: false` rung; no scenario repeats within a track.

### 18.3 Scaffolding scripts and templates
Both scripts were run while writing this plan (Node 22, with the `yaml` package that the site already depends on). They never overwrite, and every `TODO` they leave must be gone before the build passes (Section 12, D18).

**`scripts/new_topic.mjs`** (use exactly; tested):
```js
#!/usr/bin/env node
// Usage: node scripts/new_topic.mjs <topic-id>        e.g. node scripts/new_topic.mjs H4.2
// Creates, from templates/topic/ and the curriculum row (and INVENTORY.yaml, if it lists the topic):
//   src/content/docs/{track}/phase-{n}/{id-dash}-{slug}.mdx   lesson skeleton with every required heading
//   src/data/topics/{id-dash}.yaml                            data file with `uses` prefilled from `requires`
//   src/data/exercises/{id-dash}.yaml                         exercise stubs from the inventory
//   code/{id}/  notes/design/{id}.md
// Never overwrites: stops if any of these already exists. Every TODO it writes must be replaced
// before the build passes (Section 12, D18).
import fs from 'node:fs';
import path from 'node:path';
import { parse } from 'yaml';

const root = path.resolve(path.dirname(new URL(import.meta.url).pathname), '..');
const id = process.argv[2];
if (!id || !/^[LH]\d\.\d+$/.test(id)) { console.error('usage: new_topic.mjs <topic-id like L2.1 or H4.2>'); process.exit(2); }

const rows = parse(fs.readFileSync(path.join(root, 'src/data/curriculum.yaml'), 'utf8'));
const row = rows.find((r) => r.id === id);
if (!row) { console.error(`topic ${id} is not in src/data/curriculum.yaml`); process.exit(1); }

const track = row.track;                       // 'lld' | 'hld'
const dash = id.replace('.', '-');
const lessonDir = path.join(root, 'src/content/docs', track, `phase-${row.phase}`);
const files = {
  lesson: path.join(lessonDir, `${dash}-${row.slug}.mdx`),
  topic: path.join(root, 'src/data/topics', `${dash}.yaml`),
  exercises: path.join(root, 'src/data/exercises', `${dash}.yaml`),
  notes: path.join(root, 'notes/design', `${id}.md`),
};
for (const f of Object.values(files)) {
  if (fs.existsSync(f)) { console.error(`already exists: ${path.relative(root, f)}`); process.exit(1); }
}

// Relative import prefix from the lesson folder to src/components/, ending in '/'.
const comp = path.relative(lessonDir, path.join(root, 'src/components')).split(path.sep).join('/') + '/';
const fill = (text, vars) => text.replace(/\{\{(\w+)\}\}/g, (m, k) => (k in vars ? vars[k] : m));
const tpl = (name) => fs.readFileSync(path.join(root, 'templates/topic', name), 'utf8');

const uses = (row.requires ?? []).map((t) => `  - {topic: "${t}", what: "TODO"}`).join('\n') || '  []';
const isLab = track === 'hld' && row.lab && row.lab !== 'none';

// Exercise stubs from the inventory, if present.
let stubs = '  []';
const invPath = path.join(root, 'src/data/exercises/INVENTORY.yaml');
if (fs.existsSync(invPath)) {
  const inv = parse(fs.readFileSync(invPath, 'utf8'))?.topics?.[id];
  if (inv) {
    const out = [];
    for (const r of inv.ladder ?? []) {
      const kit = track === 'hld' ? `${id}/lab/rung-${r.rung}` : `${id}/ladder/rung-${r.rung}`;
      out.push(`  - id: rung-${r.rung}
    role: ladder
    type: ${track === 'hld' ? 'lab' : 'change_ladder'}
    title: "TODO"
    prompt: "TODO"
    card: ${r.card ? r.card : 'null'}
    rung: ${r.rung}
    new_force: ${JSON.stringify(r.new_force)}
    needs_new_structure: ${r.needs_new_structure}
    checkers: [{kind: kit, path: "${kit}"}]
    reference: "reference/${kit}"
    hints: ["TODO", "TODO", "TODO"]
    techniques: ["${id}"]
    checked_on: "TODO"`);
    }
    (inv.drill ?? []).forEach((d, i) => {
      const answer = d.answer === 'none'
        ? '{kind: none, simplest: "TODO", why: "TODO"}'
        : `{kind: card, card: {topic: "${d.answer.topic}", card: ${d.answer.card}}, property: "TODO", why_others_fail: "TODO"}`;
      out.push(`  - id: r-${i + 1}
    role: drill
    type: recognise
    title: "TODO"
    prompt: "TODO (stub: ${String(d.stub).replace(/"/g, "'")})"
    answer: ${answer}
    checkers: []
    techniques: ["${id}"]
    checked_on: "TODO"`);
    });
    if (out.length) stubs = out.join('\n');
  }
}

const vars = {
  ID: id, TITLE: row.title, ORDER: String(row.order), TRACK: track, C: comp, USES: uses, STUBS: stubs,
  LAB_RUNNER: isLab ? `<LabRunner unit="${id}/lab-TODO" />\n` : '',
};
fs.mkdirSync(lessonDir, { recursive: true });
for (const d of ['src/data/topics', 'src/data/exercises', 'notes/design', `code/${id}`]) fs.mkdirSync(path.join(root, d), { recursive: true });
fs.writeFileSync(files.lesson, fill(tpl('lesson.mdx'), vars));
fs.writeFileSync(files.topic, fill(tpl('topic.yaml'), vars));
fs.writeFileSync(files.exercises, fill(tpl('exercises.yaml'), vars));
fs.writeFileSync(files.notes, `# ${id} ${row.title}: private notes\n\n## Sources checked\n\n## Calibration\n\n## Dropped ideas\n`);
for (const f of Object.values(files)) console.log('created', path.relative(root, f));
console.log('created', `code/${id}/`);
```

**`scripts/new_kit.mjs`** (use exactly; tested):
```js
#!/usr/bin/env node
// Usage: node scripts/new_kit.mjs <kit-path> --lang go|cpp --package <name> [--title "…"] [--prompt "…"]
//   e.g. node scripts/new_kit.mjs H5.6/lab/rung-1 --lang go --package ratelimit
// Creates exercises/<kit-path>/ from templates/kit-<lang>/, plus empty reference/<kit-path>/ and
// reference-mutants/<kit-path>/. For a ladder rung k > 1 (path ending in rung-k), the starter is a copy of
// reference/…/rung-(k-1), which must already exist, and min_mutants is 2.
import fs from 'node:fs';
import path from 'node:path';

const root = path.resolve(path.dirname(new URL(import.meta.url).pathname), '..');
const args = process.argv.slice(2);
const kit = args[0];
const opt = (name, def) => { const i = args.indexOf(`--${name}`); return i >= 0 ? args[i + 1] : def; };
const lang = opt('lang');
const pkg = opt('package');
if (!kit || !['go', 'cpp'].includes(lang) || !/^[a-z][a-z0-9_]*$/.test(pkg ?? '')) {
  console.error('usage: new_kit.mjs <kit-path> --lang go|cpp --package <lowercase_name> [--title …] [--prompt …]');
  process.exit(2);
}
const dst = path.join(root, 'exercises', kit);
if (fs.existsSync(dst)) { console.error(`already exists: exercises/${kit}`); process.exit(1); }
const vars = { KIT_PATH: kit, PACKAGE: pkg, TITLE: opt('title', 'TODO'), PROMPT: opt('prompt', 'TODO') };
const fill = (s) => s.replace(/\{\{(\w+)\}\}/g, (m, k) => (k in vars ? vars[k] : m));

function copyTemplate(src, out) {          // copies a folder, filling {{…}} in file names and contents
  fs.mkdirSync(out, { recursive: true });
  for (const name of fs.readdirSync(src)) {
    const from = path.join(src, name);
    const to = path.join(out, fill(name));
    if (fs.statSync(from).isDirectory()) copyTemplate(from, to);
    else { fs.writeFileSync(to, fill(fs.readFileSync(from, 'utf8'))); fs.chmodSync(to, fs.statSync(from).mode); }
  }
}
copyTemplate(path.join(root, 'templates', `kit-${lang}`), dst);

const rung = /(.*)\/rung-(\d+)$/.exec(kit);
if (rung && Number(rung[2]) > 1) {
  const prev = path.join(root, 'reference', `${rung[1]}/rung-${Number(rung[2]) - 1}`);
  if (!fs.existsSync(prev) || fs.readdirSync(prev).length === 0) { console.error(`previous rung's reference is missing or empty: ${path.relative(root, prev)}`); fs.rmSync(dst, { recursive: true }); process.exit(1); }
  fs.rmSync(path.join(dst, 'starter'), { recursive: true });
  fs.cpSync(prev, path.join(dst, 'starter'), { recursive: true });
}
if (rung) fs.writeFileSync(path.join(dst, 'min_mutants'), '2\n');
fs.mkdirSync(path.join(root, 'reference', kit), { recursive: true });
fs.mkdirSync(path.join(root, 'reference-mutants', kit), { recursive: true });
console.log(`created exercises/${kit}/ (${lang}), reference/${kit}/, reference-mutants/${kit}/`);
```

**Templates** (create in D0, exactly these files):
```
templates/
├── topic/lesson.mdx        # Section 8 skeleton with {{ID}}, {{TITLE}}, {{ORDER}}, {{C}} (import prefix), {{LAB_RUNNER}}; every section body "TODO"
├── topic/topic.yaml        # id, track, uses (prefilled from requires), empty claims/cards/… marked TODO
├── topic/exercises.yaml    # topic + {{STUBS}}
├── kit-go/                 # README.md, test.sh (Appendix C's), starter/{{PACKAGE}}.go, tests/{{PACKAGE}}_test.go
└── kit-cpp/                # README.md, test.sh (below), starter/{{PACKAGE}}.hpp, tests/tests.cpp
```
The template files, exactly (the `{{…}}` markers are filled by the scripts):

`templates/topic/lesson.mdx`:
```text
---
title: "{{ID}} {{TITLE}}"
sidebar:
  order: {{ORDER}}
topic: "{{ID}}"
---
import { Code } from '@astrojs/starlight/components';
import TopicHeader from '{{C}}TopicHeader.astro';
import WhatYouNeed from '{{C}}WhatYouNeed.astro';
import ClaimEvidence from '{{C}}design/ClaimEvidence.astro';
import TradeOffTable from '{{C}}design/TradeOffTable.astro';
import LabRunner from '{{C}}design/LabRunner.astro';
import ExperimentResult from '{{C}}design/ExperimentResult.astro';
import Cards from '{{C}}Cards.astro';
import Exercises from '{{C}}design/Exercises.tsx';
import Drill from '{{C}}Drill.tsx';
import LookalikePairs from '{{C}}LookalikePairs.astro';
import SelfTest from '{{C}}SelfTest.astro';
import Checkpoint from '{{C}}Checkpoint.tsx';
import DecisionMapUpdate from '{{C}}DecisionMapUpdate.astro';

<TopicHeader topic="{{ID}}" />

## 1. Why this topic exists
TODO

## 2. Prerequisites and scope
### What you need
<WhatYouNeed topic="{{ID}}" />
### What this topic does not cover
TODO

## 3. Definitions
TODO

## 4. Principles and claims
TODO

## 5. Recognition Cards
<Cards topic="{{ID}}" />

## 6. Reference designs
{{LAB_RUNNER}}TODO

## 7. Mistake catalogue
TODO

## 8. Worked examples
TODO

## 9. Exercise ladder
<Exercises topic="{{ID}}" client:load />

## 10. Recognition drill
<Drill topic="{{ID}}" client:load />

## 11. Look-alike pairs
<LookalikePairs topic="{{ID}}" />

## 12. Self-test questions
<SelfTest topic="{{ID}}" />

## 13. Checkpoint
<Checkpoint topic="{{ID}}" client:load />

## 14. Decision map update
<DecisionMapUpdate topic="{{ID}}" />
```
`templates/topic/topic.yaml`:
```text
id: "{{ID}}"
track: {{TRACK}}
uses:
{{USES}}
claims: []        # TODO: Section 7.2
cards: []         # TODO: Section 7.2
lookalike_pairs: []
self_test: []
decision_map: []
glossary_added: []
```
`templates/topic/exercises.yaml`:
```text
topic: "{{ID}}"
exercises:
{{STUBS}}
```
`templates/kit-go/starter/{{PACKAGE}}.go` and `templates/kit-go/tests/{{PACKAGE}}_test.go`:
```text
// Package {{PACKAGE}}: see README.md for the task.
package {{PACKAGE}}

// TODO: declare the public interface here; every function body is panic("not implemented").
```
```text
package {{PACKAGE}}

import "testing"

// TODO: behaviour tests through the public interface only.
func TestTODO(t *testing.T) { t.Fatal("write the tests") }
```
`templates/kit-cpp/starter/{{PACKAGE}}.hpp` and `templates/kit-cpp/tests/tests.cpp`:
```text
#pragma once
#include <stdexcept>

// TODO: declare the public interface; every member function body is
// throw std::logic_error("not implemented");
```
```text
#include "check.hpp"
#include "{{PACKAGE}}.hpp"

// TODO: behaviour tests through the public interface only.
void todo() { CHECK(false); }

int main() {
    RUN(todo);
    return check::report();
}
```
`templates/kit-go/test.sh` is Appendix C's `test.sh`. `templates/kit-cpp/README.md` is the Go README below with the "Public interface" line replaced by "Implement the classes declared in `starter/{{PACKAGE}}.hpp`."

`templates/kit-cpp/test.sh` (use exactly; tested with a kit whose three mutants were caught, one by the undefined-behaviour sanitizer):
```bash
#!/usr/bin/env bash
# usage: bash test.sh <solution-dir>   Builds tests/tests.cpp with the solution's headers and .cpp files,
# using the flags from code/shared/cpp/cxxflags.sh (this kit's "sanitizer" file, if any, picks the sanitizer),
# then runs it. Nothing is written into the solution folder.
set -euo pipefail
KIT="$(cd "$(dirname "${BASH_SOURCE[0]}")" && pwd)"
SOL="$(cd "$1" && pwd)"
R="$KIT"; while [ "$R" != "/" ] && [ ! -f "$R/code/shared/cpp/check.hpp" ]; do R="$(dirname "$R")"; done
[ -f "$R/code/shared/cpp/check.hpp" ] || { echo "code/shared/cpp/check.hpp not found" >&2; exit 2; }
B="$(mktemp -d)"; trap 'rm -rf "$B"' EXIT
mapfile -t SRCS < <(find "$SOL" -maxdepth 1 -name '*.cpp' ! -name 'main.cpp')
g++ $(bash "$R/code/shared/cpp/cxxflags.sh" "$KIT") -I"$R/code/shared/cpp" -I"$SOL" "$KIT/tests/tests.cpp" "${SRCS[@]}" -o "$B/tests"
"$B/tests"
```
`templates/kit-go/README.md` (the C++ one differs only in the "Public interface" line):
```markdown
# {{KIT_PATH}}: {{TITLE}}

## Task
{{PROMPT}}

## Public interface
Package `{{PACKAGE}}`. Implement the functions and methods declared in `starter/`. Do not change their signatures.

## Acceptance tests (in words)
- TODO: one line per test in tests/, describing the behaviour it checks.

## How to work
    bash scripts/new_attempt.sh {{KIT_PATH}}
    # edit work/{{KIT_PATH}}/
    bash exercises/{{KIT_PATH}}/test.sh work/{{KIT_PATH}}
On the lab server: `bash scripts/labserver.sh kit {{KIT_PATH}} work/{{KIT_PATH}}`
```

### 18.4 Recipes, with a finished sample of each item type
Each recipe lists the steps, then a sample that meets every rule. Samples are examples of shape and quality; write your own content for each topic.

#### Recognition item (`recognise`), LLD or HLD
1. Pick the intended answer from the inventory stub (a card of this or an earlier topic, or "none").
2. Write a 3–6 sentence situation in a domain **different** from the lesson's examples. Include the numbers that decide it (variant counts and expected changes for LLD; rates, sizes, staleness, availability for HLD).
3. Plant one **look-alike surface feature** that points to a wrong card (the reason the item is hard).
4. Write `property` (why the right card fits, naming the decisive property) and `why_others_fail` (one sentence per tempting wrong card), or for "none", `simplest` and `why` with numbers.
5. Check the item against the quotas and that no later topic's keyword appears.

```yaml
- id: r-3
  role: drill
  type: recognise
  title: "Report exporter"
  prompt: |
    A reporting module exports reports as CSV; the export code is 12 lines.
    The product manager says PDF export "might be nice some day", but nothing is planned.
    One team owns the module and tests it as a whole.
  answer:
    kind: none
    simplest: "plain function"
    why: "One format and no planned second one. An interface plus one class per format adds files and lines (Appendix A measured +4 files and +39 lines for two variants) and isolates nothing."
  checkers: []
  techniques: ["L2.1"]
  checked_on: "2026-10-20"
```
A sample from H2.4's drill, answered by an earlier topic's card:
```yaml
- id: r-5
  role: drill
  type: recognise
  title: "Product catalogue reads"
  prompt: |
    A product catalogue API serves 40 000 reads per second at peak and 20 writes per second.
    The whole catalogue is 3 GB. Product pages may show data up to 60 seconds old.
    One database primary on the lab server handles about 8 000 indexed reads per second (given).
  answer:
    kind: card
    card: {topic: "H2.2", card: shared-cache-ttl}
    property: "Reads may be up to 60 s stale, the data fits in memory (3 GB), and reads outnumber writes 2 000 to 1, so a shared cache with a TTL of at most 60 s serves almost all reads."
    why_others_fail: "Read replicas also work but need at least 5 database machines (8 with 30% headroom: 40 000 / (8 000 × 0.7) ≈ 7.1) and still need lag handling; a single primary cannot serve 40 000 reads per second."
  checkers: []
  techniques: ["H2.2", "H2.3"]
  checked_on: "2026-10-20"
```

#### Estimate item (`estimate`)
1. Choose a scenario and **give** every input in the prompt (users, actions per user, sizes, peak factor); take any other constant from `constants.yaml`.
2. Write the calc program first (Section 9.8), deriving `expected.txt` independently (by hand or a separate one-line calculation), then run the program and compare.
3. Point each numeric checker at one printed `key`; use `factor: 2`.

```yaml
- id: est-2
  role: ladder
  type: estimate
  title: "Photo uploads"
  prompt: |
    A photo app has 10 million daily active users. Each uploads 2 photos a day, 2 MB on average.
    Traffic at the busiest hour is 3 times the daily average. Estimate peak uploads per second
    and the storage added per year (one copy, no compression).
  checkers:
    - {kind: numeric, calc: "H0.2/calc-photo-uploads", key: "peak_uploads_per_second", unit: "uploads per second", factor: 2}
    - {kind: numeric, calc: "H0.2/calc-photo-uploads", key: "storage_per_year", unit: "PB", factor: 2}
  hints: ["Uploads per day first.", "A day has 86 400 seconds; multiply the average by the peak factor.", "Bytes per day times 365; 1 PB = 10^15 bytes."]
  techniques: ["H0.2"]
  checked_on: "2026-10-20"
```
The calc program (`code/H0.2/calc-photo-uploads/main.go`, run and checked while writing this plan):
```go
// Calc program for exercise H0.2/est-2 (photo uploads). Every input is given in the prompt;
// a real calc program reads shared constants through capcalc (Section 9.8).
package main

import "fmt"

func main() {
	const (
		dailyActiveUsers = 10_000_000 // given
		uploadsPerUser   = 2.0        // per day, given
		avgPhotoBytes    = 2e6        // 2 MB, given
		peakFactor       = 3.0        // peak hour rate / average rate, given
		secondsPerDay    = 86_400
		daysPerYear      = 365
	)
	uploadsPerDay := dailyActiveUsers * uploadsPerUser
	avgPerSecond := uploadsPerDay / secondsPerDay  // uploads per second, averaged over the day
	peakPerSecond := avgPerSecond * peakFactor     // uploads per second at peak
	ingressPeak := peakPerSecond * avgPhotoBytes   // bytes per second arriving at peak
	storagePerDay := uploadsPerDay * avgPhotoBytes // bytes per day, one copy
	storagePerYear := storagePerDay * daysPerYear  // bytes per year, one copy

	fmt.Printf("uploads_per_day = %.0f uploads\n", uploadsPerDay)
	fmt.Printf("avg_uploads_per_second = %.1f uploads/s\n", avgPerSecond)
	fmt.Printf("peak_uploads_per_second = %.0f uploads/s\n", peakPerSecond)
	fmt.Printf("peak_ingress = %.2f GB/s\n", ingressPeak/1e9)
	fmt.Printf("storage_per_day = %.0f TB\n", storagePerDay/1e12)
	fmt.Printf("storage_per_year = %.1f PB\n", storagePerYear/1e15)
}
```
`expected.txt`:
```
uploads_per_day = 20000000 uploads
avg_uploads_per_second = 231.5 uploads/s
peak_uploads_per_second = 694 uploads/s
peak_ingress = 1.39 GB/s
storage_per_day = 40 TB
storage_per_year = 14.6 PB
```

#### Lab rung (`lab`, HLD)
1. From the inventory rung: the one `new_force` and its test sentence.
2. `node scripts/new_kit.mjs {topic}/lab/rung-{k} --lang go --package {pkg}`. For k > 1 the starter is the previous rung's reference.
3. Write the tests first, on `simnet` (deterministic), including the failure the rung is about; for a measurement rung, an experiment with a shape check run on the lab server.
4. Write the reference by extending the previous rung's reference, then 2+ mutants that each break the new requirement in a different way (Section 18.5). Run the kit check.
5. Write the README from the template: task, public interface, acceptance tests in words, run step.

````markdown
# H4.2/lab/rung-2: Survive one replica down

## Task
Your quorum store from rung 1 must keep working when one of its three replicas is down:
Put succeeds once W = 2 replicas store the value, and Get returns the newest value from any R = 2 replicas.
When two replicas are down, both Put and Get must fail with ErrNoQuorum instead of hanging or returning stale data.

## Public interface
Package `quorumkv`: `NewReplica`, `Client.Put`, `Client.Get`, `ErrNoQuorum` (unchanged from rung 1).

## Acceptance tests (in words)
- With replica C down, Put then Get returns the value.
- With replicas B and C down, Put returns an error that matches ErrNoQuorum.
- With replicas B and C down, Get returns an error that matches ErrNoQuorum.
- All rung 1 tests still pass. Everything runs with the race detector.

## Run it on the lab server
    bash scripts/labserver.sh exec "cd code && go run ./H4.2/lab-quorumkv/cmd/node -id A -port 8101 & …"
(the full sequence is in code/H4.2/lab-quorumkv/run.md: start three nodes, kill one, run the client, kill a second)
````

#### Change-ladder rung (`change_ladder`, LLD)
1. From the inventory rung: the one new requirement.
2. `node scripts/new_kit.mjs {topic}/ladder/rung-{k} --lang cpp --package {name}`.
3. Tests for the new requirement plus all earlier tests; reference extends the previous rung; 2+ mutants (Section 18.5).
4. In the reference `SOLUTION.md`, give the edit cost of this rung for the plain and the patterned design (run `git diff --numstat` between rung references).

#### Mock or deep dive with clarifying questions (`mock`, `deep_dive`)
1. A vague prompt of 2–4 sentences, as an interviewer would give it.
2. A `clarifying` list of 4–8 questions with the interviewer's answers; mark `critical` the ones that change the design (at least 2).
3. A reference with a decision record and the timeline; three full wrong answers for calibration (Section 10.7).

```yaml
- id: mock-1
  role: checkpoint
  type: mock
  title: "Short links for a marketing platform"
  prompt: "Design a service that turns long links into short ones for our marketing team's campaigns. Walk me through it."
  clarifying:
    - {q: "How many new links per day, and how many clicks?", a: "About 1 million new links a day; each is clicked about 100 times on average.", critical: true}
    - {q: "Can users choose their own short codes?", a: "Yes, optionally; they must be unique.", critical: true}
    - {q: "Do links expire?", a: "Campaign links expire after 1 year by default.", critical: false}
    - {q: "Do we need click analytics?", a: "Counts per link per day, visible within an hour.", critical: true}
    - {q: "What redirect latency is acceptable?", a: "Under 50 ms at p99 inside the region.", critical: false}
  checkers:
    - {kind: numeric, calc: "H8.1/calc-shortener", key: "peak_redirects_per_second", unit: "redirects per second", factor: 2}
    - {kind: rubric, id: "rubric-hld-mock-v1"}
  time_limit_minutes: 45
  techniques: ["H8.1", "H3.4", "H2.2"]
  checked_on: "2026-10-20"
```

#### Review item (transfer prompt)
Same card, a different domain, and one changed number that matters. Sample for H4.2: "A shopping cart service runs in three zones. Losing an added item is unacceptable; showing a cart up to 2 seconds old is fine. Choose N, W, and R, and say what happens when one zone is down." (Answer: N = 3, W = 2, R = 2, so a read after an acknowledged add always meets it; with one zone down both quorums still form. R = 1 would be faster but gives no bound on staleness at all, so it does not meet even the 2-second allowance by itself.)

### 18.5 Making mutants
At least three per kit (two per rung), each a **different kind** of mistake, each a small edit to the reference:
- **Go labs:** missing lock (caught by `-race`); wrong quorum or boundary (`<` versus `<=`); missing timeout or context check (the test uses a blackholed node and a deadline); retry without limit; committing before processing; ignoring an error; using wall-clock time instead of the injected clock.
- **C++ kits:** off-by-one or rounding error; a missing virtual destructor or a dangling reference (caught by the address sanitizer); a broken invariant after an exception; wrong ownership (copying where a move was meant); undefined behaviour (caught by the undefined-behaviour sanitizer); a data race (thread sanitizer, L6 only).
- If a mutant survives, the tests are too weak: add a test, never delete the mutant. Real example from testing this plan: in the C++ counter kit, a mutant that counted `add(0)` as 1 passed every test; adding a test with `add(0)` and `add(-4)` caught it.

### 18.6 Generating the pages
No page is written by hand except lesson bodies, phase intros, and phase exams. Everything else is generated at build time from the data files:

| Page | Generated from | How |
|---|---|---|
| Lesson (`src/content/docs/{track}/phase-{n}/{id-dash}-{slug}.mdx`) | `templates/topic/lesson.mdx` via `new_topic.mjs`; bodies written by you | Starlight content collection; components inside read the topic's data files |
| Practice exercise page `/{track}/exercise/{topic}/{id}/` | `src/data/exercises/*.yaml`, roles `ladder` and `worked_example` | `src/pages/[track]/exercise/[topic]/[id].astro` (below) |
| Reserved items `/data/reserved/{topic}.json` | the same files, other roles | `src/pages/data/reserved/[topic].json.ts` (below) |
| Reserved item page `/{track}/reserved/?id=…` | the JSON above, in the browser | `src/pages/[track]/reserved.astro` (below): a static shell per track (`getStaticPaths` returns `lld` and `hld`) that fetches the JSON after unlock |
| Handbooks `/lld/handbook/`, `/hld/handbook/` | every topic file's `cards` and `decision_map` | static Astro pages that group entries by symptom (LLD) or need (HLD) |
| Labs index `/hld/labs/` | every `code/**/lab.yaml` via `import.meta.glob` | static Astro page |
| Numbers sheet `/hld/numbers/` | `constants.yaml` | static Astro page plus client storage for his measured values |
| Phase intro and exam | written by you from PLAN.md 11.2–11.3 | MDX in the phase folder |

The loader and the three routes below were built with **Astro 7.4.0, Starlight 0.42.6, and yaml 2.9.1** while writing this plan, on a sample with one practice and one reserved exercise. The build produced one HTML page per practice exercise inside Starlight's layout (`StarlightPage`, imported from `@astrojs/starlight/components/StarlightPage.astro`), one reserved shell page per track, and one JSON file per topic; **the reserved item's title and prompt appeared in no HTML file**; and in a real browser (Playwright with Chromium), `/hld/reserved/?id=H4.2/r-1` displayed the item fetched from the JSON, and an unknown id displayed "Not found."

`src/lib/exercises.ts` (use exactly; extend the `Exercise` type with the remaining fields of Section 7.3):
```ts
// Loads every exercise file at build time and splits practice from reserved items.
import { parse } from 'yaml';

export type Exercise = {
  id: string; role: string; type: string; title: string; prompt: string;
  topic: string; track: 'lld' | 'hld'; globalId: string;
};

const PRACTICE = new Set(['ladder', 'worked_example']);

// import.meta.glob reads the files when the site is built; '?raw' gives the file text.
const files = import.meta.glob('/src/data/exercises/*.yaml', { query: '?raw', import: 'default', eager: true }) as Record<string, string>;

export function allExercises(): Exercise[] {
  const out: Exercise[] = [];
  for (const [path, text] of Object.entries(files)) {
    if (path.endsWith('INVENTORY.yaml')) continue;
    const data = parse(text) as { topic: string; exercises: Omit<Exercise, 'topic' | 'track' | 'globalId'>[] };
    const track = data.topic.startsWith('L') ? 'lld' : 'hld';
    for (const e of data.exercises) out.push({ ...e, topic: data.topic, track, globalId: `${data.topic}/${e.id}` });
  }
  return out;
}

export const isPractice = (e: Exercise) => PRACTICE.has(e.role);
```
`src/pages/[track]/exercise/[topic]/[id].astro`:
```astro
---
// One static page per PRACTICE exercise, inside the Starlight layout. Reserved exercises are never pre-rendered.
import StarlightPage from '@astrojs/starlight/components/StarlightPage.astro';
import { allExercises, isPractice, type Exercise } from '../../../../lib/exercises';

export function getStaticPaths() {
  return allExercises()
    .filter(isPractice)
    .map((e) => ({ params: { track: e.track, topic: e.topic, id: e.id }, props: { exercise: e } }));
}
const { exercise } = Astro.props as { exercise: Exercise };
---
<StarlightPage frontmatter={{ title: `${exercise.globalId}: ${exercise.title}` }}>
  <p>{exercise.prompt}</p>
</StarlightPage>
```
`src/pages/[track]/reserved.astro` (it needs `getStaticPaths` because `[track]` is a route parameter):
```astro
---
// Shell page for reserved exercises (drill, checkpoint, review, exam). The build knows nothing about them:
// the browser reads ?id=H4.2/r-1, fetches /data/reserved/H4.2.json, and renders the item after unlock.
import StarlightPage from '@astrojs/starlight/components/StarlightPage.astro';

export function getStaticPaths() {
  return [{ params: { track: 'lld' } }, { params: { track: 'hld' } }];
}
---
<StarlightPage frontmatter={{ title: 'Exercise' }}>
  <div id="reserved-root">Loading…</div>
  <script>
    const id = new URLSearchParams(location.search).get('id') ?? '';
    const topic = id.split('/')[0];
    const root = document.getElementById('reserved-root')!;
    fetch(`/data/reserved/${encodeURIComponent(topic)}.json`)
      .then((r) => (r.ok ? r.json() : Promise.reject(new Error(`HTTP ${r.status}`))))
      .then((items: { globalId: string; title: string; prompt: string }[]) => {
        const item = items.find((e) => e.globalId === id);
        if (!item) { root.textContent = 'Not found.'; return; }
        // The real page checks the unlock rule (Section 10.8) before this point and mounts the components.
        const h = document.createElement('h2'); h.textContent = item.title;
        const p = document.createElement('p'); p.textContent = item.prompt;
        root.replaceChildren(h, p);
      })
      .catch((e) => { root.textContent = `Could not load: ${e.message}`; });
  </script>
</StarlightPage>
```
`src/pages/data/reserved/[topic].json.ts`:
```ts
// Static JSON endpoint: /data/reserved/{topic}.json holds only that topic's reserved exercises.
// Drill, Checkpoint, Review, and Exam components fetch it in the browser on demand.
import type { APIRoute } from 'astro';
import { allExercises, isPractice } from '../../../lib/exercises';

export function getStaticPaths() {
  const topics = [...new Set(allExercises().map((e) => e.topic))];
  return topics.map((topic) => ({ params: { topic } }));
}

export const GET: APIRoute = ({ params }) => {
  const reserved = allExercises().filter((e) => e.topic === params.topic && !isPractice(e));
  return new Response(JSON.stringify(reserved), { headers: { 'Content-Type': 'application/json' } });
};
```

---

## Appendix A: sample LLD card (Strategy), measured in C++

Everything here was compiled with g++ 13 using the flags of `cxxflags.sh` (`-std=c++23 -Wall -Wextra -Wpedantic -Werror`, address and undefined-behaviour sanitizers) and measured with `change_cost.sh` while writing this plan. It is one domain; the lesson needs a second (Section 9.3).

**Behaviour:** an hourly plan at 20 per started hour, and a daily plan at 100 per started day.

Plain design, `naive/base/fee_calculator.hpp`:
```cpp
#pragma once
#include <stdexcept>
#include <string>

class FeeCalculator {
public:
    long long fee(const std::string& plan, long long minutes) const {
        if (plan == "HOURLY") return (minutes + 59) / 60 * 20;
        if (plan == "DAILY") return (minutes + 1439) / 1440 * 100;
        throw std::invalid_argument("unknown plan: " + plan);
    }
};
```

Strategy design, `patterned/base/` (the interface, one plan, and the calculator; `daily_pricing.hpp` mirrors `hourly_pricing.hpp`):
```cpp
#pragma once

// The one signature every pricing plan shares.
class PricingStrategy {
public:
    virtual ~PricingStrategy() = default;   // deleting through a base pointer must run the derived destructor
    virtual long long fee(long long minutes) const = 0;
};
```
```cpp
#pragma once
#include "pricing_strategy.hpp"

class HourlyPricing final : public PricingStrategy {
public:
    long long fee(long long minutes) const override { return (minutes + 59) / 60 * 20; }
};
```
```cpp
#pragma once
#include <map>
#include <memory>
#include <stdexcept>
#include <string>
#include "pricing_strategy.hpp"

class FeeCalculator {
public:
    void add_plan(const std::string& name, std::unique_ptr<PricingStrategy> plan) {
        plans_[name] = std::move(plan);
    }
    long long fee(const std::string& plan, long long minutes) const {
        auto it = plans_.find(plan);
        if (it == plans_.end()) throw std::invalid_argument("unknown plan: " + plan);
        return it->second->fee(minutes);
    }
private:
    std::map<std::string, std::unique_ptr<PricingStrategy>> plans_;
};
```
```cpp
#pragma once
#include <memory>
#include "daily_pricing.hpp"
#include "fee_calculator.hpp"
#include "hourly_pricing.hpp"

// Composition root: the only place that knows which plans exist.
inline FeeCalculator make_calculator() {
    FeeCalculator calc;
    calc.add_plan("HOURLY", std::make_unique<HourlyPricing>());
    calc.add_plan("DAILY", std::make_unique<DailyPricing>());
    return calc;
}
```

**Change scenarios**, applied in order to both designs; the same tests (extended per scenario) pass after each:
1. Add a weekend plan at double the hourly rate.
2. The first 30 minutes are free on the hourly plan.
3. Trucks pay more: hourly doubles and daily adds 50; weekend is unchanged. Every plan now needs the vehicle type, so **the shared signature changes**.

**Measured** (all files in each unit, including `tests.cpp` and `main.cpp`):

| | Plain | Strategy |
|---|---|---|
| Base: files, non-blank lines | 3, 28 | 7, 67 |

| Scenario | Design | Files modified / added | Lines added / removed in modified files | Lines in new files | Blast radius (other behaviours in an edited function or class) |
|---|---|---|---|---|---|
| 1. Weekend plan | Plain | 2 / 0 | 3 / 0 | 0 | 2: HOURLY and DAILY share `FeeCalculator::fee` |
| 1. Weekend plan | Strategy | 2 / 1 | 4 / 0 | 7 | 0: only wiring and tests change |
| 2. First 30 minutes free | Plain | 2 / 0 | 3 / 1 | 0 | 2: DAILY and WEEKEND share `fee` |
| 2. First 30 minutes free | Strategy | 2 / 0 | 3 / 1 | 0 | 0: only `HourlyPricing` changes |
| 3. Trucks (signature change) | Plain | 2 / 0 | 5 / 3 | 0 | 1: WEEKEND shares `fee` |
| 3. Trucks (signature change) | Strategy | **6** / 0 | **12 / 6** | 0 | 1: `WeekendPricing` must change its signature though its behaviour does not |

Raw script output, plain then Strategy:
```
base	files=3	nonblank_lines=28
scenario	files_modified	files_added	files_deleted	lines_added_in_modified	lines_removed_in_modified	lines_in_new_files
01-weekend	2	0	0	3	0	0
02-free30	2	0	0	3	1	0
03-truck	2	0	0	5	3	0
```
```
base	files=7	nonblank_lines=67
scenario	files_modified	files_added	files_deleted	lines_added_in_modified	lines_removed_in_modified	lines_in_new_files
01-weekend	2	1	0	4	0	7
02-free30	2	0	0	3	1	0
03-truck	6	0	0	12	6	0
```

**What the numbers say.**
- **Overhead:** Strategy costs 4 more files and 39 more non-blank lines for two plans.
- **Lines touched** across the three scenarios: plain 15, Strategy 33. Strategy never wins on lines here.
- **Blast radius:** for adding or changing one plan (scenarios 1 and 2), Strategy keeps every other plan's code untouched (0 against 2). For a change to the shared signature (scenario 3), Strategy is clearly worse: 6 files instead of 2, and the blast radius is the same.
- **Verdict:** Strategy buys isolation of plans from each other, paid for in lines and files, and it is fragile to changes in what every plan needs as input. It pays when plans are added or changed often and are tested or owned separately, and the inputs are stable.

```yaml
- id: strategy
  name: "Strategy"
  force: "Behaviour that varies independently of the code that uses it, with variants added or changed over time."
  decisive_property: "All variants fit one function signature that is unlikely to change, and callers do not need to know which variant runs."
  from_claim: "L2.1.2"
  how_to_test: "List the variants and write the one signature they could all share. If the inputs differ per variant, or the inputs are still changing, the property does not hold yet."
  trade_off_table:
    units: ["L2.1/strategy-fee", "L2.1/strategy-notify"]
    overhead: "+4 files and +39 non-blank lines for two plans (fee unit, C++, measured)."
    per_change: "Adding a plan: 11 lines touched against 3. Changing one plan: equal (4 and 4). Changing the shared signature: 18 lines in 6 files against 8 lines in 2 files."
    blast_radius: "Adding or changing a plan: 0 against 2. Changing the signature: 1 against 1."
    verdict: "No single break-even: Strategy costs lines and buys isolation between variants. It pays when variants change often and independently and the shared inputs are stable."
  constraint_shapes:
    - "3 or more variants now, or 2 plus a stated expectation of more; each variant longer than one or two lines; inputs settled"
  weak_signals:
    - form: "The prompt says 'support different' pricing, payment, discount, routing, or sorting rules"
      shape: "At least 3 named kinds, or 'new kinds will be added', and the kinds differ in a calculation or decision, not only in stored data"
    - form: "The prompt says 'depending on the type, plan, or mode, calculate…'"
      shape: "The chosen kind can change per request or per customer"
  kill_signals:
    - "Two variants, no expected change, one line each: the plain function is 39 lines and 4 files smaller (measured)"
    - "The inputs every variant needs are still changing: each change edits every variant class (6 files against 2, measured)"
    - "Variants differ in the data they carry, not in what they do: use fields or subtypes"
  in_action:
    statement: "A parking system charges by an hourly or a daily plan; marketing says weekend plans and promotions will follow."
    constraints: "2 plans now, at least 2 more planned this quarter, each plan tested separately by the finance team; every plan needs only the duration"
    budget: "At least 4 expected edits to pricing per year. In one shared function, each edit touches code that holds every plan."
    candidates:
      - {tool: "Plain function with if/else on the plan name", verdict: rejected, because: "Blast radius grows with each plan; every edit puts the other plans at risk."}
      - {tool: "Strategy", verdict: chosen, because: "The property holds: every plan is fee(minutes), and the input is settled."}
    property_check: "Write the signature: long long fee(long long minutes) const. Hourly, daily, and weekend all fit it, and no planned change adds an input. Yes."
    decision: "Strategy: an abstract PricingStrategy, one final class per plan, a std::map from plan name to std::unique_ptr<PricingStrategy>, filled in the composition root."
  examples:
    positive:
      - inline: {input: "Plans: hourly, daily, weekend, free-first-30-minutes; each tested alone; more promised; all need only the duration", answer: "Strategy", why: "All fit fee(minutes); plans change often and separately."}
      - inline: {input: "Notification channels: email, SMS, push, each with its own sending logic; channels get added", answer: "Strategy", why: "All fit send(message); each is added, replaced, and tested on its own."}
    negative:
      - inline: {input: "Two plans (hourly, daily) fixed by regulation", answer: "Plain function", why: "Strategy adds 4 files and 39 lines and saves nothing when nothing changes."}
        correct_tool: {simplest: "plain function"}
      - inline: {input: "Pricing rules are about to gain vehicle type, membership, and time-of-day inputs", answer: "Plain function for now", why: "The shared signature is unstable; each input change would edit every plan class (measured: 6 files against 2)."}
        correct_tool: {simplest: "plain function"}
  lookalikes:
    - description: "One subclass per variant (inheritance, from L0.3)"
      tool: {topic: "L0.3", card: subtype-per-variant}
      flipping_difference: "A subclass fixes the variant when the object is created; Strategy lets the caller choose or change it at run time and keeps variants separate from the class that uses them."
  cost: "Time: one virtual call per use. Code: see trade_off_table."
```

The solution unit behind Claim L2.1.2 (`code/L2.1/caller-unchanged/`): a new shape class is added without editing the caller.
```cpp
#pragma once
// The shared signature. Callers depend only on this.
class Shape {
public:
    virtual ~Shape() = default;
    virtual double area() const = 0;
};
```
```cpp
#pragma once
#include <memory>
#include <vector>
#include "shape.hpp"

// The caller. This file is never edited when a new Shape is added (Claim L2.1.2).
inline double total_area(const std::vector<std::unique_ptr<Shape>>& shapes) {
    double sum = 0;
    for (const auto& s : shapes) sum += s->area();
    return sum;
}
```
```cpp
#pragma once
#include "shape.hpp"

class Square final : public Shape {
public:
    explicit Square(double side) : side_(side) {}
    double area() const override { return side_ * side_; }
private:
    double side_;
};

// Added later, without touching total_area.hpp.
class Rectangle final : public Shape {
public:
    Rectangle(double w, double h) : w_(w), h_(h) {}
    double area() const override { return w_ * h_; }
private:
    double w_, h_;
};
```
```cpp
#include "check.hpp"
#include "shapes.hpp"
#include "total_area.hpp"

void sums_mixed_shapes() {
    std::vector<std::unique_ptr<Shape>> v;
    v.push_back(std::make_unique<Square>(2));
    v.push_back(std::make_unique<Rectangle>(2, 3));
    CHECK(total_area(v) == 10);
}
void empty_is_zero() { CHECK(total_area({}) == 0); }

int main() {
    RUN(sums_mixed_shapes);
    RUN(empty_is_zero);
    return check::report();
}
```

---

## Appendix B: sample HLD claim and lab (replication quorum), in Go

All of this was run with Go 1.24.7 while writing this plan (D0 re-runs it on Go 1.27): `gofmt` clean, `go vet` clean, `go test -race` passing, and the claim program's output equal to `expected.txt`.

**Claim H4.2.1 (proved).** Suppose a write to a key is acknowledged after W of that key's N replicas have stored it durably, and a read of the key that **starts after the acknowledgement** contacts R of the same N replicas. If W + R > N, at least one replica the read contacts holds that write.
*In plain words:* if the group that confirmed the write and the group that answers the read together have more members than the whole replica set, they share a member, and that member has the write.
*Tiny instance:* N = 3, W = 2, R = 2. The write reached {A, B}. Any 2 of {A, B, C} that a read picks includes A or B.
*Proof:* (1) The write set has W members. (2) The read set has R members. (3) If they shared no member, they would need W + R different replicas. (4) Only N exist and W + R > N, so that is impossible. (5) So some replica is in both sets. (6) It stored the write before the acknowledgement, and the read started later, so it holds the write when the read asks.
:::note[This claim needs]
1. A fixed set of N replicas for the key, the same for the write and the read.
2. A write is acknowledged only after W replicas have stored it durably.
3. The read starts after the write was acknowledged.
4. No replica outside the set stands in for a missing one (no sloppy quorums).
:::
**What the claim does not give.** Returning the write also needs the read to pick the newest of the R replies, which needs versions totally ordered per key (the lab assumes the caller supplies growing versions; clocks on different machines do not guarantee this, H4.1). It says nothing about writes still in flight, or about a failed write that reached fewer than W replicas: one read may see it and a later read may not.

**Claim program** (`code/H4.2/claim-1/main.go`):
```go
// Claim H4.2.1 check: for every N from 1 to 5 and every W, R from 1 to N, every write set of
// size W meets every read set of size R exactly when W + R > N. Prints the number of
// (W, R) pairs where the two disagree; the proof says 0 for every N.
package main

import "fmt"

// subsets returns every subset of {0..n-1} with exactly k members, as bit masks.
func subsets(n, k int) []uint {
	var out []uint
	for m := uint(0); m < 1<<n; m++ {
		bits := 0
		for x := m; x > 0; x &= x - 1 {
			bits++
		}
		if bits == k {
			out = append(out, m)
		}
	}
	return out
}

func main() {
	for n := 1; n <= 5; n++ {
		mismatches := 0
		for w := 1; w <= n; w++ {
			for r := 1; r <= n; r++ {
				always := true
				for _, ws := range subsets(n, w) {
					for _, rs := range subsets(n, r) {
						if ws&rs == 0 {
							always = false
						}
					}
				}
				if always != (w+r > n) {
					mismatches++
				}
			}
		}
		fmt.Printf("N=%d: mismatches with W+R>N rule = %d\n", n, mismatches)
	}
}
```
`expected.txt` (derived from the proof before running):
```
N=1: mismatches with W+R>N rule = 0
N=2: mismatches with W+R>N rule = 0
N=3: mismatches with W+R>N rule = 0
N=4: mismatches with W+R>N rule = 0
N=5: mismatches with W+R>N rule = 0
```

**Lab** (`code/H4.2/lab-quorumkv/`). The mechanism depends only on the `Caller` and `Registrar` interfaces, so it runs on `simnet` (Section 9.6) in tests and over HTTP in `cmd/`.
```go
// Package quorumkv is the H4.2 lab: a key-value store replicated on N nodes with
// write quorum W and read quorum R, running on simnet.
package quorumkv

import (
	"errors"
	"fmt"
	"sync"
)

// Caller sends one request to a node and returns its reply. simnet.Net implements it in tests;
// cmd/client implements it over HTTP for the real multi-process version.
type Caller interface {
	Call(from, to string, req any) (any, error)
}

// Registrar lets a replica receive requests. simnet.Net implements it; cmd/node uses an HTTP server.
type Registrar interface {
	Register(id string, h func(from string, req any) any)
}

// Versioned is a value with its per-key version. The lab assumes the caller supplies
// versions that grow for each key (the claim's stated assumption).
type Versioned struct {
	Value   string
	Version uint64
}

type putReq struct {
	Key string
	V   Versioned
}
type getReq struct{ Key string }

// Replica stores the newest version it has seen of each key.
type Replica struct {
	mu   sync.Mutex
	data map[string]Versioned
}

func NewReplica(net Registrar, id string) *Replica {
	r := &Replica{data: map[string]Versioned{}}
	net.Register(id, r.handle)
	return r
}

func (r *Replica) handle(_ string, req any) any {
	r.mu.Lock()
	defer r.mu.Unlock()
	switch m := req.(type) {
	case putReq:
		if m.V.Version > r.data[m.Key].Version { // keep only newer versions
			r.data[m.Key] = m.V
		}
		return true
	case getReq:
		return r.data[m.Key]
	}
	return nil
}

var ErrNoQuorum = errors.New("quorumkv: not enough replicas answered")

// Client talks to all N replicas in parallel and waits for W (writes) or R (reads) answers.
type Client struct {
	Net      Caller
	ID       string
	Replicas []string
	W, R     int
}

// fanOut calls every replica concurrently and returns the successful replies.
func (c *Client) fanOut(req any) []any {
	var mu sync.Mutex
	var wg sync.WaitGroup
	var replies []any
	for _, id := range c.Replicas {
		wg.Add(1)
		go func(id string) {
			defer wg.Done()
			if resp, err := c.Net.Call(c.ID, id, req); err == nil {
				mu.Lock()
				replies = append(replies, resp)
				mu.Unlock()
			}
		}(id)
	}
	wg.Wait()
	return replies
}

func (c *Client) Put(key string, v Versioned) error {
	if acks := len(c.fanOut(putReq{key, v})); acks < c.W {
		return fmt.Errorf("%w: %d of %d acks", ErrNoQuorum, acks, c.W)
	}
	return nil
}

// Get returns the newest version among the replies, if at least R replicas answered.
func (c *Client) Get(key string) (Versioned, error) {
	replies := c.fanOut(getReq{key})
	if len(replies) < c.R {
		return Versioned{}, fmt.Errorf("%w: %d of %d replies", ErrNoQuorum, len(replies), c.R)
	}
	var best Versioned
	for _, r := range replies {
		if v := r.(Versioned); v.Version > best.Version {
			best = v
		}
	}
	return best, nil
}
```
Tests (`holds`: the first two; `breaks`: the third, where W + R = N and a stale read appears):
```go
package quorumkv

import (
	"errors"
	"fmt"
	"sync"
	"testing"

	"selfengine/code/shared/go/simnet"
)

func setup(w, r int) (*simnet.Net, *Client, *Client) {
	net := simnet.New()
	ids := []string{"A", "B", "C"}
	for _, id := range ids {
		NewReplica(net, id)
	}
	writer := &Client{Net: net, ID: "writer", Replicas: ids, W: w, R: r}
	reader := &Client{Net: net, ID: "reader", Replicas: ids, W: w, R: r}
	return net, writer, reader
}

func TestSurvivesOneReplicaDown(t *testing.T) {
	net, w, r := setup(2, 2)
	net.SetDown("C", true)
	if err := w.Put("k", Versioned{"v1", 1}); err != nil {
		t.Fatal(err)
	}
	got, err := r.Get("k")
	if err != nil || got.Value != "v1" {
		t.Fatalf("got %v, %v; want v1", got, err)
	}
}

// W + R > N: the write reached {A, B}; the read reaches {B, C}; they share B.
func TestReadMeetsAcknowledgedWrite(t *testing.T) {
	net, w, r := setup(2, 2)
	net.Partition("writer", "C", true)
	if err := w.Put("k", Versioned{"v1", 1}); err != nil {
		t.Fatal(err)
	}
	net.Partition("reader", "A", true)
	got, err := r.Get("k")
	if err != nil || got.Value != "v1" {
		t.Fatalf("got %v, %v; want v1", got, err)
	}
}

// W + R = 2, not greater than 3: the write reached only A; the read reaches only C.
func TestW1R1CanReturnStale(t *testing.T) {
	net, w, r := setup(1, 1)
	net.Partition("writer", "B", true)
	net.Partition("writer", "C", true)
	if err := w.Put("k", Versioned{"v1", 1}); err != nil {
		t.Fatal(err)
	}
	net.Partition("reader", "A", true)
	net.Partition("reader", "B", true)
	got, err := r.Get("k")
	if err != nil {
		t.Fatal(err)
	}
	if got.Value != "" {
		t.Fatalf("expected a stale (empty) read, got %v", got)
	}
}

func TestNoQuorumWithTwoDown(t *testing.T) {
	net, w, _ := setup(2, 2)
	net.SetDown("B", true)
	net.SetDown("C", true)
	if err := w.Put("k", Versioned{"v1", 1}); !errors.Is(err, ErrNoQuorum) {
		t.Fatalf("got %v, want ErrNoQuorum", err)
	}
}

// Run with -race: many clients writing different keys at once.
func TestConcurrentClients(t *testing.T) {
	net, _, _ := setup(2, 2)
	var wg sync.WaitGroup
	for i := 0; i < 50; i++ {
		wg.Add(1)
		go func(i int) {
			defer wg.Done()
			c := &Client{Net: net, ID: fmt.Sprintf("c%d", i), Replicas: []string{"A", "B", "C"}, W: 2, R: 2}
			key := fmt.Sprintf("k%d", i%5)
			if err := c.Put(key, Versioned{"x", uint64(i + 1)}); err != nil {
				t.Error(err)
			}
			if _, err := c.Get(key); err != nil {
				t.Error(err)
			}
		}(i)
	}
	wg.Wait()
}
```

**Availability (computed).** Each replica up with probability 0.999, independently: P(at least k of n up) = Σ C(n, i) × 0.999^i × 0.001^(n−i), for i from k to n.
| Setup | Probability an operation can proceed | Expected downtime per 30-day month |
|---|---|---|
| 1 machine | 0.999 | 43.2 minutes |
| N = 3, W = R = 2 | 0.999997 | about 0.13 minutes (8 seconds) |
| N = 5, W = R = 3 | 0.99999999 | about 0.0004 minutes (0.03 seconds) |
Independence is an assumption (machines in one rack or zone fail together); the lesson states it and a kill signal covers it. In the lab's "Run it" step, Saurabh kills one of three node processes and watches writes and reads continue, then kills a second and watches them fail with `ErrNoQuorum`.

```yaml
- id: quorum-replication
  name: "Quorum replication"
  need: "Acknowledged writes must survive machine failures and be visible to reads that start after the acknowledgement, while reads and writes keep working with a minority of replicas down."
  decisive_property: "W + R > N over a fixed replica set; writes acknowledged after W durable copies; reads start after the acknowledgement and return the newest of R replies by a per-key total order of versions; no substitute replicas."
  from_claim: "H4.2.1"
  how_to_test: "Write down N, W, and R and check W + R > N. Then check the four conditions in the claim's box, and how versions are ordered."
  lab: {unit: "H4.2/lab-quorumkv", holds_test: "TestReadMeetsAcknowledgedWrite", breaks_test: "TestW1R1CanReturnStale"}
  capacity_table:
    units: ["H4.2/calc-quorum-table"]
    threshold: "Needed when the availability target exceeds what one machine gives: 0.999 is 43.2 minutes down per month."
    price: "Each write waits for the W-th fastest of N replies and each read for the R-th fastest; N = 3, W = R = 2 survives 1 failure for both."
  constraint_shapes:
    - "Availability target of 99.99% or more (at most about 4.3 minutes down per month) for single-key reads and writes"
  weak_signals:
    - form: "The prompt says 'no single point of failure' and 'a read after a successful write must see it'"
      shape: "Operations touch one key at a time; the write rate fits within one replica group"
    - form: "The prompt says 'keep working when one zone is down'"
      shape: "Three or more zones; single-key operations"
  kill_signals:
    - "Operations must change several keys together: quorums give per-key guarantees only"
    - "Every read must agree on one order of writes even while writes are in flight: W + R > N alone does not give that"
    - "One primary with synchronous replication already meets the availability target and its failover time is acceptable: simpler"
    - "Replicas share a failure domain (one rack or zone): the availability table's independence assumption is false"
  in_action:
    statement: "Store user session records. An acknowledged write must not be lost; a machine may die at any time; reads are 5 times as frequent as writes."
    constraints: "20 000 writes per second, 100 000 reads per second, three zones, 99.999% availability for single-key operations; each write of a key carries a version larger than every earlier one (stated assumption)"
    budget: "One machine gives 0.999 (43.2 minutes down per month). 99.999% allows about 0.43 minutes per month."
    candidates:
      - {tool: "Single machine", verdict: rejected, because: "0.999 is below the target."}
      - {tool: "Quorum replication, N = 3, W = 2, R = 2", verdict: chosen, because: "0.999997 by the table, above 0.99999; W + R = 4 > 3."}
    property_check: "Fixed set of 3 replicas, one per zone; writes acknowledged after 2 durable copies; reads take the newest of 2 replies by version; no substitute replicas. All conditions hold."
    decision: "N = 3, W = 2, R = 2, one replica per zone."
  examples:
    positive:
      - inline: {input: "N = 3, W = 2, R = 2", answer: "Every read set meets every write set", why: "W + R = 4 > 3 (lab: TestReadMeetsAcknowledgedWrite)."}
      - inline: {input: "N = 5, W = 3, R = 3", answer: "Every read set meets every write set, and 2 failures are tolerated", why: "W + R = 6 > 5; 3 of 5 still form both quorums."}
    negative:
      - inline: {input: "N = 3, W = 1, R = 1", answer: "A read can miss the write", why: "W + R = 2 is not greater than 3 (lab: TestW1R1CanReturnStale)."}
        correct_tool: {topic: "H2.3", card: leader-follower-replication}
      - inline: {input: "Two keys must be updated together; N = 3, W = 2, R = 2", answer: "Quorums do not make the pair atomic", why: "The guarantee is per key."}
        correct_tool: {topic: "H1.3", card: transaction-isolation}
  lookalikes:
    - description: "Leader–follower replication with asynchronous followers"
      tool: {topic: "H2.3", card: leader-follower-replication}
      flipping_difference: "Follower reads can lag the leader, and writes stop while a failed leader is replaced; quorum reads and writes continue with a minority down but need W + R > N for reads to meet writes."
  cost: "Write latency is the W-th fastest of N replies, read latency the R-th fastest. A smaller W lowers write latency and raises the chance a read misses the write unless R grows to match."
```

---

## Appendix C: sample HLD lab kit (token bucket), in Go

The H5.6 lab's first rung kit (`H5.6/lab/rung-1`), exactly as it was run through `exercise_kit_check.sh` while writing this plan: the tests fail on the starter, pass on the reference, and catch all three mutants: **m1** (no cap, so a long idle period allows a burst larger than the bucket) fails `TestIdleNeverExceedsBurst`; **m2** (no lock) is caught only by the race detector in `TestConcurrentCallersShareTokens`; **m3** (refill rounded down to whole tokens each call) fails `TestRefillsAtRate`.

`exercises/H5.6/lab/rung-1/test.sh`:
```bash
#!/usr/bin/env bash
# usage: bash test.sh <solution-dir>   Runs the kit's tests (with the race detector) against the
# solution's non-test .go files, in a throwaway module, so the learner's folder is never modified.
# The throwaway module uses the same Go version as the repository's code/go.mod.
set -euo pipefail
KIT="$(cd "$(dirname "${BASH_SOURCE[0]}")" && pwd)"
SOL="$(cd "$1" && pwd)"
R="$KIT"; while [ "$R" != "/" ] && [ ! -f "$R/code/go.mod" ]; do R="$(dirname "$R")"; done
GOV="$(sed -n 's/^go //p' "$R/code/go.mod")"
[ -n "$GOV" ] || { echo "code/go.mod not found or has no go line" >&2; exit 2; }
W="$(mktemp -d)"; trap 'rm -rf "$W"' EXIT
find "$SOL" -maxdepth 1 -name '*.go' ! -name '*_test.go' -exec cp {} "$W"/ \;
cp "$KIT"/tests/*_test.go "$W"/
printf 'module kit\n\ngo %s\n' "$GOV" > "$W/go.mod"
cd "$W"
go vet ./...
go test -race -count=1 ./...
```
`starter/bucket.go`:
```go
// Package ratelimit: implement a token bucket (see README.md).
package ratelimit

import "time"

type Bucket struct{}

// New returns a bucket that refills at rate tokens per second, holds at most burst tokens,
// starts full, and reads the time from now (tests pass a fake clock).
func New(rate float64, burst int, now func() time.Time) *Bucket { panic("not implemented") }

// Allow takes one token if one is available and reports whether it did. Safe for concurrent use.
func (b *Bucket) Allow() bool { panic("not implemented") }
```
`tests/bucket_test.go`:
```go
package ratelimit

import (
	"sync"
	"sync/atomic"
	"testing"
	"time"
)

// fakeClock lets a test move time forward by hand.
type fakeClock struct {
	mu sync.Mutex
	t  time.Time
}

func (c *fakeClock) Now() time.Time { c.mu.Lock(); defer c.mu.Unlock(); return c.t }
func (c *fakeClock) Advance(d time.Duration) { c.mu.Lock(); c.t = c.t.Add(d); c.mu.Unlock() }

func TestStartsFullThenDenies(t *testing.T) {
	c := &fakeClock{t: time.Unix(0, 0)}
	b := New(1, 3, c.Now)
	for i := 0; i < 3; i++ {
		if !b.Allow() {
			t.Fatalf("request %d denied; want the first 3 allowed", i+1)
		}
	}
	if b.Allow() {
		t.Fatal("4th request allowed; want denied")
	}
}

func TestRefillsAtRate(t *testing.T) {
	c := &fakeClock{t: time.Unix(0, 0)}
	b := New(2, 1, c.Now) // 2 tokens per second
	b.Allow()
	c.Advance(400 * time.Millisecond) // 0.8 tokens
	if b.Allow() {
		t.Fatal("allowed after 0.4s; want denied")
	}
	c.Advance(100 * time.Millisecond) // 0.8 + 0.2 = 1.0 token: fractions must not be lost
	if !b.Allow() {
		t.Fatal("denied after 0.5s in total; want allowed")
	}
}

func TestIdleNeverExceedsBurst(t *testing.T) {
	c := &fakeClock{t: time.Unix(0, 0)}
	b := New(10, 2, c.Now)
	c.Advance(time.Hour)
	n := 0
	for b.Allow() {
		n++
	}
	if n != 2 {
		t.Fatalf("allowed %d after a long idle; want 2 (the burst)", n)
	}
}

func TestConcurrentCallersShareTokens(t *testing.T) {
	c := &fakeClock{t: time.Unix(0, 0)}
	b := New(1, 100, c.Now)
	var allowed atomic.Int64
	var wg sync.WaitGroup
	for i := 0; i < 400; i++ {
		wg.Add(1)
		go func() {
			defer wg.Done()
			if b.Allow() {
				allowed.Add(1)
			}
		}()
	}
	wg.Wait()
	if got := allowed.Load(); got != 100 {
		t.Fatalf("allowed %d; want exactly 100", got)
	}
}
```
`reference/H5.6/lab/rung-1/bucket.go`:
```go
// Package ratelimit is a token bucket: tokens refill continuously at a fixed rate up to a cap (burst),
// and each allowed request spends one token.
package ratelimit

import (
	"sync"
	"time"
)

type Bucket struct {
	mu     sync.Mutex
	rate   float64 // tokens per second
	burst  float64 // capacity
	tokens float64 // current tokens, fractional so slow refills are not lost
	last   time.Time
	now    func() time.Time
}

func New(rate float64, burst int, now func() time.Time) *Bucket {
	return &Bucket{rate: rate, burst: float64(burst), tokens: float64(burst), last: now(), now: now}
}

func (b *Bucket) Allow() bool {
	b.mu.Lock()
	defer b.mu.Unlock()
	t := b.now()
	b.tokens += t.Sub(b.last).Seconds() * b.rate
	if b.tokens > b.burst {
		b.tokens = b.burst
	}
	b.last = t
	if b.tokens >= 1 {
		b.tokens--
		return true
	}
	return false
}
```
