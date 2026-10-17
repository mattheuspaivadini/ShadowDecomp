/* asm/cod/007C70.s -> SIO_ISR.
 * SIO TX putc; TU built without gcc dbr (-fno-delayed-branch), GAS reorder fills jr (Session 19)
 * MATCHED. */
#define SIO_ISR  ((volatile unsigned int *)0x1000F130)
#define SIO_TXFIFO ((volatile unsigned char *)0x1000F180)
int func_00107C70(int value) {
    while (*SIO_ISR & 0x8000)
        ;
    *SIO_TXFIFO = (unsigned char)value;
    return value;
}
