/* asm/cod/026140.s -> func_001260A8 (cc=296).
 * list node init twin of 0260A8 (stmt-order swap + no sibcall).
 * MATCHED (Session 7, permuter). */
/* asm/cod/026140.s -> func_00126140 @ 0x00126140 (0x68 bytes, 26 insns)
 *
 * Twin of func_001260A8 (called from func_001261A8 with (a0,
 * func_00127768(0x18))): initialise a D_00169F90 list node and push it, but the
 * key a0 is written to *two* words (+0x0C first, then +0x08):
 *
 *   node->f0C = a0;                      ; 0x0C
 *   node->key = a0;                      ; 0x08
 *   node->f04 = 0;                       ; 0x04
 *   node->f00 = 0;                       ; 0x00
 *   node->f10 = 0;                       ; 0x10
 *   func_00107020(D_001329A4);           ; lock
 *   node->f14 = D_00169F90;              ; old head
 *   D_00169F90 = node;                   ; in the `jal func_00107000` delay slot
 *   func_00107000(D_001329A4);           ; unlock
 *
 * $s1 = the address of D_001329A4 (value re-loaded before each call).  Both jal
 * delay slots carry real instructions, the saves are 8 bytes apart.
 * MATCH GUESS: cc=296 (-g0) */
struct S169F90 {
    int f00;                        /* 0x00 */
    int f04;                        /* 0x04 */
    int f0C;                        /* 0x08 */
    int key;                        /* 0x0C */
    int f10;                        /* 0x10 */
    struct S169F90 *f14;            /* 0x14 next-in-list */
};

#include "symbols.h"

extern __attribute__((section(".data"))) struct S169F90 *D_00169F90;

int WaitSema(int a0);
int SignalSema(int a0);

void __register_frame_info_table(int key, struct S169F90 *node) {
    node->f0C = key;
    node->key = key;
    node->f04 = 0;
    node->f00 = 0;
    node->f10 = 0;
    WaitSema(__sce_eh_sema_id);
    node->f14 = D_00169F90;
    D_00169F90 = node;
    SignalSema(__sce_eh_sema_id);
}
