/* KERNEL.XFF @ 0x02D8E8 (172 B) - vab_get_progchunk
 * Evidence: as vab_get_seprogchunk on the BD chunk at +0x30: 0 unless alive, BD present, chunk non-NULL and even, idx <= u16 count and the u16 offset entry [idx] != 0xFFFF (entry read twice); else chunk + offset. UNCONFIRMED: field names.
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

void *vab_get_progchunk(int id, unsigned int idx) {
    struct Sg2VabEnt *v = &D_kernel_bss_9BCC0[id];
    struct Sg2VabChunk *c;

    if (vab_check_alive(id) == 0) {
        return 0;
    }
    if (v->bd == 0) {
        return 0;
    }
    c = v->bd->prog;
    if (c == 0) {
        return 0;
    }
    if ((int)c & 1) {
        return 0;
    }
    if (c->num < idx) {
        return 0;
    }
    if (*(c->ofs + idx) == 0xFFFF) {
        return 0;
    }
    return (char *)c + *(c->ofs + idx);
}
