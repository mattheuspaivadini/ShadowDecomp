/* KERNEL.XFF @ 0x024F48 (168 B) - func_024F48 (static, no symbol in the shipped .symtab)
 * Evidence: same Sg2 controller shape as 024418/0245F8. The bend value is the
 * 14-bit pair (msg[2] << 7) + msg[1] shifted down by 7 (`sll a1,7; addu; sra 7`)
 * and written to ch[idx] field +0x34 (0x2E0 from the CSEd m+4 base) before the
 * Sg2SlotFindSlotClassCh/Sg2SlotSetBendValue loop, which passes the same value
 * (`daddu a1,s2,zero`). The value must be built as a plain assignment followed
 * by `>>= 7` (a single expression allocates differently) and with msg[1] as the
 * first addend.
 * UNCONFIRMED: field/param names, the bend encoding.
 */
struct Sg2ModChan {
    char pad0[0x34];
    int bendValue;
    char pad[0x70 - 0x38];
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
void Sg2SlotSetBendValue(int slot, int value);

void func_024F48(void) {
    int list[48];
    struct Sg2Mod *m = D_kernel_bss_7F6D0;
    int ch = D_kernel_bss_7F6CC[0] & 0xF;
    int bend = D_kernel_bss_7F6CC[1] + (D_kernel_bss_7F6CC[2] << 7);
    int i;

    bend >>= 7;
    m->ch[ch].bendValue = bend;
    for (i = Sg2SlotFindSlotClassCh(list, m->cls, ch) - 1; i >= 0; i--) {
        Sg2SlotSetBendValue(list[i], bend);
    }
}
