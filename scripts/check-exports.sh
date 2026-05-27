#!/usr/bin/env bash
# Drop-in export audit: assert the NEW dll's exported symbols are a superset of the GOLDEN
# dll's. Usage: scripts/check-exports.sh <golden.dll> <new.dll>
#
# Run only against an MSVC-ABI build (clang-cl / clang-cl-xwin / msvc): C++ name mangling must
# match the golden binary. The llvm-mingw build uses Itanium mangling and is NOT comparable.
set -euo pipefail

GOLDEN="${1:?usage: check-exports.sh <golden.dll> <new.dll>}"
NEW="${2:?usage: check-exports.sh <golden.dll> <new.dll>}"

# MSVC's cl.exe synthesizes internal helper members on dllexport classes that clang-cl emits
# inline and never exports, e.g. __autoclassinit / __autoclassinit2 (the member zero-init
# helpers). These are compiler-internal, never part of the consumable API, and no consumer
# imports them, so they are excluded from the drop-in comparison on both sides.
MSVC_INTERNAL_RE='__autoclassinit'

raw_exports()  { llvm-readobj --coff-exports "$1" | sed -n 's/^[[:space:]]*Name: //p' | sort -u; }
dump_exports() { raw_exports "$1" | { grep -Ev "$MSVC_INTERNAL_RE" || true; }; }

golden_file="$(mktemp)"; new_file="$(mktemp)"
trap 'rm -f "$golden_file" "$new_file"' EXIT
dump_exports "$GOLDEN" > "$golden_file"
dump_exports "$NEW"    > "$new_file"

echo "golden: $(wc -l < "$golden_file") API exports ($GOLDEN)"
echo "new:    $(wc -l < "$new_file") API exports ($NEW)"

excluded="$(raw_exports "$GOLDEN" | { grep -E "$MSVC_INTERNAL_RE" || true; })"
if [ -n "$excluded" ]; then
    echo "excluded compiler-internal symbols (not part of the API contract):"
    printf '%s\n' "$excluded"
fi

added="$(comm -13 "$golden_file" "$new_file")"
missing="$(comm -23 "$golden_file" "$new_file")"

if [ -n "$added" ]; then
    echo "exports ADDED vs golden (informational):"
    printf '%s\n' "$added"
fi

if [ -n "$missing" ]; then
    echo "FAIL: golden API exports MISSING from new DLL (drop-in violation):"
    printf '%s\n' "$missing"
    exit 1
fi

echo "OK: new DLL exports are a superset of golden (excluding compiler-internal symbols)."
