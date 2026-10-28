/* KERNEL.XFF @ 0x01F338 (160 B) - InitStrHash
 * Evidence: bits = -2 plus one per halving of n (clamped at 0); size = 1 << bits; table = iosMallocAlign(ptn, size * 4, 0x10); all size buckets cleared (size and table reloaded per iteration). UNCONFIRMED: argument names.
 */
struct StrHashKey;
struct StrHash {
    int size;
    struct StrHashKey **table;
};
void *iosMallocAlign(void *ptn, int size, int align);

void InitStrHash(struct StrHash *h, void *ptn, int n) {
    int bits = -2;
    int i;

    while (n) {
        n >>= 1;
        bits++;
    }
    if (bits < 0) {
        bits = 0;
    }
    h->size = 1 << bits;
    h->table = iosMallocAlign(ptn, h->size * 4, 0x10);
    for (i = 0; i < h->size; i++) {
        h->table[i] = 0;
    }
}
