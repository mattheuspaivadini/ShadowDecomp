/* KERNEL.XFF @ 0x00D568 (108 B) - iosApplyM_Mat
 * Evidence: the caller's `Mvec *` operand is copied into a 16-byte stack slot
 * with `ld v1,0(a2)/ld v0,8(a2)` + `sd` pair and reloaded as one 128-bit value
 * with `lq v0,0(sp)` (the Mvec union idiom of the matched neighbours 00D410 /
 * 00D510). The loop applies one 16-byte matrix row to that vector: pmultw +
 * mtsab 4 + two qfsrv builds the 128-bit product, pmultw/paddw sums the halves,
 * mtsab 8 + qfsrv folds the 64-bit halves and paddw produces the 32-bit result,
 * which is stored at row+0x10 and the pointer advances 0x10 then 4 (20-byte
 * rows: 4 floats + int result). `sq/lq s0,0x10(sp)` is the callee-save of the
 * 128-bit $s0 that the qfsrv result uses, so $16 is clobbered by the block.
 * The shipped schedule keeps `li t2,4`, the counter decrement and the two
 * pointer adds inside the MMI chain, which only reproduces when the whole loop
 * is one asm block (numeric GPRs; this gas rejects $v0/$t0 spellings) and the
 * vector reaches it as a memory operand (`lq $2, %1`), so no register is
 * reserved for it. Verified byte-exact with -G0 and -G0 -fno-strict-aliasing.
 * UNCONFIRMED: parameter names/types beyond the Mvec union.
 */
typedef unsigned int u_long128 __attribute__((mode(TI)));
typedef struct { long lo, hi; } Mvec;
typedef union { Mvec v; u_long128 q; } MvecU;

void iosApplyM_Mat(int unused, char *pp, Mvec *v) {
    MvecU u;

    u.v = *v;
    __asm__ __volatile__(
        "lq $2, %1\n"
        "li $10, 4\n"
        "1:\n"
        "lq $8, 0x0(%0)\n"
        "addi $10, $10, -1\n"
        "pmultw $9, $2, $8\n"
        "addi %0, %0, 0x10\n"
        "mtsab $0, 0x4\n"
        "qfsrv $12, $0, $8\n"
        "qfsrv $13, $0, $2\n"
        "pmultw $14, $13, $12\n"
        "paddw $15, $9, $14\n"
        "mtsab $0, 0x8\n"
        "qfsrv $16, $0, $15\n"
        "paddw $11, $15, $16\n"
        "sw $11, 0x0(%0)\n"
        "addi %0, %0, 0x4\n"
        "bgtz $10, 1b\n"
        : "+r"(pp)
        : "m"(u.q)
        : "$2", "$8", "$9", "$10", "$11", "$12", "$13", "$14", "$15", "$16",
          "memory");
}
