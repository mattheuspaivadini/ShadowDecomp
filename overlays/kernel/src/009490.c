/* KERNEL.XFF @ 0x009490 (136 B) - InitDld
 * Evidence: iosCdInit(); InitStrHash(&.bss+0xDE58, rootPtn, 0x10000); isysInitGroup on .data+0x380/+0x388/+0x390; LoaderSysGetMemoryInfo(&.bss+0xDDF0); the static at .text+0x8CA8 with (&info+0x20, info.+0x64, rootPtn); sibling isysCreateExceptionThread(). UNCONFIRMED: info layout.
 */
struct MemInfo {
    char pad[0x20];
    char region[0x44];
    int size;
};
extern char rootPtn[];
extern char D_kernel_bss_DE58[];
extern struct MemInfo D_kernel_bss_DDF0;
extern char D_kernel_data_0380[];
extern char D_kernel_data_0388[];
extern char D_kernel_data_0390[];
void iosCdInit(void);
void InitStrHash(void *hash, void *ptn, int size);
void isysInitGroup(void *group);
void LoaderSysGetMemoryInfo(void *info);
void func_008CA8(void *region, int size, void *ptn);
void isysCreateExceptionThread(void);

void InitDld(void) {
    iosCdInit();
    InitStrHash(D_kernel_bss_DE58, rootPtn, 0x10000);
    isysInitGroup(D_kernel_data_0380);
    isysInitGroup(D_kernel_data_0388);
    isysInitGroup(D_kernel_data_0390);
    LoaderSysGetMemoryInfo(&D_kernel_bss_DDF0);
    func_008CA8(D_kernel_bss_DDF0.region, D_kernel_bss_DDF0.size, rootPtn);
    isysCreateExceptionThread();
}
