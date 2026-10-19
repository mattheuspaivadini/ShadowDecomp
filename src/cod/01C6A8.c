/* asm/cod/01C6A8.s -> func_0011C6A8.
 * libmc FAT free-cluster search from the per-unit hint (wraps once to 0); SysInfo pointer local as in 01C7D8
 * MATCHED. */
struct F { int hint; char rest[0x898 - 4]; };
struct S { char pad00[0x170]; int f170; char rest[0x184 - 0x174]; };
extern struct S gSceMc2SysInfo[];
extern struct F D_0015E7D8[];
int func_0011C3B0(int index, int slot, int *out);

int func_0011C6A8(int index, int *out) {
    int i, r;
    struct S *s = &gSceMc2SysInfo[index];

    *out = 0;
    while (1) {
        for (i = D_0015E7D8[index].hint; i < s->f170; i++) {
            r = func_0011C3B0(index, i, out);
            if (*out != 0)
                return 0;
            if ((r & 0x80000000) == 0) {
                *out = 0;
                D_0015E7D8[index].hint = i;
                return i;
            }
        }
        if (D_0015E7D8[index].hint == 0)
            break;
        D_0015E7D8[index].hint = 0;
    }
    *out = 0x8101001C;
    return 0;
}
