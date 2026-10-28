/* KERNEL.XFF @ 0x01F2B0 (40 B) - iosMouseInit
 * Evidence: `lui/addiu .data+0xA34` + `sw $0` in the jal delay slot is a
 * zero store to the module's mouse-init flag; sceSifInitRpc takes 0; the
 * function returns the same 0 (`daddu v0,zero,zero` before the `ld ra`).
 * The `do { } while (0)` wrapper is what keeps 2.96's sched2 from sinking the
 * `daddu v0,zero,zero` behind the epilogue restore (block boundary at the
 * do-while exit); it does not change behaviour.
 * UNCONFIRMED: flag name/width, parameter name of sceSifInitRpc.
 */
extern int D_kernel_data_0A34;
int sceSifInitRpc(int mode);

int iosMouseInit(void) {
    int r = 0;

    do {
        D_kernel_data_0A34 = r;
        sceSifInitRpc(r);
    } while (0);
    return r;
}
