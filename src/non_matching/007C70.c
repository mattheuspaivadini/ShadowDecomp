/* STATUS (10, 2026-10-16): NON_MATCHING. best score 4 [cc=29].
 * 
 * The original .s stays in the build (asm/cod/007C70.s); this C
 * draft (10) is kept for the record. */
int func_00107C70(unsigned int value) {
    while (*(volatile unsigned int *)0x1000F130 & 0x8000)
        ;
    *(unsigned char *)0x1000F180 = value;
    return value;
}
