/* asm/cod/007CA8.s -> func_00112330.
 * R4 w25a_0 (base kept in $s2 per arm)
 * MATCHED (Session 8). */
extern int  D_00132284 __attribute__((section(".data")));
extern char D_001440A0[];   /* .data 0x80-byte output buffer */

void kputs(char *a0);

void func_00107CA8(int c) {
    int n;

    n = D_00132284;
    if (n >= 0x7E) {
        D_00132284 = 0;
        D_001440A0[0x7F] = 0;
        kputs(D_001440A0);
        n = D_00132284;
    }
    if (c == 0xA) {
        D_00132284 = 0;
        D_001440A0[n] = c;
        D_001440A0[n + 1] = 0;
        kputs(D_001440A0);
    } else {
        D_00132284 = n + 1;
        D_001440A0[n] = c;
    }
}
