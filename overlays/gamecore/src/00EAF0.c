/* GAMECORE.XFF @ 0x00EAF0 (52 B) - activeDemoCancel
 * Evidence: `.data+0x6D0` word at +0xC is tested (skip when zero), the +0x8
 * word is compared with `$a0` (skip when different) and then +0x0 is OR-ed
 * with 4.
 * UNCONFIRMED: the struct field meanings.
 
 */
struct ActiveDemoState {
    int flags;
    char pad[4];
    int handle;
    int active;
};
extern struct ActiveDemoState D_kernel_data_06D0;

void activeDemoCancel(int handle) {
    if (D_kernel_data_06D0.active != 0) {
        if (D_kernel_data_06D0.handle == handle)
            D_kernel_data_06D0.flags |= 4;
    }
}
