/* STATUS (Session 7, 2026-10-14): NON_MATCHING. best score 18 [cc=29, default].
 * VIF1/GS reset; register roles differ.
 * The original .s stays in the build (asm/cod/013530.s); this C
 * draft (subagent-produced, Session 7) is kept for the record. */
/* asm/cod/013530.s -> func_00113530 @ 0x00113530 (0x68 bytes, 26 insns)
 *
 * GS/VIF path reset (the func_00113520 sibling block; register identities from
 * docs/structs.md, confirmed against ps2sdk/PCSX2):
 *
 *   *(volatile u32 *)0x10003C10 = 1;     ; VIF1_FBRST  (force break)
 *   *(volatile u32 *)0x10003C20 = 2;     ; VIF1_ERR
 *   sync;                                ; fence between the VIF reset and the
 *                                        ; VU0 write
 *   $vi28 |= 0x200;                      ; VU0 status: set macro mode
 *                                        ; (cfc2.ni -> ori 0x200 -> ctc2.ni)
 *   sync.p;
 *   write the 0x20-byte template D_00133980 to the VIF1 FIFO 0x10005000 as two
 *   16-byte quads (lq 0($a1)/sq -> lq 0x10($a1)/sq);
 *   *(volatile u32 *)0x10003000 = 1;     ; GIF_CTRL (in the `jr $ra` shadow)
 *
 * The `$vi28` access (named COP2 register) and the lq/sq quads have no plain-C
 * form, so the VU0/fence part is one inline-asm block and the two FIFO quads
 * another; the four hardware stores are volatile stores. Both asm blocks use a
 * dummy register output (no named-register clobber, which ee-gcc 2.96 rejects).
 * RESIDUAL (expected): the original materialises `1` once into $a3 and reuses it
 * for the first and the last store, and its FIFO quads use $a0 then $v0; the
 * register choices of this version may differ.
 * MATCH GUESS: cc=296
 */
#define VIF1_FBRST 0x10003C10u
#define VIF1_ERR   0x10003C20u
#define VIF1_FIFO  0x10005000u
#define GIF_CTRL   0x10003000u

extern char D_00133980[];   /* .data 0x00133980, 0x20-byte VIF1 packet template */

void func_00113530(void) {
    unsigned int vu0;
    unsigned int quad;

    *(volatile unsigned int *)VIF1_FBRST = 1;
    *(volatile unsigned int *)VIF1_ERR = 2;
    __asm__ __volatile__("sync" ::: "memory");
    __asm__ __volatile__("cfc2.ni %0, $vi28\n\t"
                         "ori %0, %0, 0x200\n\t"
                         "ctc2.ni %0, $vi28\n\t"
                         "sync.p"
                         : "=r"(vu0));
    __asm__ __volatile__("lq %0, 0x0(%1)\n\t"
                         "sq %0, 0x0(%2)\n\t"
                         "lq %0, 0x10(%1)\n\t"
                         "sq %0, 0x0(%2)"
                         : "=r"(quad)
                         : "r"(D_00133980), "r"((void *)VIF1_FIFO));
    *(volatile unsigned int *)GIF_CTRL = 1;
}
