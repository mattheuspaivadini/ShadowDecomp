/* KERNEL.XFF @ 0x003B28 (108 B) - iosInitMallocSystem
 * Evidence: allocator semaphore = iosCreateSema(1, 1, 0) (.bss+0x90B8); .data+0x154 = base; sibling of the static at .text+0x2CC0 with (&.data+0x148, base, size, align). UNCONFIRMED: root partition names.
 */
extern int D_kernel_bss_90B8;
extern void *D_kernel_data_0154;
extern char D_kernel_data_0148[];
int iosCreateSema(int init, int max, int attr);
void func_002CC0(void *root, void *base, int size, int align);

void iosInitMallocSystem(void *base, int size, int align) {
    D_kernel_bss_90B8 = iosCreateSema(1, 1, 0);
    D_kernel_data_0154 = base;
    func_002CC0(D_kernel_data_0148, base, size, align);
}
