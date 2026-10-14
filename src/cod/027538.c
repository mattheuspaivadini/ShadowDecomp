/* asm/cod/027538.s -> func_00127538 @ 0x00127538 (0x64 bytes, 25 insns)
 *
 * Ref-counted operation on the stdio state in D_00135C60:
 *   func_00128490(D_00135C60[0]);                  ; reference the file (void)
 *   r = func_001275A0(D_00135C60[0], a0, a1);      ; the operation
 *   func_00128510(D_00135C60[0]);                  ; release (void)
 *   return r;
 * The object's address is built once into $s0 (lui + addiu %lo) and its *value*
 * is re-loaded before each of the three calls (the calls may change it); $s2
 * keeps a0 across the first call and $s1 keeps a1 and is then reused for the
 * result - exactly the shape of the matched func_00127768 (same family, 8-byte
 * spaced saves).
 * MATCH GUESS: cc=296 */
#include "symbols.h"

extern int func_001275A0(int a0, int a1, int a2);
extern void func_00128490(int a0);
extern void func_00128510(int a0);

int func_00127538(int a0, int a1) {
    int r;

    func_00128490(D_00135C60);
    r = func_001275A0(D_00135C60, a0, a1);
    func_00128510(D_00135C60);
    return r;
}
