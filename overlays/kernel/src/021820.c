/* KERNEL.XFF @ 0x021820 (136 B) - all_soundpause
 * Evidence: Sg2SlotFindSlotClass(list, mod[id].+4) into a 48-int stack list, then Sg2SlotSetPause(list[i], on) from the last found slot down. UNCONFIRMED: names.
 */
struct Sg2Mod {
    int status;
    int cls;
    char pad[0x9B0 - 8];
};
extern struct Sg2Mod D_kernel_bss_7F6D8[];
int Sg2SlotFindSlotClass(int *out, int cls);
void Sg2SlotSetPause(int slot, int on);

void all_soundpause(int id, int on) {
    int list[48];
    int i;

    for (i = Sg2SlotFindSlotClass(list, D_kernel_bss_7F6D8[id].cls) - 1; i >= 0; i--) {
        Sg2SlotSetPause(list[i], on);
    }
}
