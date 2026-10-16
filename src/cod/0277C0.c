/* asm/cod/0277C0.s -> func_001277C0 @ 0x001277C0 (0x48 bytes, 18 insns)
 * Ref-counted acquire of the stdio state in D_00135C60:
 *   func_00128490(D_00135C60);          (reference the file; returns void)
 *   func_0012DBB0(D_00135C60, a0);      (acquire with argument a0)
 *   func_00128510(D_00135C60);          (release; tail call)
 * The object's address is built once into $s0 (lui + addiu %lo) and the *value*
 * is re-loaded before each of the three calls (the calls may change it); the
 * second call gets a0 in $a1.
 * MATCH GUESS: cc=296 (0x0288xx/0x02E5xx framed trampoline family) */
int _impure_ptr[];   /* .data 0x00135C60: lui/%lo (non-small) */
extern void __malloc_lock(int a0);
extern void _free_r(int a0, int a1);
extern void __malloc_unlock(int a0);

void free(int a0) {
    __malloc_lock(_impure_ptr[0]);
    _free_r(_impure_ptr[0], a0);
    __malloc_unlock(_impure_ptr[0]);
}
