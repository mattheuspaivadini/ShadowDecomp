/* KERNEL.XFF @ 0x0249C8 (132 B) - func_0249C8 (static, no symbol in the shipped .symtab)
 * Evidence: msg[2] < 0x7E (`sltiu`/`beqz` on the lbu) selects the dumper-off
 * path: ch[idx] field +0x30 (0x2E0 from the m base) is cleared and
 * Sg2SlotSetDumperOff(m->cls, ch) is tail-called (`j`, sp popped in the delay
 * slot); otherwise the same field is set to 1 and the function just returns.
 * The record pointer is reloaded from .bss+0x7F6D0 inside each branch, so the
 * global is used directly there instead of through a local.
 * Size note: 132 B (the inventory's 128 B stops before the `jr` delay slot).
 * UNCONFIRMED: dumper semantics, whether 0x7E is 126 or a threshold constant.
 */
struct Sg2ModChan {
    char pad0[0x30];
    int dumper;
    char pad[0x70 - 0x34];
};
struct Sg2Mod {
    int vab;
    int cls;
    char pad8[0x2B0 - 8];
    struct Sg2ModChan ch[16];
};
extern unsigned char *D_kernel_bss_7F6CC;
extern struct Sg2Mod *D_kernel_bss_7F6D0;
void Sg2SlotSetDumperOff(int cls, int ch);

void func_0249C8(void) {
    int ch = D_kernel_bss_7F6CC[0] & 0xF;

    if (D_kernel_bss_7F6CC[2] < 0x7E) {
        D_kernel_bss_7F6D0->ch[ch].dumper = 0;
        Sg2SlotSetDumperOff(D_kernel_bss_7F6D0->cls, ch);
    } else {
        D_kernel_bss_7F6D0->ch[ch].dumper = 1;
    }
}
