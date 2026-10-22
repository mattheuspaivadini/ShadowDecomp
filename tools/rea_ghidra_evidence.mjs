// Turn the Ghidra Emotion Engine export (docs/plan/ghidra/ExportAll.java output)
// into a REA evidence bundle, so REA's provider-independent tools
// (import_evidence_bundle, record_unknown, build_reconstruction_obligation_ledger,
// ...) can work on SCUS_974.72 even though every REA native lane rejects R5900.
//
// Each function becomes one REA analyze_function dossier (Ghidra pseudo-C, call
// graph and strings plus the splat asm/ listing), checked against REA's own
// functionDossierSchema and sealed with createEvidence, so evidence ids validate
// on import and inspect_analysis_view facets work.
//
// Usage:
//   node tools/rea_ghidra_evidence.mjs [ghidraOutDir] [elf] [outBundle]
// Defaults: build/plan/ghidra_out/SCUS_974.72  extracted/SCUS_974.72
//           build/rea/ghidra-ee-evidence.json
// REA is loaded from $REA_DIST, else `npm root -g`/rea-agents/dist.

import { execSync } from "node:child_process";
import { createHash } from "node:crypto";
import { existsSync, mkdirSync, readFileSync, writeFileSync } from "node:fs";
import { dirname, join, resolve } from "node:path";
import { pathToFileURL } from "node:url";

const [ghidraOut = "build/plan/ghidra_out/SCUS_974.72", elf = "extracted/SCUS_974.72",
       outPath = "build/rea/ghidra-ee-evidence.json"] = process.argv.slice(2);

const dist = process.env.REA_DIST ??
    join(execSync("npm root -g", { encoding: "utf8" }).trim(), "rea-agents", "dist");
const load = (rel) => import(pathToFileURL(join(dist, rel)).href);
const { createEvidence } = await load("domain/evidence.js");
const { createEvidenceBundle, serializeEvidenceBundle } = await load("domain/evidenceBundle.js");
const { functionDossierSchema } = await load("domain/hopperValues.js");

const tsv = (name) => readFileSync(join(ghidraOut, name), "utf8")
    .split(/\r?\n/).slice(1).filter(Boolean).map((l) => l.split("\t"));
const hex = (n) => "0x" + n.toString(16).padStart(8, "0");

const funcs = tsv("functions.tsv").map(([addr, size, name, , , signature]) =>
    ({ start: Number(addr), size: Number(size), name, signature, callers: [], callees: [], strings: [] }))
    .sort((a, b) => a.start - b.start);
const byAddr = new Map(funcs.map((f) => [f.start, f]));
const containing = (x) => {
    let lo = 0, hi = funcs.length - 1;
    while (lo <= hi) {
        const mid = (lo + hi) >> 1;
        if (funcs[mid].start <= x) lo = mid + 1; else hi = mid - 1;
    }
    const f = funcs[hi];
    return f && x < f.start + f.size ? f : undefined;
};

for (const [caller, callerName, callee, calleeName] of tsv("callgraph.tsv")) {
    byAddr.get(Number(caller))?.callees.push({ address: hex(Number(callee)), name: calleeName });
    byAddr.get(Number(callee))?.callers.push({ address: hex(Number(caller)), name: callerName });
}
for (const [strAddr, , literal, xrefs = ""] of tsv("strings_xrefs.tsv"))
    for (const x of xrefs.split(/[ ,;]+/).filter(Boolean))
        containing(Number(x))?.strings.push({ address: hex(Number(strAddr)), from: hex(Number(x)), literal });

const elfBytes = readFileSync(elf);
const target = {
    path: resolve(elf).replaceAll("\\", "/"),
    sha256: createHash("sha256").update(elfBytes).digest("hex"),
    format: "elf",
    architecture: "mips",
};
const provider = {
    id: "ghidra-emotionengine",
    name: "Ghidra headless + ghidra-emotionengine-reloaded (r5900:LE:32:default)",
    version: "ghidra-12.1.4/ee-2.1.38",
};
const limitations = [
    "Produced outside REA by headless Ghidra with the Emotion Engine extension; REA's own native lanes reject R5900 (MIPS III + MMI) targets.",
    "Pseudo-C is a hint only: byte-exact matching is decided by EE-GCC and build/s10/verify_fast.py.",
    "Function boundaries come from Ghidra auto-analysis; config/symbol_addrs.txt is authoritative.",
];

// Ghidra's body is an address count, not ranges, so REA gets it as unavailable.
const noBody = { available: false, reason: "Ghidra EE export records entry and address count only." };
const ident = ({ address, name }) => ({ address, name, classification: null, body: noBody });
const off = { available: false, reason: "Not exported by the Ghidra EE pipeline." };

const records = funcs.map((f) => {
    const stem = (f.start >= 0x100000 && f.start < 0x200000 ? f.start - 0x100000 : f.start)
        .toString(16).toUpperCase().padStart(6, "0");
    const pseudo = join(ghidraOut, "pseudo", stem + ".c");
    const asm = join("asm", "cod", stem + ".s");
    const dossier = {
        procedure: { ...ident({ address: hex(f.start), name: f.name }), signature: f.signature || null, locals: [] },
        pseudocode: existsSync(pseudo) ? readFileSync(pseudo, "utf8") : "",
        // Assembly is the repository's splat listing, which is authoritative for matching.
        assembly: existsSync(asm) ? readFileSync(asm, "utf8").split(/\r?\n/).filter((l) => l.startsWith("    /*")) : [],
        comments: [],
        callers: f.callers.map(ident),
        callees: f.callees.map(ident),
        incoming_references: [],
        outgoing_references: [],
        referenced_strings: f.strings.map((s) => ({ address: s.address, value: s.literal, source_address: s.from })),
        referenced_names: [],
        basic_blocks: [],
        native_api: null,
        native_value_flow: { available: false, reason: "Ghidra EE export carries no value-flow facts.", limitations: [] },
        facet_availability: { comments: off, references: off, cfg: off },
        limitations,
    };
    if (!dossier.pseudocode) dossier.facet_availability.pseudocode = off;
    if (!dossier.assembly.length) dossier.facet_availability.assembly = off;
    const checked = functionDossierSchema.safeParse(dossier);
    if (!checked.success) throw new Error(`${stem}: ${checked.error.message}`);
    return createEvidence(target, provider, {
        operation: "analyze_function",
        parameters: { procedure: hex(f.start) },
        result: dossier,
        confidence: "derived",
        limitations,
        locations: [{ kind: "address", address: hex(f.start) }],
    });
});

mkdirSync(dirname(outPath), { recursive: true });
writeFileSync(outPath, serializeEvidenceBundle(createEvidenceBundle(records)));
console.log(`rea_ghidra_evidence: ${records.length} records -> ${resolve(outPath)}`);
