/* KERNEL.XFF @ 0x0203D8 (348 B) - Sg2ExStAdpcmOpen
 * Evidence: `(src | &st->0x28) & 7` selects between the ldl/ldr and the ld/sd
 * copy loops: a 0x78-byte descriptor is copied to st+0x28 in three 0x20-byte
 * chunks plus a 0x18-byte tail (GCC's inline block move for a 0x78-byte struct
 * assignment). Arguments 3..6 arrive in $a2,$a3,$t0,$t1 (arguments 5/6 live in
 * the $t registers of this ABI) and are stored at +0x230/+0x234/+0x238/+0x23C;
 * +0x2D8/+0x2DC are zeroed; +0x240/+0x244 are the descriptor's +0x10/+0x14
 * shifted left by 11. The 16 words at +0x24C..+0x28B are then filled with 100
 * eight at a time (two words per iteration, `addiu $a0,$t2,0x250` with -4/0
 * offsets), +0x2CC = 100 and the body tail-calls func_020350(st).
 * UNCONFIRMED: struct/field names, func_020350's real name.
 */
struct Sg2AdpcmHdr {
    char pad00[0x10];
    int unk10;
    int unk14;
    char pad18[0x60];
};

struct Sg2ExStAdpcm {
    char pad00[0x28];
    struct Sg2AdpcmHdr hdr;
    char padA0[0x190];
    int unk230;
    int unk234;
    int unk238;
    int unk23C;
    int unk240;
    int unk244;
    char pad248[4];
    int env[16];
    char pad28C[0x40];
    int unk2CC;
    char pad2D0[8];
    int unk2D8;
    int unk2DC;
};
void func_020350(struct Sg2ExStAdpcm *st);

void Sg2ExStAdpcmOpen(struct Sg2ExStAdpcm *st, struct Sg2AdpcmHdr *src,
                      int a2, int a3, int a4, int a5) {
    int i;

    st->hdr = *src;
    st->unk230 = a2;
    st->unk234 = a3;
    st->unk238 = a4;
    st->unk23C = a5;
    st->unk2D8 = 0;
    st->unk2DC = 0;
    st->unk240 = src->unk10 << 11;
    st->unk244 = src->unk14 << 11;
    for (i = 0; i < 8; i++) {
        st->env[i * 2] = 100;
        st->env[i * 2 + 1] = 100;
    }
    st->unk2CC = 100;
    func_020350(st);
}
