/* C equivalent of func_001293B8 (0293B8, 444 B @ 0x001293B8) -- strncpy.
 *
 * Reconstructed from asm/cod/0293B8.s and the REA/Ghidra Emotion Engine
 * dossier ev_341c6d0bdc72ed984eac8ce6f29c6791330f7d3ba094d5c2057faa3d0c6d3862,
 * cross-checked with 028E6C/029200 (same MMI block helpers) and the matched
 * 0290C4.  Readable reconstruction: NOT byte-exact (28-45 diff instructions in
 * the block-entry predicates and the predicted 16->8 continuation), not part
 * of the build.  The codegen-tuned near-miss is src/non_matching/archive/0293B8.c.
 *
 * Newlib's strncpy with an alignment-dependent fast path: the block size is 16
 * when src|dst is 16-aligned, 8 when only 8-aligned.  Each block is tested for
 * a NUL before it is copied; the byte loop copies the terminating NUL and the
 * remainder is zero-filled.
 *
 * Behaviour derived from the target:
 *   1293C8  or/andi 7             -> unaligned source/destination skips the fast path
 *   1293D4  movz a5,a6,v0         -> blk = 16 or 8 depending on the &15 test
 *   129408  pcpyld/pnor/psubb/... -> NUL test of the first block
 *   129444  sq + addiu a2,-16     -> 16-byte copy while count >= 16
 *   1294E8  addiu a2,-8 / ld/sd   -> 8-byte copy loop
 *   129520  lbu/sb + sll/sra      -> byte loop with the NUL test
 *   129544  if (count-- > 0)      -> zero fill
 *   129568  move v0,t0            -> returns the original destination
 */
typedef unsigned int size_t;
typedef unsigned int u_long128 __attribute__((mode(TI)));

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

char *func_001293B8(char *dst0, const char *src, size_t count)
{
    char *dst = dst0;

    if ((((long)src | (long)dst) & 7) == 0) {
        if ((((long)src | (long)dst) & 15) == 0) {
            while (count >= 16) {
                if (haszero16(src))
                    break;
                *(u_long128 *)dst = *(const u_long128 *)src;
                dst += 16;
                src += 16;
                count -= 16;
            }
        }
        while (count >= 8) {
            if (haszero8(*(const unsigned long *)src))
                break;
            *(unsigned long *)dst = *(const unsigned long *)src;
            dst += 8;
            src += 8;
            count -= 8;
        }
    }

    while (count != 0) {
        count--;
        if ((*dst++ = *src++) == '\0')
            break;
    }
    while (count != 0) {
        count--;
        *dst++ = '\0';
    }
    return dst0;
}
