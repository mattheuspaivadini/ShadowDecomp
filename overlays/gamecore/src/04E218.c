/* GAMECORE.XFF @ 0x04E218 (36 B) - getTriggerPointEffectIntensity
 * Evidence: `$a0 += 3` (materialised in its own register, NOT folded into the
 * displacement), then the strength-reduced index multiply
 * `((x << 4) - x) << 3` = x * 120, added to .bss and read as `lwc1` at +0x6EA4:
 * a float array of 120-byte elements indexed from (arg + 3).
 * UNCONFIRMED: the element layout and the +3 bias meaning.
 
 */
extern char D_kernel_bss_6EA4[];

float getTriggerPointEffectIntensity(int index) {
    int i = index + 3;

    return *(float *)(D_kernel_bss_6EA4 + i * 120);
}
