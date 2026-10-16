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
    bash "$0" sync
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
    bash "$0" sync
    remote "bash exercises/$k/test.sh $sol" ;;
  experiment)
    pkg="${1:?go package, e.g. ./H0.4/lab-queue/experiments/sweep}"; shift
    bash "$0" sync
    out="$(date +%F)-labserver.txt"
    remote "set -o pipefail; mkdir -p code/$pkg/results && cd code && go run $pkg $* | tee $pkg/results/$out"
    mkdir -p "$ROOT/code/$pkg/results"
    remote "tar -C code/$pkg/results -czf - $out" | tar -C "$ROOT/code/$pkg/results" -xzf -
    echo "results copied to code/$pkg/results/$out" ;;
  exec) require_mirror; remote "$*" ;;
  *) sed -n '2,17p' "$0"; exit 2 ;;
esac
