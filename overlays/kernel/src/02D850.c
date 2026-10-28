/* KERNEL.XFF @ 0x02D850 (152 B) - vab_get_seprogchunk
 * Evidence: 0 unless vab_check_alive(id); then the VAB entry [id] (0x2C bytes at .bss+0x9BCC0) BD pointer (+0x14) chunk at +0x44: 0 when NULL or odd, or when its u16 count (+0) < idx; else chunk + u16 offset table[idx] (+2). UNCONFIRMED: field names.
 */
struct Sg2VabChunk {
    unsigned short num;
    unsigned short ofs[1];
};
struct Sg2VabBd {
    char pad[0x44];
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
void *vab_get_seprogchunk(int id, unsigned int idx) {
    struct Sg2VabEnt *v = &D_kernel_bss_9BCC0[id];
    struct Sg2VabChunk *c;
    if (vab_check_alive(id) == 0) return 0;
    if (v->bd == 0) return 0;
    c = v->bd->seprog;
 if (c == 0) return 0;
 if ((int)c & 1) return 0;
 if (c->num < idx) return 0;
 return (char *)c + *(c->ofs + idx);
}
