/* asm/cod/027768.s -> func_00127768 @ 0x00127768 (0x54 bytes, 21 insns)
 *
 * Ref-counted operation on the stdio state in D_00135C60:
 *   func_00128490(D_00135C60[0]);            (reference the file; void)
 *   r = func_00127A60(D_00135C60[0], a0);    (the operation; a0 is the 2nd arg)
 *   func_00128510(D_00135C60[0]);            (release)
 *   return r;
 * The object's address is built once into $s0 (lui + addiu %lo) and its *value*
 * is re-loaded before each of the three calls (the calls may change it); the
 * incoming a0 is saved into $s1 across the first call and $s1 is then reused
 * for the result. The three saves are 8 bytes apart ($s0, $s1, $ra) - the
 * cc=296 slot layout, as in the matched sibling 0277C0.
 * MATCH GUESS: cc=296 */
int _impure_ptr[];   /* .data 0x00135C60: lui/%lo (non-small) */
extern void __malloc_lock(int a0);
extern int _malloc_r(int a0, int a1);
extern void __malloc_unlock(int a0);

int malloc(int a0) {
    int r;

    __malloc_lock(_impure_ptr[0]);
    r = _malloc_r(_impure_ptr[0], a0);
    __malloc_unlock(_impure_ptr[0]);
    return r;
}
