/* KERNEL.XFF @ 0x01F530 (48 B) - ReleaseStrHashKeyAll
 * Evidence: iosFree(table) then table = 0 and size = 0.
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
void iosFree(void *p);

void ReleaseStrHashKeyAll(struct StrHash *h) {
    iosFree(h->table);
    h->table = 0;
    h->size = 0;
}
