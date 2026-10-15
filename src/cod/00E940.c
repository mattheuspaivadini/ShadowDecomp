/* asm/cod/00E940.s -> func_0010E940 @ 0x0010E940 (0x90 bytes, 36 insns)
 *
 * Clone of func_0010E810 (00E810.c), only the transport command differs
 * (0xA instead of 8):
 *
 *   if (func_0010E238() < 0) return 0xFFFF0000;          ; bltz + lui in slot
 *   if (func_0010E338() != 0) return 0xFFFEFFFC;         ; memcmp clone
 *   D_00147380 = a0;                                     ; sw $s1,%lo($s0)
 *   if (SceSifrpcCall(D_00147580, 0xA, 0, &D_00147380, 4,
 *                    &D_00147380, 4, 0, 0) < 0)          ; 9th arg at $sp+0
 *       return 0xFFFEFFFF;                               ; bgezl + reload slot
 *   return D_00147380;                                   ; reload after the call
 *
 * Byte-for-byte the same shape as 00E810.s with `addiu $a1,$zero,0xA`.
 * MATCH GUESS: cc=296 (the 0x0010Exxx block: 00E9D0/00E9F0 are cc=296 TUs) */
int func_0010E238(void);
int func_0010E338(void);
int SceSifrpcCall(int a0, int a1, int a2, int a3, int a4, int a5, int a6,
                  int a7, int a8);

extern int D_00147380[];   /* .bss/.data, outside small-data -> lui/%lo */
extern int D_00147580[];   /* .bss transfer buffer          -> lui/addiu */

int func_0010E940(int a0) {
    if (func_0010E238() < 0)
        return 0xFFFF0000;
    if (func_0010E338() != 0)
        return 0xFFFEFFFC;
    D_00147380[0] = a0;
    if (SceSifrpcCall((int)D_00147580, 0xA, 0, (int)D_00147380, 4,
                      (int)D_00147380, 4, 0, 0) < 0)
        return 0xFFFEFFFF;
    return D_00147380[0];
}
