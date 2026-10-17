/* asm/cod/002C90.s -> if.
 * loader (cc=296; SDK prototypes from the image)
 * MATCHED. */
/* asm/cod/002C90.s -> func_00102C90 @ 0x00102C90 (0x64 bytes, 25 insns)
 *
 * Release/clear the 256-entry pointer table D_0013C790 (.bss, 0x400 bytes):
 *
 *   func_00108FF8(0);
 *   func_0010DCE8();
 *   p = (int *)D_0013C790;
 *   for (i = 0xFF; i >= 0; i--) {        ; `addiu $s1,$zero,0xFF` ... `bgez`
 *       if (*p != 0) {                   ; beqz skips the body
 *           func_0010DED8();             ; release
 *           *p = 0;
 *       }
 *       p++;                             ; `addiu $s0,$s0,0x4` in the bgez slot
 *   }
 *
 * The `-1` per-iteration decrement sits in the `beqz` shadow (scheduler).
 * MATCH GUESS: cc=296
 */
#include "symbols.h"

int sceSifInitRpc(int x);
int sceSifInitIopHeap(void);
int sceSifFreeIopHeap(void *addr);

void LoaderSysDeleteAllExternalIopMemory(void) {
    int i;
    int *p;

    sceSifInitRpc(0);
    sceSifInitIopHeap();
    p = (int *)D_0013C790;
    for (i = 0; i < 0x100; i++) {
        if (*p != 0) {
            sceSifFreeIopHeap((void *)*p);
            *p = 0;
        }
        p++;
    }
}
