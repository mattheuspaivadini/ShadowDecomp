/* KERNEL.XFF @ 0x01E1E8 (132 B) - sndSepPlayerSrh
 * Evidence: first of the 32 0x70-byte SEP slots (.bss+0x7C3D0) that is used, has shorts +0x14 == a and +0x16 == b, and whose VAB reference (+0x10) has id (+4) == vab; NULL otherwise (ret variable + break). UNCONFIRMED: names.
 */
struct SndVabRef {
    int unk0;
    int id;
};
struct SepSlot {
    int used;
    int unk4;
    long flags;
    struct SndVabRef *vab;
    short a;
    short b;
    char pad[0x70 - 0x18];
};
extern struct SepSlot D_kernel_bss_7C3D0[32];

struct SepSlot *sndSepPlayerSrh(int vab, int a, int b) {
    struct SepSlot *ret = 0;
    struct SepSlot *s;
    int i;

    for (i = 0; i < 32; i++) {
        s = &D_kernel_bss_7C3D0[i];
        if (s->used && s->a == a && s->b == b && s->vab && s->vab->id == vab) {
            ret = s;
            break;
        }
    }
    return ret;
}
