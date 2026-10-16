/* asm/cod/015D28.s -> func_00115D28 @ 0x00115D28 (0x48 bytes, 18 insns)
 * One-shot flag handler: `bnez D_00133A28` -> return 0 (the `b` to the shared
 * epilogue with `daddu $v0,$zero,$zero`); otherwise clear the flag, load the
 * signed handle D_00150DC0, `bltz` -> return 1, else reset it through the
 * syscall stub func_00106FF0 (syscall 0x41) and return 1.  The two separate
 * `addiu $v0,$zero,1` materialisations are the two `return 1;` sites (the
 * second one is after the call, so the value is not kept in a saved register).
 * MATCH GUESS: cc=29 (0x015008/0x0183xx wrapper tier; weak) */
extern int D_00133A28[];   /* .data 0x00133A28: lui/%lo (non-small) */
extern int D_00150DC0[];   /* .bss  0x00150DC0: 0x40 bytes, lui/%lo */
extern int DeleteSema(int a0);

int sceDbcEnd(void) {
    int v;

    if (D_00133A28[0] == 0)
        return 0;
    D_00133A28[0] = 0;
    v = D_00150DC0[0];
    if (v < 0)
        return 1;
    DeleteSema(v);
    return 1;
}
