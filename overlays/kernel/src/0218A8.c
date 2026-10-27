/* KERNEL.XFF @ 0x0218A8 (136 B) - all_soundmute
 * Evidence: same as all_soundpause with Sg2SlotSetMute.
 */
struct Sg2Mod {
    int status;
    int cls;
    char pad[0x9B0 - 8];
};
extern struct Sg2Mod D_kernel_bss_7F6D8[];
int Sg2SlotFindSlotClass(int *out, int cls);
void Sg2SlotSetMute(int slot, int on);

void all_soundmute(int id, int on) {
    int list[48];
    int i;

    for (i = Sg2SlotFindSlotClass(list, D_kernel_bss_7F6D8[id].cls) - 1; i >= 0; i--) {
        Sg2SlotSetMute(list[i], on);
    }
}
