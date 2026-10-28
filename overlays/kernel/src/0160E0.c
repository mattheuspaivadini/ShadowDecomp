/* KERNEL.XFF @ 0x0160E0 (152 B) - iosCheckDrawFinish
 * Evidence: ++counter (.data+0x5AC); reads VU status $vi29; returns 0 while D1_CHCR or D2_CHCR STR (0x100), VIF1_STAT & 0x1F000003, VU1 running (vi29 & 0x100) or GIF_STAT & 0xC00 is set, else 1 (one || condition). UNCONFIRMED: counter name.
 */
extern int D_kernel_data_05AC;
int iosCheckDrawFinish(void) {
    int stat;
    D_kernel_data_05AC++;
    asm volatile("cfc2.ni %0, $vi29" : "=r"(stat));
 if ((*(volatile int *)0x10009000 & 0x100) || (*(volatile int *)0x1000A000 & 0x100) || (*(volatile int *)0x10003C00 & 0x1F000003) || (stat & 0x100) || (*(volatile int *)0x10003020 & 0xC00)) return 0;
 return 1;
}
