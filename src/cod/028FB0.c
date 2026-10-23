/* strcpy (KERNEL.XFF symbol; kept as func_00128FB0, see config/symbol_addrs.txt).
 * Newlib 1.9.0 string/strcpy.c with a 16-byte MMI null test and explicit first tests.
 * Toolchain: 2.9-ee-990721 cc1 + 2.9-ee-991111 as, -malign-loops=2.
 * Register-asm pins give the roles (src stays a pseudo so CSE keeps it as the load base);
 * volatile MMI asms and asm() fences fix the schedule and keep the byte loop's bnez slot
 * empty; the 8-byte first test and loop test use different hard registers so cross-jumping
 * does not merge them. pcpyud's rt is a don't-care (the loaded word). */
typedef unsigned int u_long128 __attribute__((mode(TI)));

char *func_00128FB0(char *dst0, const char *src0)
{
  register char *ret asm("$7") = dst0;
  register char *dst asm("$3") = ret;
  const char *src = src0;
  register long al asm("$8") = (long)src | (long)ret;

  if ((al & 7) == 0)
    {
      register long a15 asm("$2") = al & 15;
      register unsigned long ones asm("$9") = 0x0101010101010101;
      register unsigned long hi asm("$4") = 0x8080808080808080;
      register long *aligned_dst asm("$6");
      if (a15 == 0)
        {
          register u_long128 o asm("$10"), h asm("$8"), x asm("$9");
          register u_long128 a asm("$2"), b asm("$3");
          register unsigned long m asm("$2"), u asm("$4"), r asm("$3");
          asm volatile("pcpyld %0,%1,%1" : "=r"(o) : "r"(ones));
          x = *(u_long128 *)src;
          asm volatile("pcpyld %0,%1,%1" : "=r"(h) : "r"(hi));
          asm volatile("psubb %0,%1,%2" : "=r"(a) : "r"(x), "r"(o));
          asm volatile("pnor %0,$0,%1" : "=r"(b) : "r"(x));
          asm volatile("pand %0,%1,%2" : "=r"(a) : "r"(a), "r"(b));
          asm volatile("pand %0,%1,%2" : "=r"(m) : "r"(a), "r"(h));
          asm volatile("pcpyud %0,%1,%2" : "=r"(u) : "r"(m), "r"(x));
          r = m | u;
          aligned_dst = (long *)ret;
          if (r == 0)
            {
              do
                {
                  *(u_long128 *)aligned_dst = x;
                  asm volatile("");
                  src += 16;
                  x = *(u_long128 *)src;
                  asm volatile("psubb %0,%1,%2" : "=r"(a) : "r"(x), "r"(o));
                  asm volatile("pnor %0,$0,%1" : "=r"(b) : "r"(x));
                  asm volatile("pand %0,%1,%2" : "=r"(a) : "r"(a), "r"(b));
                  asm volatile("pand %0,%1,%2" : "=r"(m) : "r"(a), "r"(h));
                  asm volatile("pcpyud %0,%1,%2" : "=r"(u) : "r"(m), "r"(x));
                  r = m | u;
                  aligned_dst += 2;
                }
              while (r == 0);
            }
        }
      else
        {
          register unsigned long w asm("$10") = *(unsigned long *)src;
          register unsigned long d1 asm("$2") = w - ones, n1 asm("$3") = ~w;
          aligned_dst = (long *)ret;
          d1 &= n1;
          d1 &= hi;
          if (d1 == 0)
            {
              register unsigned long n2 asm("$2"), d2 asm("$3"), r8 asm("$3");
              do
                {
                  *aligned_dst = w;
                  src += 8;
                  w = *(unsigned long *)src;
                  n2 = ~w;
                  d2 = w - ones;
                  aligned_dst++;
                  r8 = d2 & n2;
                  r8 &= hi;
                }
              while (r8 == 0);
            }
        }
      dst = (char *)aligned_dst;
    }

  while (({ int r; asm(""); r = (*dst++ = *src++) != 0; asm(""); r; }))
    ;
  asm("");
  return ret;
}
