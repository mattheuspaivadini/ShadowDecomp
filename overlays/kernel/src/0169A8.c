/* KERNEL.XFF @ 0x0169A8 (372 B) - iosSyncGP
 * Evidence: FlushCache(0), iosGsInitDC(), the same two-path branch as
 * iosGPFrameInit (016C90) keyed on .data+0x658, then FlushCache(0) and the
 * common epilogue (hook .data+0x630, iosGsResetCRTC, .data+0x620 = 1,
 * sceGsPutIMR(sceGsGetIMR() & ~0x200), iosDlSwap, iosDlTrans), finally
 * iosSyncPath(0, 0) and a tail call to iosSyncV(1).
 * UNCONFIRMED: names.
 * Build: --flags='-G0' or '-G0 -fno-strict-aliasing' (not -g0).
 */
extern int D_kernel_data_0658;
extern void (*D_kernel_data_0630)(void);
extern volatile int D_kernel_data_0620;
extern int D_kernel_data_0640;
void FlushCache(int mode);
void iosGsInitDC(void);
void iosGsResetCRTC(void);
void iosCopyFrameBuffer(void);
unsigned long sceGsGetIMR(void);
unsigned long sceGsPutIMR(unsigned long imr);
void iosDlSwap(void);
void iosDlTrans(void);
void iosSyncPath(int a, int b);
void iosSyncV(int a);
static void func_016348(void);

void iosSyncGP(void) {
    FlushCache(0);
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
    } else {
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
    FlushCache(0);
    if (D_kernel_data_0630) {
        D_kernel_data_0630();
    }
    iosGsResetCRTC();
    D_kernel_data_0620 = 1;
    sceGsPutIMR(sceGsGetIMR() & ~0x200);
    iosDlSwap();
    iosDlTrans();
    iosSyncPath(0, 0);
    iosSyncV(1);
}
