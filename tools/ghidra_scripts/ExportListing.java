// Export a Ghidra program's function inventory, string inventory, and full
// disassembly listing to plain text for the decompilation pipeline.
//
// Usage (headless):
//   analyzeHeadless <projDir> <projName> -process <progName> -noanalysis \
//       -scriptPath tools/ghidra_scripts -postScript ExportListing.java <outDir>
//
// @category ShadowDecomp

import ghidra.app.script.GhidraScript;
import ghidra.program.model.address.Address;
import ghidra.program.model.listing.Data;
import ghidra.program.model.listing.DataIterator;
import ghidra.program.model.listing.Function;
import ghidra.program.model.listing.FunctionIterator;
import ghidra.program.model.listing.Instruction;
import ghidra.program.model.listing.InstructionIterator;
import ghidra.program.model.listing.Listing;

import java.io.File;
import java.io.FileWriter;
import java.io.PrintWriter;

public class ExportListing extends GhidraScript {

    @Override
    public void run() throws Exception {
        String[] args = getScriptArgs();
        String outPath = (args.length > 0) ? args[0] : ".";
        File dir = new File(outPath);
        if (!dir.exists() && !dir.mkdirs()) {
            throw new RuntimeException("could not create output directory: " + dir);
        }

        // ---- Functions -------------------------------------------------
        File fFn = new File(dir, "functions.txt");
        int nFn = 0;
        try (PrintWriter w = new PrintWriter(new FileWriter(fFn))) {
            FunctionIterator it = currentProgram.getFunctionManager().getFunctions(true);
            while (it.hasNext()) {
                Function f = it.next();
                long size = f.getBody().getNumAddresses();
                w.printf("0x%08x %6d %s%n", f.getEntryPoint().getOffset(), size, f.getName());
                nFn++;
            }
        }
        println("ExportListing: " + nFn + " functions -> " + fFn.getName());

        // ---- Strings ---------------------------------------------------
        File fStr = new File(dir, "strings.txt");
        int nStr = 0;
        try (PrintWriter w = new PrintWriter(new FileWriter(fStr))) {
            Listing listing = currentProgram.getListing();
            DataIterator it = listing.getDefinedData(true);
            while (it.hasNext()) {
                Data d = it.next();
                Object v = d.getValue();
                if (v instanceof String) {
                    String s = ((String) v).replace("\\", "\\\\").replace("\n", "\\n").replace("\r", "\\r");
                    w.printf("0x%08x %s%n", d.getAddress().getOffset(), s);
                    nStr++;
                }
            }
        }
        println("ExportListing: " + nStr + " strings -> " + fStr.getName());

        // ---- Full disassembly listing ---------------------------------
        File fLs = new File(dir, "listing.txt");
        long nIns = 0;
        try (PrintWriter w = new PrintWriter(new FileWriter(fLs))) {
            Listing listing = currentProgram.getListing();
            Address min = currentProgram.getMinAddress();
            InstructionIterator it = listing.getInstructions(min, true);
            while (it.hasNext()) {
                Instruction ins = it.next();
                w.printf("%s  %s%n", ins.getAddress().toString(), ins.toString());
                nIns++;
            }
        }
        println("ExportListing: " + nIns + " instructions -> " + fLs.getName());
        println("ExportListing: done, output in " + dir.getAbsolutePath());
    }
}
