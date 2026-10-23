/* strcat (KERNEL.XFF symbol; kept as func_00128BB0, see config/symbol_addrs.txt).
 * Newlib 1.9.0 string/strcat.c with the MMI strlen scan inlined, then strcpy (func_00128FB0).
 * Toolchain: 2.9-ee-990721 cc1 + 2.9-ee-991111 as, -malign-loops=2.
 * The 128-bit sq/lq saves of s0/ra come from the EE cc1's `register_precision(reg, bits)`
 * function attribute (mips.c save_restore_insns; found by disassembling cc1). This cc1
 * drops the first attribute of the list, hence the repeated s0 entry.
 * Register-asm pins, volatile scan asms and asm() fences reproduce the schedule; the 8-byte
 * word is loaded before the 16/8 split so reorg fills the bnez slot from before. */
typedef unsigned int u_long128 __attribute__((mode(TI)));

char *func_00128FB0(char *dst0, const char *src0);

char *func_00128BB0(char *str, const char *s2)
  __attribute__((register_precision(s0, 128), register_precision(ra, 128),
                 register_precision(s0, 128)));

char *func_00128BB0(char *str, const char *s2)
{
  register char *s1 asm("$4") = str;
  char *s = str;

  if (((long)s & 7) == 0)
    {
      register long al asm("$2") = (long)s & 15;
      register unsigned long ones asm("$3") = 0x0101010101010101;
      register unsigned long hi asm("$4") = 0x8080808080808080;
      register unsigned long w asm("$6") = *(unsigned long *)s;
      register unsigned long *p asm("$6");
      if (al == 0)
        {
          register u_long128 o asm("$7"), h asm("$8");
          register u_long128 v asm("$2"), x asm("$3"), y asm("$2");
          register unsigned long m asm("$3"), u asm("$2"), r asm("$3");
          v = *(u_long128 *)s;
          asm volatile("pcpyld %0,%1,%1" : "=r"(o) : "r"(ones));
          asm volatile("pcpyld %0,%1,%1" : "=r"(h) : "r"(hi));
          asm volatile("psubb %0,%1,%2" : "=r"(x) : "r"(v), "r"(o));
          asm volatile("pnor %0,$0,%1" : "=r"(y) : "r"(v));
          asm volatile("pand %0,%1,%2" : "=r"(x) : "r"(x), "r"(y));
          asm volatile("pand %0,%1,%2" : "=r"(m) : "r"(x), "r"(h));
          asm volatile("pcpyud %0,%1,%2" : "=r"(u) : "r"(m), "r"(m));
          r = u | m;
          s1 = s;
          if (r == 0)
            {
              register u_long128 w asm("$2"), z asm("$3");
              register unsigned long m2 asm("$2"), u2 asm("$3"), r2 asm("$2");
              p = (unsigned long *)(s1 + 16);
              for (;;)
                {
                  w = *(u_long128 *)p;
                  asm volatile("pnor %0,$0,%1" : "=r"(z) : "r"(w));
                  asm volatile("psubb %0,%1,%2" : "=r"(w) : "r"(w), "r"(o));
                  asm volatile("pand %0,%1,%2" : "=r"(w) : "r"(w), "r"(z));
                  asm volatile("pand %0,%1,%2" : "=r"(m2) : "r"(w), "r"(h));
                  asm volatile("pcpyud %0,%1,%2" : "=r"(u2) : "r"(m2), "r"(m2));
                  r2 = m2 | u2;
                  if (r2 != 0)
                    break;
                  p += 2;
                }
              asm("");
              s1 = (char *)p;
            }
        }
      else
        {
          register unsigned long o asm("$7"), h asm("$8");
          register unsigned long d1 asm("$3"), n1 asm("$2");
          asm("" : "=r"(o) : "0"(ones));
          asm("" : "=r"(h) : "0"(hi));
          asm volatile("dsubu %0,%1,%2" : "=r"(d1) : "r"(w), "r"(ones));
          asm volatile("nor %0,$0,%1" : "=r"(n1) : "r"(w));
          asm volatile("and %0,%1,%2" : "=r"(d1) : "r"(d1), "r"(n1));
          asm volatile("and %0,%1,%2" : "=r"(d1) : "r"(d1), "r"(hi));
          s1 = s;
          if (d1 == 0)
            {
              register unsigned long w2 asm("$2"), n2 asm("$3"), r2 asm("$2");
              p = (unsigned long *)(s + 8);
              for (;;)
                {
                  w2 = *p;
                  asm volatile("nor %0,$0,%1" : "=r"(n2) : "r"(w2));
                  asm volatile("dsubu %0,%1,%2" : "=r"(w2) : "r"(w2), "r"(o));
                  asm volatile("and %0,%1,%2" : "=r"(r2) : "r"(w2), "r"(n2));
                  asm volatile("and %0,%1,%2" : "=r"(r2) : "r"(r2), "r"(h));
                  if (r2 != 0)
                    break;
                  p++;
                }
              asm("");
              s1 = (char *)p;
            }
        }
    }
  while (*s1)
    s1++;
  func_00128FB0(s1, s2);
  return s;
}
