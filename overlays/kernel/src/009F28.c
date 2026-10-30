/* KERNEL.XFF @ 0x009F28 (244 B) - isysDisposeModuleObjRelocationElement
 * STATUS: NOT MATCHING, 240 B vs 244 B. Not in c_sources.txt.
 * Shape is right (two n-iteration loops over 0x1C-byte entries at hdr->0x3C; sum of ent[i].cnt (+4); func_00A710(h, ent[0].off + sum*8);
 * zero ent[i].cnt; return hdr->0x14 - (ent[n].off - h)). Residual: the image loads s1 = obj->0x1C, THEN the .data+0x378 magic,
 * and keeps h in s1 / n in s0; every variant loads the magic first and swaps s0/s1. Tried: local m = magic after h, swapped compare,
 * decls n/sum/i before h, -fno-schedule-insns, -g0.
 */
struct ModEnt { int a; int cnt; int b; int off; int c[3]; };
struct ModImg {
    int magic;
    char pad04[0x10];
    int size;
    char pad18[0x20];
    int nent2;
    struct ModEnt *ent;
};
struct ModObjX { char pad[0x1C]; struct ModImg *img; };
extern int D_kernel_data_0378;
extern void func_00A710(struct ModImg *h, int p);

int isysDisposeModuleObjRelocationElement(struct ModObjX *obj) {
    int n;
    int sum;
    int i;
    int ret = 0;
    struct ModImg *h = obj->img;

    if (h->magic == D_kernel_data_0378) {
        n = h->nent2 >> 1;
        sum = 0;
        for (i = 0; i < n; i++) {
            sum += h->ent[i].cnt;
        }
        func_00A710(h, h->ent[0].off + sum * 8);
        for (i = 0; i < n; i++) {
            h->ent[i].cnt = 0;
        }
        ret = h->size - (h->ent[n].off - (int)h);
    }
    return ret;
}
