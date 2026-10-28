/* KERNEL.XFF @ 0x01EF50 (52 B) - iosKeybdInit
 * Evidence: `lui/addiu s0,.data+0xA2C`, `sw $0,0(s0)` in the jal delay slot
 * (zero the keyboard flag), sceSifInitRpc(0), then the flag is *reloaded*
 * (`lw v0,0(s0)`) and returned, which is why the value is read back through
 * the pointer instead of reusing the constant.
 * The `do { } while (0)` wrapper keeps sched2 from moving the reload behind
 * the epilogue restores ($s0 is restored after it in the image).
 * UNCONFIRMED: flag name.
 */
extern int D_kernel_data_0A2C;
int sceSifInitRpc(int mode);

int iosKeybdInit(void) {
    do {
        D_kernel_data_0A2C = 0;
        sceSifInitRpc(0);
    } while (0);
    return D_kernel_data_0A2C;
}
