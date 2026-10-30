/* GAMECORE.XFF @ 0x0F7E78 (56 B) - getPassageWork
 * Evidence: loads $v0, 0x380($a0)
 
 */
/* UNCONFIRMED: +0x380 is the passage count, passages start at +0x100 with a
 * 0x20 stride and the count is capped at 0x14.
 */
char *getPassageWork(char *p, int idx) {
    if (idx < 0x14 && idx < *(unsigned int *)(p + 0x380))
        return p + 0x100 + idx * 0x20;
    return 0;
}
