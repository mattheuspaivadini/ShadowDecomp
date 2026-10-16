/* asm/cod/012B98.s -> sceSifExitCmd.
 * sceSifExitCmd: D_0014B354 array decl
 * MATCHED (Session 12). */
int DisableDmac(int x);
int RemoveDmacHandler(int a, int b);

extern int D_0014B354[];
extern int D_00133948 __attribute__((section(".data")));

void sceSifExitCmd(void) {
    DisableDmac(5);
    RemoveDmacHandler(5, D_0014B354[0]);
    D_00133948 = 0;
}
