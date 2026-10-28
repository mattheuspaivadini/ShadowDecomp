/* KERNEL.XFF @ 0x020350 (132 B) - Sg2ExStAdpcmOpenFake
 * Evidence: -3 when the stream's status (+0) is non-zero; -1 unless the header word at +0x28 (read through a pointer) is 'EXST' (0x54535845); clears +0x2D4, +0x248, the 64-bit +0xA0, +0x228, +0x22C and memset(+0xA8, 0, 0x180); +8 = +0xC; returns the static at .text+0x200B8 ? -2 : 0. UNCONFIRMED: field names.
 */
struct ExStAdpcm {
    int status;
    char pad4[4];
    int unk8;
    int unkC;
    char pad10[0x28 - 0x10];
    int magic;
    char pad2C[0xA0 - 0x2C];
    long unkA0;
    char work[0x180];
    char pad228[0];
    int unk228;
    int unk22C;
    char pad230[0x248 - 0x230];
    int unk248;
    char pad24C[0x2D4 - 0x24C];
    int unk2D4;
};
void *memset(void *p, int c, unsigned int n);
int func_0200B8(struct ExStAdpcm *w);

int Sg2ExStAdpcmOpenFake(struct ExStAdpcm *w) {
    int *hdr = &w->magic;

    if (w->status != 0) {
        return -3;
    }
    if (*hdr != 0x54535845) {
        return -1;
    }
    w->unk2D4 = 0;
    w->unk248 = 0;
    w->unkA0 = 0;
    w->unk228 = 0;
    w->unk22C = 0;
    memset(w->work, 0, 0x180);
    w->unk8 = w->unkC;
    if (func_0200B8(w)) {
        return -2;
    }
    return 0;
}
