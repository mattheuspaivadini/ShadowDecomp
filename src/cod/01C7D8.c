/* asm/cod/01C7D8.s -> func_0011C7D8.
 * FAT entry counter; typed 0x898/0x184 records, SysInfo pointer local (Session 23)
 * MATCHED. */
struct F { char pad00[0x890]; int f890; int f894; };
struct S { char pad00[0x170]; int f170; char rest[0x184 - 0x174]; };
extern struct S gSceMc2SysInfo[];
extern struct F D_0015DF48[];
int func_0011C3B0(int index, int slot, int *out);

int func_0011C7D8(int index, int *out) {
    int i, n, r;
    struct S *s = &gSceMc2SysInfo[index];
    *out = 0;
    n = 0;
    for (i = D_0015DF48[index].f890; i < s->f170; i++) {
        r = func_0011C3B0(index, i, out);
        if (*out != 0) return 0;
        if ((r & 0x80000000) == 0) n++;
    }
    return n;
}
