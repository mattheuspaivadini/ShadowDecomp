/* KERNEL.XFF @ 0x017050 (232 B) - gsRegBegin
 * Evidence: opens a GS register packet on the path-1 packet context (.data+0x664, reloaded at every access): error = 0; cur = iosGetPacketPtrPath1() (error = 1 when NULL, else top = cur and cur skips the DMA tag); then tag = cur, a zero GIF tag qword (a second one when cur is not aligned), reg = cur, cur += 2 qwords; returns cur. UNCONFIRMED: field names.
 */
struct GsPacketCtx {
    unsigned long *top;
    unsigned long *tag;
    unsigned long *reg;
    unsigned long *cur;
    char pad10[0xC];
    int error;
};
extern struct GsPacketCtx *D_kernel_data_0664;
unsigned long *iosGetPacketPtrPath1(void);

unsigned long *gsRegBegin(void) {
    D_kernel_data_0664->error = 0;
    D_kernel_data_0664->cur = iosGetPacketPtrPath1();
    if (D_kernel_data_0664->cur == 0) {
        D_kernel_data_0664->error = 1;
    } else {
        D_kernel_data_0664->top = D_kernel_data_0664->cur;
        D_kernel_data_0664->cur++;
    }
    if (D_kernel_data_0664->error == 0) {
        D_kernel_data_0664->tag = D_kernel_data_0664->cur;
        *D_kernel_data_0664->cur++ = 0;
        if ((unsigned int)D_kernel_data_0664->cur & 3) {
            *D_kernel_data_0664->cur++ = 0;
        }
        D_kernel_data_0664->reg = D_kernel_data_0664->cur;
        D_kernel_data_0664->cur += 2;
    }
    return D_kernel_data_0664->cur;
}
