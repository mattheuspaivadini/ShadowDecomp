/* KERNEL.XFF @ 0x01F560 (152 B) - DeleteStrHashKey
 * Evidence: unlinks key from its bucket table[key & (size - 1)] (next at +0xC, next read before the compare, bucket index recomputed from the found key); a key that is not chained reaches iosJumpRecoverPoint(.rodata+0x2AF8 message).
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
extern char D_kernel_rodata_2AF8[];
void iosJumpRecoverPoint(const char *msg);
void DeleteStrHashKey(struct StrHash *h, struct StrHashKey *k) {
 struct StrHashKey *p;
 struct StrHashKey *next;
 struct StrHashKey *prev = 0;
 for (p = h->table[k->key & (h->size - 1)]; p; p = next) {
 next = p->next;
 if (k == p) {
 if (prev == 0) h->table[p->key & (h->size - 1)] = next;
 else prev->next = next;
 return;
 }
 prev = p;
 }
 iosJumpRecoverPoint(D_kernel_rodata_2AF8);
}
