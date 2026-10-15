/* asm/cod/02E490.s -> func_00128E6C.
 * PART1 02E490 store-order swap (a0[0x30]=a1 before a0[0x34]=a2), MATCH cc=296
 * MATCHED (Session 8). */
extern char D_00139B48[];   /* absolute lui/addiu */
extern char D_00139B38[];   /* absolute lui/addiu */

int func_00128E6C(int a0, int a1);

int func_0012E490(int *a0, int a1, int a2) {
    if (a2 != 0) {
        if (func_00128E6C(a2, (int)D_00139B48) != 0) {
            if (func_00128E6C(a2, (int)D_00139B38) != 0)
                return 0;
        }
        a0[0x30 / 4] = a1;
        a0[0x34 / 4] = a2;
    }
    return (int)D_00139B48;
}
