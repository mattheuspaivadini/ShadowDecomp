/* asm/cod/006518.s -> func_00106518 @ 0x00106518 (0x70 bytes, 28 insns)
 *
 * Two-way GS path setup through the 0x20000000 RAM mirror; a1 selects the
 * second (0x100-higher) set:
 *   p = (char *)(a0 | 0x20000000);
 *   if (a1 != 0) { func_00114080(p + 0x150, 0x800, 0x800, (short)a2);
 *                  sceGsPutDrawEnv(p + 0x140); }
 *   else         { func_00114080(p + 0x60,  0x800, 0x800, (short)a2);
 *                  sceGsPutDrawEnv(p + 0x50);  }
 * The base is `lui $v0,%hi(D_20000060)` (0x20000000) ORed into a0; the four
 * spimdisasm `%lo(D_20000xxx)` addends are the 0x50/0x60/0x140/0x150
 * displacements. a2 is sign-extended once at the top (`sll`/`sra` pair in $a3,
 * with the pre-shift value parked in $v1) and recomputed in the else arm, and
 * a2 is overwritten with 0x800 (a2 is also the third argument of the call).
 * MATCH GUESS: cc=296 (both sceGsPutDrawEnv calls are `j` with the frame
 * teardown in the delay slot)
 */
int func_00114080(void *dst, int a1, int a2, short a3);
void sceGsPutDrawEnv(void *env);

void func_00106518(unsigned int a0, int a1, int a2) {
    char *p = (char *)(a0 | 0x20000000);

    if (a1 != 0) {
        func_00114080(p + 0x150, 0x800, 0x800, (short)a2);
        sceGsPutDrawEnv(p + 0x140);
    } else {
        func_00114080(p + 0x60, 0x800, 0x800, (short)a2);
        sceGsPutDrawEnv(p + 0x50);
    }
}
