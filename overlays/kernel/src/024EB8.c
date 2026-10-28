/* KERNEL.XFF @ 0x024EB8 (136 B) - func_024EB8 (static, no symbol in the shipped .symtab)
 * Evidence: MIDI program change: channel = msg[0] & 0xF; the channel record (0x70 bytes at module + 0x2B0) gets program msg[1] (+8), vab_get_progchunk(module vab, msg[1]) (+0x68) and vab_get_splitchunk of it (+0x6C); module pointer .bss+0x7F6D0 reloaded after each call, message .bss+0x7F6CC. UNCONFIRMED: names; Ghidra FUN_00224eb8.
 */
struct Sg2ModProg {
    int unk0;
    int unk4;
    void *prog;
    void *split;
};
struct Sg2ModChan {
    char pad0[8];
    int prog;
    char padC[0x60 - 0xC];
    struct Sg2ModProg pc;
};
struct Sg2Mod {
    int vab;
    int cls;
    char pad8[0x2B0 - 8];
    struct Sg2ModChan ch[16];
};
extern unsigned char *D_kernel_bss_7F6CC;
extern struct Sg2Mod *D_kernel_bss_7F6D0;
void *vab_get_progchunk(int vab, unsigned int prog);
void *vab_get_splitchunk(void *prog);

void func_024EB8(void) {
    unsigned char *msg = D_kernel_bss_7F6CC;
    struct Sg2Mod *m = D_kernel_bss_7F6D0;
    int ch = msg[0] & 0xF;
    void *p;

    m->ch[ch].prog = msg[1];
    p = vab_get_progchunk(m->vab, msg[1]);
    D_kernel_bss_7F6D0->ch[ch].pc.prog = p;
    D_kernel_bss_7F6D0->ch[ch].pc.split = vab_get_splitchunk(p);
}
