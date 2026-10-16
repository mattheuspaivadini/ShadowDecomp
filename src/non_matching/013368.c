/* STATUS (Session 4, 2026-10-14): NON_MATCHING. 64-bit split store; register allocation differs.
 * The original .s stays in the build (asm/cod/013368.s); this C
 * attempt is kept for the record. */
/* asm/cod/013368.s -> func_00113368 @ 0x00113368 (0x28 bytes)
 *   lw    $v0, 0x0($a0)          ; p = *pp
 *   dsll32 $v1, $a1, 0
 *   dsra32 $v1, $v1, 0           ; lo = (int)v
 *   dsra32 $a1, $a1, 0           ; hi = (int)(v >> 32)
 *   sw    $v1, 0x0($v0)          ; p[0] = lo
 *   addiu $v0, $v0, 0x4          ; p++
 *   addiu $v1, $v0, 0x4          ; &p[2]
 *   sw    $a1, 0x0($v0)          ; p[1] = hi
 *   jr    $ra
 *    sw   $v1, 0x0($a0)          ; *pp = &p[2]
 *
 * Append a 64-bit value as two 32-bit words; returns &p[1].
 */
int *sceVif1PkAddGsData(int **pp, long long v) {
    int *p = *pp;

    p[0] = (int)v;
    p[1] = (int)(v >> 32);
    *pp = p + 2;
    return p + 1;
}
