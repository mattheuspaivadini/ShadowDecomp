/* STATUS (Session 19, 2026-10-17): NON_MATCHING. best score 2 [cc=29].
 * full 0x184-byte record; residual = mflo placed before the jal instead of in its delay slot
 * The original .s stays in the build (asm/cod/020D58.s); this C
 * draft (Session 19) is kept for the record. */
struct R020D58 {
    char pad00[0x2A];
    unsigned short w;   /* 0x2A */
    unsigned short d;   /* 0x2C */
    char pad2E[0x184 - 0x2E];
};

extern struct R020D58 gSceMc2SysInfo[];

int _sceMcpIsSpeckOutBlock(int index, int key);

int _sceMcpIsSpeckOutClust(int index, int a1) {
    struct R020D58 *r = &gSceMc2SysInfo[index];

    return _sceMcpIsSpeckOutBlock(index, a1 * r->w / r->d);
}
