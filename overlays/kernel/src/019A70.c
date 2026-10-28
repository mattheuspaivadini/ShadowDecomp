/* KERNEL.XFF @ 0x019A70 (328 B) - func_019A70 (static, no symbol in the shipped .symtab)
 * Evidence: unlinks a 0x18-byte group entry (.bss+0x27100) from its group list (next +0xE / prev +0x10, group head/tail +0/+2 when it has no neighbour and a group) and from its object's list (onext +0x12 / oprev +0x14, object head/tail +0xC/+0xE), clears obj and the lock byte and pushes it on the free list at .bss+0x79180 (index link at +0xE). Inverse of isysAddGroupWithLinkParam. UNCONFIRMED: names.
 */
struct IsysGroup {
    unsigned short first;
    unsigned short last;
};
struct IsysObjHdr {
    char pad0[0xC];
    unsigned short ghead;
    unsigned short gtail;
};
struct GroupEnt {
    struct IsysObjHdr *obj;
    struct IsysGroup *group;
    int param;
    unsigned char lock;
    char padD;
    unsigned short next;
    unsigned short prev;
    unsigned short onext;
    unsigned short oprev;
    unsigned short link;
};
extern struct GroupEnt D_kernel_bss_27100[];
extern struct GroupEnt *D_kernel_bss_79180;

#define getIdx(e) ((e) ? (e) - D_kernel_bss_27100 : 0)

void func_019A70(struct GroupEnt *e) {
    struct IsysGroup *g = e->group;
    struct IsysObjHdr *obj = e->obj;

    if (e->next) {
        D_kernel_bss_27100[e->next].prev = e->prev;
    } else if (g) {
        g->last = e->prev;
    }
    if (e->prev) {
        D_kernel_bss_27100[e->prev].next = e->next;
    } else if (g) {
        g->first = e->next;
    }
    if (e->onext) {
        D_kernel_bss_27100[e->onext].oprev = e->oprev;
    } else {
        obj->gtail = e->oprev;
    }
    if (e->oprev) {
        D_kernel_bss_27100[e->oprev].onext = e->onext;
    } else {
        obj->ghead = e->onext;
    }
    e->obj = 0;
    e->lock = 0;
    e->next = getIdx(D_kernel_bss_79180);
    D_kernel_bss_79180 = e;
}
