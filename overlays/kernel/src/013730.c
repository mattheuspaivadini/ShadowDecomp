/* KERNEL.XFF @ 0x013730 (112 B) - iosDlLockObj
 * Evidence: after isysObjDeleteLock(obj), calls
 * isysAddGroupWithLinkParamNoWait(obj, .bss+0x1EAF8 + workBufId*4, 0, 0) and
 * then pre-increments the parallel counter at .bss+0x1EB00 + workBufId*4,
 * returning the incremented value (the image reloads workBufId twice through
 * `s0 = .bss+0x1EAD8`, shifts by 2 and steps +0x20 / +0x28). DLWork layout is
 * the one already matched in the lane (base[2], buf[2], packet, layerNum,
 * workBufId at +0x18, layer); the two 2-int arrays follow at +0x20 / +0x28.
 * UNCONFIRMED: callee arities, the counter names and the array extent.
 */
struct DLWork {
    char *base[2];
    char *buf[2];
    char *packet;
    int layerNum;
    int workBufId;
    int layer;
    int grpA[2];
    int grpB[2];
};
extern struct DLWork D_kernel_bss_1EAD8;

extern void isysObjDeleteLock(void *obj);
extern void isysAddGroupWithLinkParamNoWait(void *obj, void *p, int a, int b);

int iosDlLockObj(void *obj) {
    isysObjDeleteLock(obj);
    isysAddGroupWithLinkParamNoWait(obj, &D_kernel_bss_1EAD8.grpA[D_kernel_bss_1EAD8.workBufId], 0, 0);
    return ++D_kernel_bss_1EAD8.grpB[D_kernel_bss_1EAD8.workBufId];
}
