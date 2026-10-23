/* strlen (KERNEL.XFF symbol; kept as func_001290C4, see config/symbol_addrs.txt).
 * Newlib 1.9.0 string/strlen.c with a 16-byte MMI null test (psubb/pnor/pand/pcpyud) and an
 * explicit first test + do-while per block size (Ghidra shows the same shape, Session 54).
 * Toolchain: 2.9-ee-990721 cc1 + 2.9-ee-991111 as, -malign-loops=2.
 * Register-asm pins give the roles; `str` pinned to a0 makes CSE keep the aligned pseudo as
 * the load base (it prefers pseudos over user hard registers); volatile MMI asms fix the
 * schedule. pcpyud's rt is a don't-care (o in the first test, t in the loop). The "0"(m2) tie
 * keeps a0 live on the loop entry so reorg annuls the first exit's slot (bnezl), as in the
 * image. */
typedef unsigned int size_t;
typedef unsigned int u_long128 __attribute__((mode(TI)));

#define UNALIGNED(X) ((long)X & (sizeof (long) - 1))

static __inline__ unsigned long detectnull(unsigned long x)
{
    unsigned long ones = 0x0101010101010101;
    return (x - ones) & ~x & 0x8080808080808080;
}

size_t func_001290C4(const char *str0)
{
    register const char *str asm("$4") = str0;
    register const char *start asm("$7") = str;
    unsigned long *aligned_addr;

    if (!UNALIGNED(str)) {
        register long al asm("$3") = (long)str & 15;
        register unsigned long ones asm("$2") = 0x0101010101010101;
        aligned_addr = (unsigned long *)str;
        if (al == 0) {
            register u_long128 o asm("$8"), h asm("$9");
            register unsigned long t asm("$6");
            register unsigned long hi asm("$4");
            register u_long128 v asm("$3"), x asm("$2"), y asm("$3");
            register unsigned long m asm("$2"), u asm("$3"), m3 asm("$3");
            v = *(u_long128 *)aligned_addr;
            asm volatile("pcpyld %0,%1,%1" : "=r"(o) : "r"(ones));
            hi = 0x8080808080808080;
            asm volatile("psubb %0,%1,%2" : "=r"(x) : "r"(v), "r"(o));
            asm volatile("pnor %0,$0,%1" : "=r"(y) : "r"(v));
            asm volatile("pcpyld %0,%1,%1" : "=r"(h) : "r"(hi));
            asm volatile("pand %0,%1,%2" : "=r"(x) : "r"(x), "r"(y));
            asm volatile("pand %0,%1,%2" : "=r"(m) : "r"(x), "r"(h));
            asm volatile("pcpyud %0,%1,%2" : "=r"(u) : "r"(m), "r"(o));
            t = u | m;
            if (t == 0) {
                do {
                    register u_long128 w asm("$2"), z asm("$3");
                    register unsigned long m2 asm("$4"), u2 asm("$3");
                    aligned_addr += 2;
                    w = *(u_long128 *)aligned_addr;
                    asm volatile("pnor %0,$0,%1" : "=r"(z) : "r"(w));
                    asm volatile("psubb %0,%1,%2" : "=r"(w) : "r"(w), "r"(o));
                    asm volatile("pand %0,%1,%2" : "=r"(w) : "r"(w), "r"(z));
                    asm volatile("pand %0,%1,%2" : "=r"(m2) : "r"(w), "r"(h), "0"(m2));
                    asm volatile("pcpyud %0,%1,%2" : "=r"(u2) : "r"(m2), "r"(t));
                    m3 = u2 | m2;
                } while (m3 == 0);
            }
        } else {
            register unsigned long w asm("$3") = *aligned_addr;
            if (((w - ones) & ~w & 0x8080808080808080) == 0) {
                do
                    aligned_addr++;
                while (!detectnull(*aligned_addr));
            }
        }
        str = (char *)aligned_addr;
    }
    while (*str)
        str++;
    return str - start;
}
