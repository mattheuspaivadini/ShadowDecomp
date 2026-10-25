/* KERNEL.XFF @ 0x009E90 (84 B) - isysGetXffWorkSize
 * Evidence: k = byte +0xC ? byte + 1 : 2; n = word +0x24 - word +0x1C - k; size = n ? n*16 + 0x33 : 0, plus word +0x1C * 16 + 0x33 when that word is non-zero. UNCONFIRMED: field meanings (symbol counts of the .xff header).
 */
struct XffInfo {
    char pad[0xC];
    unsigned char nsec;
    char pad2[0xF];
    int nlocal;
    int unk20;
    int nsym;
};

int isysGetXffWorkSize(struct XffInfo *x) {
    int k;
    int n;
    int size;

    k = x->nsec ? x->nsec + 1 : 2;
    n = x->nsym - x->nlocal - k;
    size = n ? n * 16 + 0x33 : 0;
    if (x->nlocal) {
        size += x->nlocal * 16 + 0x33;
    }
    return size;
}
