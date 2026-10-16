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
