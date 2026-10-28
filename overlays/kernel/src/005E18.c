/* KERNEL.XFF @ 0x005E18 (240 B) - iosPadRead
 * Evidence: copies the 0x78-byte pad record [port] (8-aligned, .data+0x270) to the caller buffer; the inlined constant-size memcpy tests the destination alignment and uses aligned or ldl/sdl 8-byte moves. UNCONFIRMED: record layout.
 */
struct PadInfo {
    unsigned long data[15];
};
extern struct PadInfo D_kernel_data_0270[];
void *memcpy(void *d, const void *s, unsigned int n);

void iosPadRead(int port, void *info) {
    memcpy(info, &D_kernel_data_0270[port], sizeof(struct PadInfo));
}
