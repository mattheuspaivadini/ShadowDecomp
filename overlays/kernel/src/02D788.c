/* KERNEL.XFF @ 0x02D788 (196 B) - vab_get_seseq
 * Evidence: 0 unless vab_check_alive(id), BD present and its chunk at +0x3C non-NULL with idx <= u16 count; off = entry[idx] >> 1 (u16 index); 0 when u16 [off] < sub, else chunk + u16 [off + sub + 1]. UNCONFIRMED: field names.
 */
struct Sg2VabChunk {
    unsigned short num;
    unsigned short ofs[1];
};
struct Sg2VabBd {
    char pad[0x30];
    struct Sg2VabChunk *prog;
    char pad34[0x3C - 0x34];
    struct Sg2VabChunk *seseq;
    struct Sg2VabChunk *seprog;
};
struct Sg2VabEnt {
    int alive;
    int unk4;
    int unk8;
    int info;
    int unk10;
    struct Sg2VabBd *bd;
    char pad18[0x2C - 0x18];
};
extern struct Sg2VabEnt D_kernel_bss_9BCC0[8];
int vab_check_alive(int id);

void *vab_get_seseq(int id, unsigned int idx, unsigned int sub) {
    struct Sg2VabEnt *v = &D_kernel_bss_9BCC0[id];
    struct Sg2VabChunk *c;
    unsigned int off;

    if (vab_check_alive(id) == 0) {
        return 0;
    }
    if (v->bd == 0) {
        return 0;
    }
    c = v->bd->seseq;
    if (c == 0) {
        return 0;
    }
    if (c->num < idx) {
        return 0;
    }
    off = *(c->ofs + idx) >> 1;
    if (((unsigned short *)c)[off] < sub) {
        return 0;
    }
    return (char *)c + ((unsigned short *)c)[off + sub + 1];
}
