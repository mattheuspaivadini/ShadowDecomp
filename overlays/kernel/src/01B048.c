/* KERNEL.XFF @ 0x01B048 (56 B) - isysGetGroupSrhNext
 * Evidence: returns &pool[g->next] (index * 24 off .bss+0x27100) or NULL when the index is 0. Group entries are 24-byte records in the .bss+0x27100 pool, linked by the 16-bit index at +0xE (0 = end); see isysGetGroupSrhNext. UNCONFIRMED: layout names.
 */
struct IsysObj {
    char pad[9];
    unsigned char ref;
};
struct GroupEnt {
    struct IsysObj *obj;
    char pad[10];
    unsigned short next;
    char pad2[8];
};
extern struct GroupEnt D_kernel_bss_27100[];

struct GroupEnt *isysGetGroupSrhNext(struct GroupEnt *g) {
    return g->next ? &D_kernel_bss_27100[g->next] : 0;
}
