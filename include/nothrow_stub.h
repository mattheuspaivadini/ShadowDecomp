/* NOTHROW_STUB: model a callee that the original translation unit defined
 * *before* the caller.
 *
 * ee-gcc 2.96 (rest_of_compilation) sets TREE_NOTHROW on every function whose
 * body cannot throw, and calls to a TREE_NOTHROW decl get a REG_EH_REGION 0
 * note.  Without that note can_throw() is true for every call, so reorg's
 * mark_target_live_regs/find_dead_or_set_registers stops scanning at the
 * call, keeps the call-clobbered registers live on that thread and fills a
 * conditional-branch delay slot with an *annulled* copy (beql/bnel) where the
 * original has a plain beq/bne (docs/decisions.md, 2026-10-18).
 *
 * A single-function C file only sees prototypes, so the callee is defined here
 * as an empty weak stand-in in a section the link script discards
 * (`/DISCARD/ : { *(*) }` keeps only `.text*` of each object).  The call
 * relocations stay against the callee's global symbol, which the strong
 * definition in asm/cod/ resolves.  Usage, before the caller:
 *
 *     void NOTHROW_STUB frame_init (struct object *ob) {}
 */
#ifndef NOTHROW_STUB_H
#define NOTHROW_STUB_H

#define NOTHROW_STUB __attribute__((weak, section(".nothrow_stub")))

#endif
