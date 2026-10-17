/* asm/cod/01CAC0.s -> func_0011CAC0.
 * SCE libmc card spec from the FAT header (Session 19)
 * MATCHED. */
struct mc_spec_src {
    char           pad00[0x28];
    unsigned short page;    /* 0x28 */
    unsigned short pad2A;
    unsigned short blk;     /* 0x2C */
    unsigned short pad2E;
    int            size;    /* 0x30 */
};

int _sceMcCoreSetCardSpec(int index, int *spec);

int func_0011CAC0(int index, struct mc_spec_src *rec) {
    int buf[4];

    buf[0] = rec->page;
    buf[1] = rec->blk;
    buf[2] = (rec->size << 10) / rec->page;
    buf[3] = 1;
    return _sceMcCoreSetCardSpec(index, buf);
}
