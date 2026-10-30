/* KERNEL.XFF @ 0x021770 (172 B) - all_soundoff
 * Evidence: module record stride 0x9B0 (i*5 << 5 - i*5 << 4) off .bss+0x7F6D8,
 * field +4 (cls) passed to Sg2SlotFindSlotClass together with a 48-int stack
 * list; the loop runs from the returned count-1 down, calling
 * Sg2SlotSetAdsr(list[i], 0, 8) and then Sg2SlotSetKeyOffBit(core, bit) where
 * core = list[i] >= 24 and bit = 1 << (list[i] mod 24) (slti 0x18, sllv twice).
 * Same body as all_keyoff (0216D0) plus the ADSR call. UNCONFIRMED: names.
 */
struct Sg2Mod {
    int vab;
    int cls;
    char pad[0x9B0 - 8];
};
extern struct Sg2Mod D_kernel_bss_7F6D8[];
int Sg2SlotFindSlotClass(int *out, int cls);
void Sg2SlotSetAdsr(int slot, int a, int b);
void Sg2SlotSetKeyOffBit(int core, unsigned int bits);

void all_soundoff(int id) {
    int list[48];
    int i;

    for (i = Sg2SlotFindSlotClass(list, D_kernel_bss_7F6D8[id].cls) - 1; i >= 0; i--) {
        Sg2SlotSetAdsr(list[i], 0, 8);
        Sg2SlotSetKeyOffBit(list[i] >= 24, list[i] < 24 ? 1 << list[i] : 1 << (list[i] - 24));
    }
}
