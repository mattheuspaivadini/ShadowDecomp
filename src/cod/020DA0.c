/* asm/cod/020DA0.s -> _sceMcpMakeSpecoutBlock.
 * libmc2 bad-block scan: read each block's first 0x800 bytes and list (up to 16) blocks that are not all 0xFFFFFFFF. Buffer pointer local fixes the register set; the early return 1 at the loop top gives the separate return block (li v0,1 before ld ra).
 * MATCHED. */
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
        if (n >= 16)
            return 1;
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
    }
    return 1;
}
