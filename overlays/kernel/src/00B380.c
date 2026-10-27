/* KERNEL.XFF @ 0x00B380 (124 B) - InitMath
 * Evidence: iosInitPushPosVuSema(); VIF0 registers 0x10003830/0x10003820 = 0 and 0x10003810 = 1; a volatile asm sets bit 1 of the VU0 FBRST ($vi28) through $t0 + sync.p; two quadwords from .data+0x3A0 to the VIF0 FIFO 0x10004000; InitQuaternionDrive(); sibling InitTableSinCos().
 */
typedef unsigned int u_long128 __attribute__((mode(TI)));
extern u_long128 D_kernel_data_03A0[2];
void iosInitPushPosVuSema(void);
void InitQuaternionDrive(void);
void InitTableSinCos(void);

void InitMath(void) {
    iosInitPushPosVuSema();
    *(volatile int *)0x10003830 = 0;
    *(volatile int *)0x10003820 = 0;
    *(volatile int *)0x10003810 = 1;
    __asm__ __volatile__(
        "cfc2.ni $8, $vi28\n"
        "ori $8, $8, 0x2\n"
        "ctc2.ni $8, $vi28\n"
        "sync.p\n" : : : "$8");
    *(volatile u_long128 *)0x10004000 = D_kernel_data_03A0[0];
    *(volatile u_long128 *)0x10004000 = D_kernel_data_03A0[1];
    InitQuaternionDrive();
    InitTableSinCos();
}
