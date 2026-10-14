/* asm/cod/0260A8.s -> func_001260A8 @ 0x001260A8 (0x68 bytes, 26 insns)
 *
 * Initialise a node and push it on the D_00169F90 list (the list walked by
 * func_001261D8, which compares the node's +0x08 word against a key and follows
 * the +0x14 link):
 *
 *   node->key = a0;                      ; 0x08, stored first
 *   node->f04 = 0;                       ; 0x04
 *   node->f00 = 0;                       ; 0x00
 *   node->f0C = 0;                       ; 0x0C
 *   node->f10 = 0;                       ; 0x10
 *   func_00107020(D_001329A4);           ; lock (semaphore take)
 *   node->f14 = D_00169F90;              ; old head, loaded after the lock
 *   D_00169F90 = node;                   ; in the `jal func_00107000` delay slot
 *   func_00107000(D_001329A4);           ; unlock
 *
 * $s1 holds the address of D_001329A4 (lui/addiu built before the stores), the
 * value being re-loaded (`lw $a0,0x0($s1)`) before each of the two calls.  The
 * caller (func_00126110) passes (a0, func_00127768(0x18)) so a0 is the key and
 * $a1 the node.  Both jal delay slots carry real instructions and the saves are
 * 8 bytes apart -> the 296 slot layout.
 * MATCH GUESS: cc=296 (-g0: the two jal delay slots are filled) */
struct S169F90 {
    int f00;                        /* 0x00 */
    int f04;                        /* 0x04 */
    int key;                        /* 0x08 */
    int f0C;                        /* 0x0C */
    int f10;                        /* 0x10 */
    struct S169F90 *f14;            /* 0x14 next-in-list */
};

#include "symbols.h"

extern __attribute__((section(".data"))) struct S169F90 *D_00169F90;

int func_00107020(int a0);
int func_00107000(int a0);

void func_001260A8(int key, struct S169F90 *node) {
    node->key = key;
    node->f04 = 0;
    node->f00 = 0;
    node->f0C = 0;
    node->f10 = 0;
    func_00107020(D_001329A4);
    node->f14 = D_00169F90;
    D_00169F90 = node;
    func_00107000(D_001329A4);
}
