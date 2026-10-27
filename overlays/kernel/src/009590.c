/* KERNEL.XFF @ 0x009590 (88 B) - isysSearchSymbol
 * Evidence: NULL name -> *out = 0, return 1; else SearchStrHashKey(&.bss+0xDE58, name) and, when found, *out = entry->+8->+4; returns found != 0. UNCONFIRMED: table/entry layout.
 */
struct HashEnt {
    int unk0;
    int unk4;
    int *value;
};
extern char D_kernel_bss_DE58[];
struct HashEnt *SearchStrHashKey(void *table, const char *key);

int isysSearchSymbol(int *out, const char *name) {
    struct HashEnt *e;

    if (name == 0) {
        *out = 0;
        return 1;
    }
    e = SearchStrHashKey(D_kernel_bss_DE58, name);
    if (e != 0) {
        *out = e->value[1];
    }
    return e != 0;
}
