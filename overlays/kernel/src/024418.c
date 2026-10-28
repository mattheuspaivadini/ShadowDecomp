/* KERNEL.XFF @ 0x024418 (156 B) - func_024418 (static, no symbol in the shipped .symtab)
 * Evidence: MIDI controller handler: the channel record (module + 0x2B0, 0x70 bytes) field +0x50 = msg[2]; Sg2SlotSetLfoPitchDepth(slot, msg[2]) for every slot of the class/channel (Sg2SlotFindSlotClassCh, last down; message pointer reloaded per call). UNCONFIRMED: controller number; Ghidra FUN_00224418.
 */
struct Sg2ModChan {
    char pad0[0x50];
    int mod;
    char pad54[0x70 - 0x54];
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
void Sg2SlotSetLfoPitchDepth(int slot, int depth);

void func_024418(void) {
    int list[48];
    struct Sg2Mod *m = D_kernel_bss_7F6D0;
    int ch = D_kernel_bss_7F6CC[0] & 0xF;
    int i;

    m->ch[ch].mod = D_kernel_bss_7F6CC[2];
    for (i = Sg2SlotFindSlotClassCh(list, m->cls, ch) - 1; i >= 0; i--) {
        Sg2SlotSetLfoPitchDepth(list[i], D_kernel_bss_7F6CC[2]);
    }
}
