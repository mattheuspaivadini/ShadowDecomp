/* asm/cod/010F40.s -> func_00110F40 @ 0x00110F40 (0x5C bytes, 23 insns)
 *
 * Guard/target wrapper of the func_0010FB20 family:
 *   a = func_0010FB20();              (the critical-section guard)
 *   b = func_00110EF0(a0, a1);        (the protected operation)
 *   if (a)
 *       func_0010FB70();              (release)
 *   return b;
 * The single trailing `return b` is load-bearing (with an early return the
 * `beqz` would target the epilogue, as in the matched 011168). a0/a1 are saved
 * into $s0/$s1 before the first call and re-loaded for the second.
 * The saves are 16 bytes apart ($s0 0x00, $s1 0x10, $s2 0x20, $ra 0x30, frame
 * 0x40) - the cc=29 slot layout of this whole family.
 * MATCH GUESS: cc=29 */
int func_0010FB20(void);
int func_00110EF0(int a0, int a1);
int func_0010FB70(void);

int func_00110F40(int a0, int a1) {
    int a = func_0010FB20();
    int b = func_00110EF0(a0, a1);

    if (a != 0)
        func_0010FB70();
    return b;
}
