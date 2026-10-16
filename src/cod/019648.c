/* asm/cod/019648.s -> func_00118E58.
 * byte-exact under EE-GCC 2.95.3-136 (PE/wine)
 * MATCHED (Session 8). */
/* func_00119648 @ 0x00119648 (0x24 bytes): forwards through with a3=9,
 * a4=original a3, a5=0x10 to func_00118E58. */
int sceInetInterfaceControl(int a, int b, int c, int d, int e, int f);

void func_00119648(int a, int b, int c, int d) {
    sceInetInterfaceControl(a, b, c, 9, d, 0x10);
}
