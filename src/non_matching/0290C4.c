/* STATUS (Session 54, 2026-10-23): NON_MATCHING. best score 35 [cc=ee-gcc2.9-990721-as991111 -malign-loops=2].
 * Formerly classed asm-permanent ("hand-vectorised MMI strlen"). Evidence that it is C: the
 * control flow, the GCC dli constant expansion, the re-materialised 0x0101.. constant in the
 * 8-byte loop, branch-likely loops and the GAS short-loop nops are all reproduced by ee-gcc
 * 2.9-ee-990721 cc1 + the 2.9-ee-991111 assembler (tools/cc/make_hybrid_990721.sh) with
 * -malign-loops=2 (990721 aligns loop labels to 8 by default; the image does not). The MMI
 * operations are inline asm; the pcpyud rt operand is a don't-care: the pre-loop test reads an
 * uninitialised value (cc=29-era cc1s give an uninitialised pseudo an arbitrary register, which
 * is what the image shows: t0), the loop test reads the pre-loop result t (a2).
 * Residual (35 words): register roles only. The image keeps the aligned pointer as CSE's
 * canonical copy (loads via a1, str's a0 reused for the 0x8080.. mask); ours loads through str
 * (a0), which cascades into start/o/h/t allocation (image: a3/t0/t1/a2).
 * Tried: Newlib-shaped inline helper (no exit-test duplication in 2.9 cc1s: block notes),
 * while/for(;;)/do-while forms, masks inside the macro (no CSE between copies), TImode vs
 * DImode masks/temps, statement order of aligned/ones, register qualifiers, parameter copies,
 * -fno-cse-follow-jumps/-fno-rerun-cse-after-loop/-fno-gcse/-fno-strength-reduce; ee-gcc2.96
 * builtins (__builtin_mips5900_*: V2DI/V16QI only, scalar<->vector casts add por moves);
 * cc=29 (46), cc=296 (74).
 * The original .s stays in the build (asm/cod/0290C4.s); this C
 * draft (Session 54) is kept for the record. */
typedef unsigned int size_t;
typedef unsigned int u_long128 __attribute__((mode(TI)));

#define UNALIGNED(X) ((long)X & (sizeof (long) - 1))

static __inline__ unsigned long detectnull(unsigned long x)
{
    unsigned long ones = 0x0101010101010101;
    return (x - ones) & ~x & 0x8080808080808080;
}

/* t is only a don't-care pcpyud operand (the upper half of rd is never used) */
#define DETECTNULL128(V) ({ \
    u_long128 x, y; \
    unsigned long m, u; \
    asm("psubb %0,%1,%2" : "=r"(x) : "r"(V), "r"(o)); \
    asm("pnor %0,$0,%1" : "=r"(y) : "r"(V)); \
    asm("pand %0,%1,%2" : "=r"(x) : "r"(x), "r"(y)); \
    asm("pand %0,%1,%2" : "=r"(m) : "r"(x), "r"(h)); \
    asm("pcpyud %0,%1,%2" : "=r"(u) : "r"(m), "r"(t)); \
    u | m; })

size_t func_001290C4(const char *str)
{
    const char *start = str;
    unsigned long *aligned_addr;

    if (!UNALIGNED(str)) {
        unsigned long ones = 0x0101010101010101;
        aligned_addr = (unsigned long *)str;
        if (((long)str & 15) == 0) {
            u_long128 o, h;
            unsigned long t, hi = 0x8080808080808080;
            asm("pcpyld %0,%1,%1" : "=r"(o) : "r"(ones));
            asm("pcpyld %0,%1,%1" : "=r"(h) : "r"(hi));
            t = DETECTNULL128(*(u_long128 *)aligned_addr);
            if (t == 0) {
                do
                    aligned_addr += 2;
                while (DETECTNULL128(*(u_long128 *)aligned_addr) == 0);
            }
        } else {
            while (!detectnull(*aligned_addr))
                aligned_addr++;
        }
        str = (char *)aligned_addr;
    }
    while (*str)
        str++;
    return str - start;
}
