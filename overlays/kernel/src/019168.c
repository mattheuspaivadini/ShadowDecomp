/* KERNEL.XFF @ 0x019168 (72 B) - gsReg
 * Evidence: unless word +0x1C of the packet object at .data+0x664 is set, appends two u64 (data, then the register address) through its write pointer at +0xC; the object pointer is reloaded after the first 64-bit store (no type-based aliasing). UNCONFIRMED: layout names.
 */
struct GsPacket {
    char pad[0xC];
    unsigned long *ptr;
    char pad2[0xC];
    int busy;
};
extern struct GsPacket *D_kernel_data_0664;

void gsReg(unsigned long addr, unsigned long data) {
    if (D_kernel_data_0664->busy == 0) {
        *D_kernel_data_0664->ptr++ = data;
        *D_kernel_data_0664->ptr++ = addr;
    }
}
