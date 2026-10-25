/* KERNEL.XFF @ 0x015EC0 (84 B) - iosSyncV
 * Evidence: waitVscheduler() n + 1 times (the counted up-loop reversed by loop.c: count n + 1 tested with blez, copied to $s0, bnez), then returns bit 13 of the GS CSR (FIELD) as in iosGetField.
 */
void waitVscheduler(void);

int iosSyncV(int n) {
    int i;

    for (i = 0; i < n + 1; i++) {
        waitVscheduler();
    }
    return (*(volatile unsigned long *)0x12001000 >> 13) & 1;
}
