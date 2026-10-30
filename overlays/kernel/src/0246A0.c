/* KERNEL.XFF @ 0x0246A0 (112 B) - func_0246A0 (static, no symbol in the shipped .symtab)
 * Evidence: MIDI controller handler in the Sg2 static cluster (see 024418/0245F8).
 * .bss+0x7F6CC is the message byte pointer, .bss+0x7F6D0 the module record whose
 * 16 channel records are 0x70 bytes at +0x2B0; the address is materialised as
 * `sll/subu/sll` (*7*16) with ch = msg[0] & 0xF.
 * The stored value is msg[2] through the toolchain's software-double helpers:
 * `(double)v / 12.0` compiles to litodp + dpdiv + dptofp, with the divisor folded
 * to 0x4028000000000000 (IEEE-754 bit pattern of 12.0) and materialised as
 * `ori 0x8050; dsll32 15`; the result is stored with swc1. The byte is read with
 * lbu, which is why the value is copied to an `int` local before the conversion.
 * UNCONFIRMED: field name at +0x3C, controller number.
 */
struct Sg2ModChan {
    char pad0[0x3C];
    float f;
    char pad[0x70 - 0x40];
};
struct Sg2Mod {
    int vab;
    int cls;
    char pad8[0x2B0 - 8];
    struct Sg2ModChan ch[16];
};
extern unsigned char *D_kernel_bss_7F6CC;
extern struct Sg2Mod *D_kernel_bss_7F6D0;

void func_0246A0(void) {
    int ch = D_kernel_bss_7F6CC[0] & 0xF;
    int v = D_kernel_bss_7F6CC[2];
    struct Sg2Mod *m = D_kernel_bss_7F6D0;

    m->ch[ch].f = (float)((double)v / 12.0);
}
