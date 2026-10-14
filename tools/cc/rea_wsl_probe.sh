#!/bin/bash
# STEP 5 (Session 3): attempt to run REA inside WSL2 (Linux host) so the
# win32-only PE gate in REA's Ghidra provider no longer applies.
set -u
echo "== 1. host + node availability"
echo "uname: $(uname -srm)"
echo -n "node on PATH: "; command -v node || echo "(none)"
echo -n "linux node candidates: "; ls /usr/bin/node /usr/local/bin/node 2>/dev/null || echo "(none)"
echo -n "windows node.exe via interop: "
if [ -x "/mnt/c/Program Files/nodejs/node.exe" ]; then
  "/mnt/c/Program Files/nodejs/node.exe" -e 'console.log(process.platform, process.arch, process.version)'
else
  echo "(not executable)"
fi

echo
echo "== 2. REA install location (Windows npm global)"
REA_DIR=/mnt/c/Users/Matheus/AppData/Roaming/npm/node_modules/rea-agents
ls "$REA_DIR/scripts" 2>/dev/null | head -5
echo -n "rea version: "; sed -n 's/.*"version": "\([^"]*\)".*/\1/p' "$REA_DIR/package.json" 2>/dev/null | head -1

echo
echo "== 3. run the REA CLI through windows node.exe from inside WSL"
"/mnt/c/Program Files/nodejs/node.exe" "$REA_DIR/scripts/rea.mjs" doctor 2>&1 | head -25
