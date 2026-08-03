#!/bin/bash
# Build the standalone block-drop harness against whatever the working tree
# currently contains. Output: tools/blockdrop/blockdrop_test
set -euo pipefail

ROOT="$(cd "$(dirname "$0")/../.." && pwd)"
OUT="${1:-$ROOT/tools/blockdrop/blockdrop_test}"

CXXFLAGS="-O2 -std=c++17 -Wno-multichar"
CFLAGS="-O2"

TMP="$(mktemp -d)"
trap 'rm -rf "$TMP"' EXIT

for c in filterkit resample resamplesubs; do
  cc $CFLAGS -c "$ROOT/Source/emulator/resample/$c.c" -o "$TMP/$c.o"
done

OBJS=("$TMP"/*.o)
c++ $CXXFLAGS \
  "$ROOT/tools/blockdrop/blockdrop_test.cpp" \
  "$ROOT/Source/emulator/mcu.cpp" \
  "$ROOT/Source/emulator/mcu_opcodes.cpp" \
  "$ROOT/Source/emulator/mcu_interrupt.cpp" \
  "$ROOT/Source/emulator/mcu_timer.cpp" \
  "$ROOT/Source/emulator/pcm.cpp" \
  "$ROOT/Source/emulator/lcd.cpp" \
  "$ROOT/Source/emulator/submcu.cpp" \
  "${OBJS[@]}" \
  -o "$OUT"

echo "built $OUT"
