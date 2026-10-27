/* KERNEL.XFF @ 0x01F3D8 (68 B) - AddStrHashKey
 * Evidence: chains the key in front of bucket table[key & (size - 1)] (next at +0xC); size and table are reloaded for the second index (no type-based aliasing).
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

void AddStrHashKey(struct StrHash *h, struct StrHashKey *k) {
    k->next = h->table[k->key & (h->size - 1)];
    h->table[k->key & (h->size - 1)] = k;
}
