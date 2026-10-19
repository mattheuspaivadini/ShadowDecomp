/* STATUS (Session 30, 2026-10-19): NON_MATCHING. best score 2 [cc=29].
 * Residual = 'li v0,1' is the first epilogue insn in the original (at the shared exit label) but lands after 'ld ra' in ours. Levers that got here: buffer pointer local (fixes the s-register set and the 0x800 spill), the n < 16 test as an if/else inside the for, the page number computed before the page count. Tried a ret variable, goto exit, return inside the else, -g0, dtls13010 -g0, -fno-schedule-insns{,2}.
 * The original .s stays in the build (asm/cod/020DA0.s); this C
 * draft (Session 30) is kept for the record. */
struct McSpec {
    unsigned int pagesize;      /* 0x00 */
    int blocksize;              /* 0x04 pages per block */
    int cardsize;               /* 0x08 pages per card */
};

extern unsigned int D_001634C0[];   /* 0x800-byte page buffer */

void _sceMcCoreReadPage2(int port, unsigned int *buf, int page, int count, int ecc);

int _sceMcpMakeSpecoutBlock(int port, struct McSpec *spec, int *out) {
    int n;
    int blk;
    int nblk;
    unsigned int pages;
    unsigned int i;
    int bad;
    int page;
    unsigned int *buf;

    n = 0;
    buf = D_001634C0;
    nblk = spec->cardsize / spec->blocksize;
    for (blk = 1; blk < nblk; blk++) {
        if (n < 16) {
            page = blk * spec->blocksize;
            pages = 0x800 / spec->pagesize;
            bad = 0;
            _sceMcCoreReadPage2(port, buf, page, pages, 0);
            for (i = 0; i < spec->pagesize * pages / 4; i++) {
                if (buf[i] != 0xFFFFFFFF) {
                    bad = 1;
                    break;
                }
            }
            if (bad > 0) {
                *out++ = blk;
                n++;
            }
        } else
            break;
    }
    return 1;
}
