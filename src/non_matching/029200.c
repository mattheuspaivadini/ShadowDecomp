/* C equivalent of func_00129200 (029200, 440 B @ 0x00129200) -- strncmp.
 *
 * Reconstructed from asm/cod/029200.s and the REA/Ghidra Emotion Engine
 * dossier ev_e7f5063dcfa2d8102c090f954a4f3a230eb956aa21c1e8cf4d63c11c0e7dbb97,
 * cross-checked with 028E6C (strcmp) and the matched 0290C4 (strlen).  Readable
 * reconstruction: NOT byte-exact (42-74 diff instructions in the block-entry
 * predicates and pointer bumps), not part of the build.  The codegen-tuned
 * near-miss is src/non_matching/archive/029200.c.
 *
 * Same strategy as strcmp, bounded by n: a 16-byte MMI compare when both
 * pointers are 16-aligned and n >= 16, an 8-byte word compare when 8-aligned,
 * then a byte loop.  A mismatch returns the unsigned character difference;
 * reaching n bytes returns 0; an equal NUL returns 0.
 *
 * Behaviour derived from the target:
 *   129208  beqz a2               -> n == 0 returns 0 before any load
 *   12921C  or/andi/sltiu/or      -> ((s1|s2)&15) | (n < 16) selects the path
 *   129280  lq/psubw/pcpyud/or    -> first 16-byte compare, n intact
 *   129288  addiu a2,-16          -> n is decremented after the compare
 *   1292B8  sltiu a2,16           -> n < 16 breaks to the byte loop
 *   12931C  ld + bnel             -> 8-byte path
 *   12936C  while (n-- > 0 ...)   -> byte loop, `addiu a2,-1` in the delay slot
 *   1293A4  lbu a3,0(a0)          -> unsigned difference on return
 */
typedef unsigned int size_t;
typedef unsigned int u_long128 __attribute__((mode(TI)));

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

static __inline__ int haszero8(unsigned long x)
{
    return (x - 0x0101010101010101UL) & ~x & 0x8080808080808080UL;
}

int func_00129200(const char *s1, const char *s2, size_t n)
{
    if (n == 0)
        return 0;

    if ((((long)s1 | (long)s2) & 7) == 0) {
        if ((((long)s1 | (long)s2) & 15) == 0 && n >= 16) {
            if (neq16(s1, s2))
                goto bytes;
            n -= 16;
            s1 += 16;
            s2 += 16;
            while (n >= 16) {
                if (haszero16(s1))
                    return 0;
                if (neq16(s1, s2))
                    goto bytes;
                n -= 16;
                s1 += 16;
                s2 += 16;
            }
        } else if (n >= 8) {
            if (*(const unsigned long *)s1 != *(const unsigned long *)s2)
                goto bytes;
            n -= 8;
            s1 += 8;
            s2 += 8;
            while (n >= 8) {
                if (haszero8(*(const unsigned long *)s1))
                    return 0;
                if (*(const unsigned long *)s1 != *(const unsigned long *)s2)
                    goto bytes;
                n -= 8;
                s1 += 8;
                s2 += 8;
            }
        }
    }
bytes:
    while (n != 0) {
        unsigned char a = (unsigned char)*s1;
        unsigned char b = (unsigned char)*s2;

        if (a != b)
            return a - b;
        if (a == 0)
            return 0;
        s1++;
        s2++;
        n--;
    }
    return 0;
}
