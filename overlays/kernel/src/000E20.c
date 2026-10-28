/* KERNEL.XFF @ 0x000E20 (152 B) - iosLoaderResetEntry
 * Evidence: s0 = &.bss+0x90B0 (two-word table) tested at +0; while that word is
 * zero the prologue calls loaderSetResetCallback(text+0xEF0).  The scan keeps
 * the index in $s0, pre-increments it and compares table[i-1] with 0 (`slti
 * $a0,$s0,2` feeding the `bnel` back edge, with the two R5900 short-loop nops);
 * taking the `beqz` jumps straight to the store and skips the recovery report.
 * Exhausting the table calls iosJumpRecoverPoint(.rodata+0x160) and then stores
 * the argument at table[i] (i == 2 on that path).
 * UNCONFIRMED: parameter type, loaderSetResetCallback prototype, the recovery
 * message text, and the table name beyond its .bss offset.
 * Byte-exact with `-G0` and `-G0 -fno-strict-aliasing`.
 */
extern int D_kernel_bss_90B0[2];
extern char D_kernel_rodata_160[];

extern void loaderSetResetCallback(void *func);
extern void iosJumpRecoverPoint(char *msg);
extern void func_000EF0(void);

void iosLoaderResetEntry(int entry)
{
    int i;

    if (D_kernel_bss_90B0[0] == 0)
        loaderSetResetCallback(func_000EF0);
    for (i = 0; i < 2; i++) {
        if (D_kernel_bss_90B0[i] == 0)
            goto found;
    }
    iosJumpRecoverPoint(D_kernel_rodata_160);
found:
    D_kernel_bss_90B0[i] = entry;
}
