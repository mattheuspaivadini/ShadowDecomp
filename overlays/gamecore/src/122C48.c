/* GAMECORE.XFF @ 0x122C48 (32 B) - forceRenewLastPosPerceptionWork
 * Evidence: two lq/sq pairs through pointer at (*(a1+0x4C))+0x134, reloaded each time (needs -fno-strict-aliasing)
 * UNCONFIRMED: field names/types guessed from offsets
 */
typedef unsigned int u_long128 __attribute__((mode(TI)));
void forceRenewLastPosPerceptionWork(int a, char *w) {
    char *o = *(char **)(w + 0x4C);
    *(u_long128 *)w = **(u_long128 **)(o + 0x134);
    *(u_long128 *)(w + 0x10) = **(u_long128 **)(o + 0x134);
}
