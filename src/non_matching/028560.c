/* STATUS (Session 7, 2026-10-14): NON_MATCHING. best score 18 [cc=29, default].
 * variadic vfprintf trampoline.
 * The original .s stays in the build (asm/cod/028560.s); this C
 * draft (subagent-produced, Session 7) is kept for the record. */
/* asm/cod/028560.s -> func_00128560 @ 0x00128560 (0x5C bytes, 23 insns)
 *
 * Variadic print trampoline - the sibling of func_001285C0 (the variadic print
 * entry point that the matched asm/cod/002FE8.s tail-calls). The EE-GCC varargs
 * prologue spills $a2-$a7 and $f12-$f19 (two fixed arguments) and the call is
 *
 *   vfprintf(a0, *(int *)(a0 + 8), (char *)a1, va);
 *
 * i.e. the first fixed argument is the reent-like object, its 0x8 field is the
 * FILE handle ($a1 loaded from 0x8($a0) in the jal delay slot), the second fixed
 * argument is the format ($a2 = $a1), and $a3 = $sp+0x30 is the varargs
 * register-save area (the 3rd fixed argument onwards) - exactly what
 * __builtin_saveregs() yields; the toolchain ships no stdarg.h, so the builtin
 * is used directly (same idiom as src/non_matching/008DB8.c).
 *
 * The 4-argument callee is vfprintf @ 0x001299A8 as called by func_00129930
 * (asm/cod/029930.s: $a0 = the handle stored at 0x54 of the FILE, $a1 = the
 * FILE, $a2 = format, $a3 = va_list).
 * MATCH GUESS: cc=296 (the printf family: the matched 002FE8/003FF8 are cc=296) */
int vfprintf(int a0, int a1, char *fmt, int ap);

int func_00128560(int a0, int a1, ...) {
    return vfprintf(a0, (int)*(int **)(a0 + 8), (char *)a1,
                    (int)__builtin_saveregs());
}
