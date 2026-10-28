/* KERNEL.XFF @ 0x0197E8 (644 B) - func_0197E8 (static, no symbol in the shipped .symtab)
 * Evidence: group list insertion (0x18-byte entries at .bss+0x27100, next +0xE, prev +0x10, group +4 with head/tail indices +0/+2): with no reference entry the entry becomes the only element; mode 0 inserts before rel, mode 1 after rel; other modes iosJumpRecoverPoint(.rodata+0x24A0). The copied neighbour index is tested through the assignment, then reloaded. UNCONFIRMED: names.
 */
struct IsysGroup {
    unsigned short first;
    unsigned short last;
};
struct GroupEnt {
    void *obj;
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
extern char D_kernel_rodata_24A0[];
void iosJumpRecoverPoint(const char *fmt, ...);

#define getEnt(i) ((i) ? &D_kernel_bss_27100[i] : 0)
#define getIdx(e) ((e) ? (e) - D_kernel_bss_27100 : 0)

void func_0197E8(struct GroupEnt *rel, struct GroupEnt *e, int mode) {
    if (rel == 0) {
        e->group->first = getIdx(e);
        e->group->last = getIdx(e);
        e->next = 0;
        e->prev = 0;
    } else {
    switch (mode) {
    case 0:
        if ((e->prev = rel->prev) != 0) {
            getEnt(rel->prev)->next = getIdx(e);
        } else {
            rel->group->first = getIdx(e);
        }
        e->next = getIdx(rel);
        rel->prev = getIdx(e);
        break;
    case 1:
        e->prev = rel - D_kernel_bss_27100;
        if ((e->next = rel->next) != 0) {
            getEnt(rel->next)->prev = getIdx(e);
        } else {
            rel->group->last = getIdx(e);
        }
        rel->next = getIdx(e);
        break;
    default:
        iosJumpRecoverPoint(D_kernel_rodata_24A0);
        break;
    }
    }
}
