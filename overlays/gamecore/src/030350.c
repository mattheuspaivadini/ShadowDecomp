/* GAMECORE.XFF @ 0x030350 (52 B) - bgmScriptRecvSoundSignal
 * Evidence: `lw` of `.bss+0x4DC0`, `srav`+`andi 1` for the old bit, a `beqz`
 * that returns the old value, and on the set path `1 << bit` XOR-ed back into
 * the same word.
 * UNCONFIRMED: the flag word meaning.
 
 */
extern int D_kernel_bss_4DC0;

int bgmScriptRecvSoundSignal(int bit) {
    int old = (D_kernel_bss_4DC0 >> bit) & 1;

    if (old)
        D_kernel_bss_4DC0 ^= 1 << bit;
    return old;
}
