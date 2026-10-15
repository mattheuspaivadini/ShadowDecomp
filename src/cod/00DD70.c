/* asm/cod/00DD70.s -> func_0010DD70 @ 0x0010DD70 (0x70 bytes, 28 insns)
 *
 * Publish one word into D_00147240 and run the 9-argument SceSifrpcCall
 * transfer, then return the first word of the D_00147200 result block:
 *   if (D_0013232C < 0) return 0;                ; signed guard
 *   D_00147240[0] = a0;                          ; the incoming word
 *   r = SceSifrpcCall(&D_001471C0, 1, 0, &D_00147240, 4, &D_00147200, 4, 0, 0);
 *   if (r < 0) return 0;
 *   return D_00147200[0];
 * a0 is copied to $a1 at the top because a0 is reloaded with &D_001471C0 for
 * the call; the 9th argument is the `sw $zero,0x0($sp)` outgoing word. The two
 * `return 0`s are cross-jumped by gcc (the shared block sits after the body),
 * and the D_00147200 load is hoisted into the bgez delay slot.
 * MATCH GUESS: cc=29 (the SceSifrpcCall 9-arg family, cf. the matched 015A30)
 */
extern int D_0013232C __attribute__((section(".data")));
extern int D_001471C0[];   /* .bss 0x001471C0, 0x40 bytes */
extern int D_00147200[];   /* .bss 0x00147200, 0x40 bytes */
extern int D_00147240[];   /* .bss 0x00147240, 0x40 bytes */

int SceSifrpcCall(int a0, int a1, int a2, int a3, int a4, int a5, int a6,
                  int a7, int a8);

int func_0010DD70(int a0) {
    int r;

    if (D_0013232C < 0)
        return 0;
    D_00147240[0] = a0;
    r = SceSifrpcCall((int)D_001471C0, 1, 0, (int)D_00147240, 4,
                      (int)D_00147200, 4, 0, 0);
    if (r < 0)
        return 0;
    return D_00147200[0];
}
