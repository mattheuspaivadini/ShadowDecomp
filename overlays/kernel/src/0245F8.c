/* KERNEL.XFF @ 0x0245F8 (164 B) - func_0245F8 (static, no symbol in the shipped .symtab)
 * Evidence: same shape as the lane's 024418 (MIDI controller handler): the
 * channel record field +0x54 is set from msg[2], then every slot of the
 * class/channel returned by Sg2SlotFindSlotClassCh is walked (last index down)
 * and Sg2SlotSetLfoVolSpeed is called with msg[2] reloaded from .bss+0x7F6CC per
 * iteration. `addiu a3,m,4` proves the compiler CSEd &m->ch[..].field with
 * &m->cls (field offset 0x54 -> 0x300+4 in the listing).
 * UNCONFIRMED: field/controller names.
 */
struct Sg2ModChan {
    char pad0[0x54];
    int volSpeed;
    char pad[0x70 - 0x58];
};
struct Sg2Mod {
    int vab;
    int cls;
    char pad8[0x2B0 - 8];
    struct Sg2ModChan ch[16];
};
extern unsigned char *D_kernel_bss_7F6CC;
extern struct Sg2Mod *D_kernel_bss_7F6D0;
int Sg2SlotFindSlotClassCh(int *out, int cls, int ch);
void Sg2SlotSetLfoVolSpeed(int slot, int value);

void func_0245F8(void) {
    int list[48];
    struct Sg2Mod *m = D_kernel_bss_7F6D0;
    int ch = D_kernel_bss_7F6CC[0] & 0xF;
    int i;

    m->ch[ch].volSpeed = D_kernel_bss_7F6CC[2];
    for (i = Sg2SlotFindSlotClassCh(list, m->cls, ch) - 1; i >= 0; i--) {
        Sg2SlotSetLfoVolSpeed(list[i], D_kernel_bss_7F6CC[2]);
    }
}
