/* STATUS (Session 9, 2026-10-15): NON_MATCHING. best score 4 [cc=29].
 * session9 R1; residual class not auto-classified
 * The original .s stays in the build (asm/cod/007C70.s); this C
 * draft (Session 9) is kept for the record. */
int func_00107C70(unsigned int value) {
    while (*(volatile unsigned int *)0x1000F130 & 0x8000)
        ;
    *(unsigned char *)0x1000F180 = value;
    return value;
}
