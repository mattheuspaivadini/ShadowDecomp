// Produce a complete linear disassembly of every executable memory block, which
// is the ground-truth listing for a fixed-width ISA such as MIPS. Undefined
// opcodes (e.g. R5900 MMI / COP2 that the stock MIPS language does not decode)
// are emitted as `.word 0x........`.
//
// MIPS instructions are always 4 bytes, so a linear sweep never misaligns; the
// only loss is unknown mnemonics.
//
// Usage (headless):
//   analyzeHeadless <projDir> <projName> -process <progName> -noanalysis \
//       -scriptPath tools/ghidra_scripts -postScript LinearDisasm.java <outDir>
//
// @category ShadowDecomp

import ghidra.app.script.GhidraScript;
import ghidra.program.model.address.Address;
import ghidra.program.model.listing.Instruction;
import ghidra.program.model.listing.Listing;
import ghidra.program.model.mem.Memory;
import ghidra.program.model.mem.MemoryBlock;

import java.io.File;
import java.io.FileWriter;
import java.io.PrintWriter;

public class LinearDisasm extends GhidraScript {

    @Override
    public void run() throws Exception {
        String[] args = getScriptArgs();
        File dir = new File(args.length > 0 ? args[0] : ".");
        if (!dir.exists() && !dir.mkdirs()) {
            throw new RuntimeException("could not create output directory: " + dir);
        }

        Memory mem = currentProgram.getMemory();
        Listing listing = currentProgram.getListing();

        File out = new File(dir, "linear.txt");
        long total = 0;
        long undefinedWords = 0;

        try (PrintWriter w = new PrintWriter(new FileWriter(out))) {
            w.printf("; linear disassembly of %s%n", currentProgram.getName());
            for (MemoryBlock b : mem.getBlocks()) {
                if (!b.isExecute() || !b.isInitialized()) {
                    continue;
                }
                Address start = b.getStart();
                Address end = b.getEnd();
                w.printf("; --- block %s 0x%08x..0x%08x (len 0x%x) ---%n",
                        b.getName(), start.getOffset(), end.getOffset(), b.getSize());
                clearListing(start, end);
                Address a = start;
                while (a.compareTo(end) <= 0) {
                    boolean ok = false;
                    try {
                        ok = disassemble(a);
                    } catch (Exception e) {
                        ok = false;
                    }
                    if (ok) {
                        Instruction ins = listing.getInstructionAt(a);
                        if (ins != null) {
                            w.printf("%s  %s%n", a.toString(), ins.toString());
                            a = a.add(ins.getLength());
                            total++;
                            continue;
                        }
                    }
                    // Undefined opcode: emit the raw word and advance 4 bytes.
                    try {
                        int word = mem.getInt(a);
                        w.printf("%s  .word 0x%08x%n", a.toString(), word);
                    } catch (Exception e) {
                        w.printf("%s  .byte 0x%02x%n", a.toString(), mem.getByte(a) & 0xff);
                    }
                    undefinedWords++;
                    a = a.add(4);
                }
            }
        }
        println("LinearDisasm: " + total + " instructions, " + undefinedWords
                + " undefined words -> " + out.getAbsolutePath());
    }
}
