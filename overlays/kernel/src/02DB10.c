/* KERNEL.XFF @ 0x02DB10 (132 B) - Sg2VabGetBdSize
 * Evidence: -1 unless vab_check_alive(id) and the 0x2C-byte VAB entry [id] (.bss+0x9BCC0) is alive; then word +4 of the record pointed to by +0x14 (ret variable with an else). UNCONFIRMED: field names.
 */
struct Sg2VabBd {
    int unk0;
    int size;
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
int Sg2VabGetBdSize(int id) {
 struct Sg2VabEnt *v = &D_kernel_bss_9BCC0[id];
 int ret;
 if (vab_check_alive(id) == 0) return -1;
 if (v->alive) ret = D_kernel_bss_9BCC0[id].bd->size; else ret = -1;
 return ret;
}
