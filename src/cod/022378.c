/* asm/cod/022378.s -> func_00122378.
 * session9 R1 wcg wave
 * MATCHED (Session 8). */
struct S022378 {
    char b[0x310];
};

extern char D_00167F00[];

int func_00122378(char *dst) {
    *(struct S022378 *)dst = *(struct S022378 *)D_00167F00;
    return 0;
}
