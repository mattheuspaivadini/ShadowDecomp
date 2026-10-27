/* KERNEL.XFF @ 0x009518 (100 B) - IosLoadIrxSimulation
 * Evidence: three iosLoadIopModule(path, name, 0, 0) calls with the .rodata string pairs at +0xBD0/+0xBF0, +0xBF8/+0xC10, +0xC20/+0xC40.
 */
extern char D_kernel_rodata_0BD0[];
extern char D_kernel_rodata_0BF0[];
extern char D_kernel_rodata_0BF8[];
extern char D_kernel_rodata_0C10[];
extern char D_kernel_rodata_0C20[];
extern char D_kernel_rodata_0C40[];
int iosLoadIopModule(const char *path, const char *name, int argc, const char *args);

void IosLoadIrxSimulation(void) {
    iosLoadIopModule(D_kernel_rodata_0BD0, D_kernel_rodata_0BF0, 0, 0);
    iosLoadIopModule(D_kernel_rodata_0BF8, D_kernel_rodata_0C10, 0, 0);
    iosLoadIopModule(D_kernel_rodata_0C20, D_kernel_rodata_0C40, 0, 0);
}
