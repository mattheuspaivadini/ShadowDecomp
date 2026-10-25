/* KERNEL.XFF @ 0x016BF0 (92 B) - iosTransGP
 * Evidence: optional hook at .data+0x630; iosGsResetCRTC(); volatile .data+0x620 = 1 (addressed through lui/addiu + 0); sceGsPutIMR(sceGsGetIMR() & ~0x200); iosDlSwap(); sibling iosDlTrans(). UNCONFIRMED: object names.
 */
extern void (*D_kernel_data_0630)(void);
extern volatile int D_kernel_data_0620;
void iosGsResetCRTC(void);
int sceGsGetIMR(void);
int sceGsPutIMR(int imr);
void iosDlSwap(void);
void iosDlTrans(void);

void iosTransGP(void) {
    if (D_kernel_data_0630 != 0) {
        D_kernel_data_0630();
    }
    iosGsResetCRTC();
    D_kernel_data_0620 = 1;
    sceGsPutIMR(sceGsGetIMR() & ~0x200);
    iosDlSwap();
    iosDlTrans();
}
