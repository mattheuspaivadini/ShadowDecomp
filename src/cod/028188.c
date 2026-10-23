/* memcmp (KERNEL.XFF symbol; kept as func_00128188, see config/symbol_addrs.txt).
 * MMI libc routine: 16-byte compare loop on pxor/pcpyud, then Newlib's byte loop.
 * Toolchain: 2.9-ee-990721 cc1 + 2.9-ee-991111 as (tools/cc/make_hybrid_990721.sh),
 * -malign-loops=2 (Session 54).
 * The register-asm locals reproduce the original register roles; the volatile pxor/pcpyud
 * keep sched1 from hoisting `s2 + 16` (so it lands in v0); the movz is inline asm (an asm is
 * never put in a delay slot, so reorg fills the bnezl slot from the s1 fix-up instead); the
 * fix-up block sits inside the for(;;) so loop.c finds no outer barrier to move exit blocks to.
 * pcpyud's rt operand is a don't-care (the upper half of rd is never read). */
typedef unsigned int size_t;
typedef unsigned int u_long128 __attribute__((mode(TI)));

int func_00128188(const void *m1, const void *m2, size_t len)
{
  register unsigned char *s1 asm("$4") = (unsigned char *) m1;
  register unsigned char *s2 asm("$5") = (unsigned char *) m2;
  register size_t n asm("$6") = len;
  register int last asm("$7");
  register unsigned long x asm("$8"), u asm("$10"), r asm("$9");

  if (n >= 16 && !(((long)s1 | (long)s2) & 15))
    {
      for (;;)
        {
          register u_long128 a asm("$3"), b asm("$2");
          unsigned char *p;

          last = n < 32;
          a = *(u_long128 *)s1;
          b = *(u_long128 *)s2;
          s1 += 16;
          asm volatile("pxor %0,%1,%2" : "=r"(x) : "r"(b), "r"(a));
          p = s2 + 16;
          asm volatile("pcpyud %0,%1,%2" : "=r"(u) : "r"(x), "r"(last));
          r = u | x;
          asm("movz %0,%1,%2" : "=r"(s2) : "r"(p), "r"(r), "0"(s2));
          if (r != 0)
            goto fix;
          n -= 16;
          if (!last)
            continue;
          break;
        fix:
          s1 -= 16;
          break;
        }
    }

  while (n--)
    {
      if (*s1 != *s2)
        return *s1 - *s2;
      s1++;
      s2++;
    }
  return 0;
}
