#!/bin/bash
# STEP 5, attempt 2: run REA with a correctly-translated Windows path and check
# whether a Linux Ghidra lane is bundled at all.
set -u
REA_WIN='C:\Users\Matheus\AppData\Roaming\npm\node_modules\rea-agents'
REA=/mnt/c/Users/Matheus/AppData/Roaming/npm/node_modules/rea-agents
NODE='/mnt/c/Program Files/nodejs/node.exe'

echo "== attempt 2a: rea open_binary on the ELF, from WSL via interop"
"$NODE" "${REA_WIN}\\scripts\\rea.mjs" doctor 2>&1 | head -20

echo
echo "== attempt 2b: is a Linux Ghidra / linux-x86_64 ghidra dist bundled?"
find "$REA" -maxdepth 3 -type d \( -name 'ghidra*' -o -name 'linux*' \) 2>/dev/null | head -10
echo -n "bundled ghidra provider files: "
ls "$REA/dist/ghidra" 2>/dev/null | head -5
echo -n "GHIDRA_INSTALL_DIR visible to WSL: "; echo "${GHIDRA_INSTALL_DIR:-(unset)}"
echo -n "windows Ghidra install: "; ls -d /mnt/c/Users/Matheus/ghidra/ghidra_12.1.4_PUBLIC 2>/dev/null || echo "(none)"
echo -n "java in WSL: "; command -v java || echo "(none)"
