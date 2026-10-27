/* KERNEL.XFF @ 0x0216D0 (156 B) - all_keyoff
 * Evidence: Sg2SlotFindSlotClass(list, mod[id].+4) into a 48-int stack list, then for each found slot from the last down Sg2SlotSetKeyOffBit(core = slot >= 24, 1 << (slot mod 24)) (as all_soundpause). UNCONFIRMED: names.
 */
struct Sg2Mod {
    int status;
    int cls;
    char pad[0x9B0 - 8];
};
extern struct Sg2Mod D_kernel_bss_7F6D8[];
int Sg2SlotFindSlotClass(int *out, int cls);
void Sg2SlotSetKeyOffBit(int core, unsigned int bits);

void all_keyoff(int id) {
    int list[48];
    int i;

    for (i = Sg2SlotFindSlotClass(list, D_kernel_bss_7F6D8[id].cls) - 1; i >= 0; i--) {
        Sg2SlotSetKeyOffBit(list[i] >= 24, list[i] < 24 ? 1 << list[i] : 1 << (list[i] - 24));
    }
}
