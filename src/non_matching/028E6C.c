/* C equivalent of func_00128E6C (028E6C, 324 B @ 0x00128E6C) -- strcmp.
 *
 * Reconstructed from asm/cod/028E6C.s and the REA/Ghidra Emotion Engine
 * dossier ev_762ecd6fd582ca6c9f25d841fc7713aed7033bd9e29847da2d71bd0fa17a1123,
 * and cross-checked with the matched sibling 0290C4 (strlen), which uses the
 * same MMI null test.  Readable reconstruction: NOT byte-exact (the delay-slot
 * placement of the 16-byte `pnor` cannot be produced by any installed cc1),
 * not part of the build.  The codegen-tuned near-miss is
 * src/non_matching/archive/028E6C.c.
 *
 * The EE libc compares 16 bytes at a time when both pointers are 16-aligned,
 * 8 bytes when only 8-aligned, and falls back to a byte loop.  MMI has no C
 * operators in this compiler generation, so the three vector primitives are
 * spelled out as asm, exactly as the original source must have done (P2).
 *
 * Behaviour derived from the target:
 *   128E7C  lq/psubw/pcpyud/or   -> 16-byte lane difference test
 *   128E88  bnel a5,zero         -> the first test is done before the loop
 *   128EDC  psubb/pand/pcpyud/or-> 16-byte NUL test (0x0101.. / 0x8080..)
 *   128F34  ld + bnel            -> 8-byte word compare
 *   128F9C  lbu/lb/sll/sra       -> byte loop, unsigned difference on return
 */
typedef unsigned int u_long128 __attribute__((mode(TI)));

/* non-zero when any 32-bit lane of the two 16-byte blocks differs */
static __inline__ int neq16(const void *a, const void *b)
{
    u_long128 x = *(const u_long128 *)a;
    u_long128 y = *(const u_long128 *)b;
    u_long128 d, u;
    unsigned long r;

    __asm__("psubw %0,%1,%2" : "=r"(d) : "r"(x), "r"(y));
    __asm__("pcpyud %0,%1,%2" : "=r"(u) : "r"(d), "r"(d));
    __asm__("or %0,%1,%2" : "=r"(r) : "r"(u), "r"(d));
    return r != 0;
}

/* non-zero when the 16-byte block contains a zero byte */
static __inline__ int haszero16(const void *p)
{
    u_long128 x = *(const u_long128 *)p;
    u_long128 o, h, z, m, u;
    unsigned long ones = 0x0101010101010101;
    unsigned long hi = 0x8080808080808080;
    unsigned long r;

    __asm__("pcpyld %0,%1,%1" : "=r"(o) : "r"(ones));
    __asm__("pnor %0,$0,%1" : "=r"(z) : "r"(x));
    __asm__("pcpyld %0,%1,%1" : "=r"(h) : "r"(hi));
    __asm__("psubb %0,%1,%2" : "=r"(x) : "r"(x), "r"(o));
    __asm__("pand %0,%1,%2" : "=r"(x) : "r"(x), "r"(z));
    __asm__("pand %0,%1,%2" : "=r"(m) : "r"(x), "r"(h));
    __asm__("pcpyud %0,%1,%2" : "=r"(u) : "r"(m), "r"(m));
    __asm__("or %0,%1,%2" : "=r"(r) : "r"(u), "r"(m));
    return r != 0;
}

/* non-zero when the 8-byte word contains a zero byte */
static __inline__ int haszero8(unsigned long x)
{
    return (x - 0x0101010101010101UL) & ~x & 0x8080808080808080UL;
}

int func_00128E6C(const char *s1, const char *s2)
{
    if ((((long)s1 | (long)s2) & 7) == 0) {
        if ((((long)s1 | (long)s2) & 15) == 0) {
            if (!neq16(s1, s2)) {
                for (;;) {
                    if (haszero16(s1))
                        return 0;
                    s1 += 16;
                    s2 += 16;
                    if (neq16(s1, s2))
                        break;
                }
            }
        } else if (*(const unsigned long *)s1 == *(const unsigned long *)s2) {
            for (;;) {
                if (haszero8(*(const unsigned long *)s1))
                    return 0;
                s1 += 8;
                s2 += 8;
                if (*(const unsigned long *)s1 != *(const unsigned long *)s2)
                    break;
            }
        }
    }
    while (*s1 != '\0') {
        if (*s1 != *s2)
            break;
        s1++;
        s2++;
    }
    return (unsigned char)*s1 - (unsigned char)*s2;
}
