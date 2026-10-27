/* KERNEL.XFF @ 0x016C90 (248 B) - iosGPFrameInit
 * Evidence: iosGsInitDC(); when .data+0x658 is set it is cleared and the frame skips iosCopyFrameBuffer and the trailing hook; otherwise iosCopyFrameBuffer() first. Both paths: optional hook .data+0x630, iosGsResetCRTC(), .data+0x620 = 1 (volatile: lui/addiu+0 store), sceGsPutIMR(sceGsGetIMR() & ~0x200), iosDlSwap(), iosDlTrans(); the second path then calls static .text+0x16348 when .data+0x640 is set. UNCONFIRMED: names.
 */
extern int D_kernel_data_0658;
extern void (*D_kernel_data_0630)(void);
extern volatile int D_kernel_data_0620;
extern int D_kernel_data_0640;
void iosGsInitDC(void);
void iosGsResetCRTC(void);
void iosCopyFrameBuffer(void);
unsigned long sceGsGetIMR(void);
unsigned long sceGsPutIMR(unsigned long imr);
void iosDlSwap(void);
void iosDlTrans(void);
static void func_016348(void);

void iosGPFrameInit(void) {
    iosGsInitDC();
    if (D_kernel_data_0658) {
        D_kernel_data_0658 = 0;
        if (D_kernel_data_0630) {
            D_kernel_data_0630();
        }
        iosGsResetCRTC();
        D_kernel_data_0620 = 1;
        sceGsPutIMR(sceGsGetIMR() & ~0x200);
        iosDlSwap();
        iosDlTrans();
        return;
    }
    iosCopyFrameBuffer();
    if (D_kernel_data_0630) {
        D_kernel_data_0630();
    }
    iosGsResetCRTC();
    D_kernel_data_0620 = 1;
    sceGsPutIMR(sceGsGetIMR() & ~0x200);
    iosDlSwap();
    iosDlTrans();
    if (D_kernel_data_0640) {
        func_016348();
    }
}
