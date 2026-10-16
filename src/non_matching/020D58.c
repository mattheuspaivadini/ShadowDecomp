/* STATUS (Session 6, step 3): NON_MATCHING. Correct instruction sequence at cc=29 (mult stride + div), register roles and scheduling differ (15 edits).
 * See docs/non-matching-backlog.md. */
/* asm/cod/020D58.s -> func_00120D58 @ 0x00120D58
 * Record lookup (stride 0x184, the 2.9 `mult $v1,$a0,$v1` shape): scale `a1`
 * by the unsigned short at +0x2A, divide by the unsigned short at +0x2C
 * (`div` + the divide-by-zero `break` guard) and forward to func_00120D10. */
struct R020D58 {
    char pad00[0x2A];
    unsigned short w;   /* 0x2A */
    unsigned short d;   /* 0x2C */
};

extern struct R020D58 gSceMc2SysInfo[];

int _sceMcpIsSpeckOutBlock(int index, int key);

int _sceMcpIsSpeckOutClust(int index, int a1) {
    unsigned short w = gSceMc2SysInfo[index].w;
    unsigned short d = gSceMc2SysInfo[index].d;

    return _sceMcpIsSpeckOutBlock(index, a1 * w / d);
}
