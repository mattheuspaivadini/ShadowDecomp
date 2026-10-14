/* STATUS (Session 7, 2026-10-14): NON_MATCHING. best score 9 [cc=29, default].
 * shutdown sequence; merged second routine not derivable from C.
 * The original .s stays in the build (asm/cod/001A50.s); this C
 * draft (subagent-produced, Session 7) is kept for the record. */
/* asm/cod/001A50.s -> func_00101A50 @ 0x00101A50 (0x70 bytes declared, 28
 * insns; the reachable part is the first 16 insns, 0x00101A50-0x00101A9C)
 *
 * Shutdown / report routine of the 0x00101xxx "system" cluster:
 *
 *   func_00102608();                             ; tear the sub-systems down
 *   func_00105948(0xFF603000, D_00139E50);       ; variadic report ("\n")
 *   func_00106E70(func_00106ED0(), 0x7F);        ; syscall stub 0x29 (arg 0x2F)
 *   func_00106F10(D_0013A084);                   ; syscall stub 0x33
 *   for (;;)
 *       func_00106F00();                         ; syscall stub 0x32 (idle)
 *
 * D_00139E50 is the 4-byte .sdata string "\n" but the image addresses it
 * absolutely (lui/%hi + addiu %lo), so it must be declared non-small (unknown
 * size array); D_0013A084 is a gp-relative (.sdata) scalar.
 *
 * RESIDUAL: the declared 0x70 span also contains a *second* routine at
 * 0x00101AA0 (`addiu $sp,-0x10; addiu $a1,$ra,-0x8; ...; j func_00100C80`),
 * which splat merged into this subsegment.  It is a real, separately
 * registered handler - 0x00101AA0 is materialised as a function pointer by
 * func_00100D48 (asm/cod/000D48.s:173) and func_00101190 (asm/cod/001190.s:46)
 * - and it is unreachable from func_00101A50's infinite loop, so no C body of
 * func_00101A50 can emit those 12 instructions.  Expect a ~12-instruction
 * residual.
 * MATCH GUESS: cc=296 (0x00101xxx cluster; the jal delay slots are `nop`) */
extern char D_00139E50[];       /* .sdata "\n", addressed absolutely here */
extern int D_0013A084;          /* .sdata scalar: gp-relative */

void func_00102608(void);
void func_00105948(int a0, int a1, ...);
int func_00106ED0(void);
int func_00106E70(int a0, int a1);
int func_00106F10(int a0);
void func_00106F00(void);

void func_00101A50(void) {
    func_00102608();
    func_00105948(0xFF603000, (int)D_00139E50);
    func_00106E70(func_00106ED0(), 0x7F);
    func_00106F10(D_0013A084);
    for (;;)
        func_00106F00();
}
