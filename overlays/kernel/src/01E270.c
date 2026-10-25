/* KERNEL.XFF @ 0x01E270 (120 B) - sndSepPlayerSrh2
 * Evidence: as sndSepPlayerSrh without the +0x16 test.
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

struct SepSlot *sndSepPlayerSrh2(int vab, int a) {
    struct SepSlot *ret = 0;
    struct SepSlot *s;
    int i;

    for (i = 0; i < 32; i++) {
        s = &D_kernel_bss_7C3D0[i];
        if (s->used && s->a == a && s->vab && s->vab->id == vab) {
            ret = s;
            break;
        }
    }
    return ret;
}
