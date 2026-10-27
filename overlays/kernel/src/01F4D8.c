/* KERNEL.XFF @ 0x01F4D8 (88 B) - SearchStrHashKey
 * Evidence: walks bucket table[key & (size - 1)] through +0xC links until k->key == key; NULL when absent (the nops are R5900 loop padding).
 */
struct StrHashKey {
    unsigned int key;
    int unk4;
    int unk8;
    struct StrHashKey *next;
};
struct StrHash {
    int size;
    struct StrHashKey **table;
};

struct StrHashKey *SearchStrHashKey(struct StrHash *h, unsigned int key) {
    struct StrHashKey *k;

    for (k = h->table[key & (h->size - 1)]; k != 0; k = k->next) {
        if (key == k->key) {
            return k;
        }
    }
    return 0;
}
