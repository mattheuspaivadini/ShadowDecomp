/* strchr (KERNEL.XFF symbol; kept as func_00128CDC, see config/symbol_addrs.txt).
 * Newlib 1.9.0 string/strchr.c shape: 16-byte MMI null + char tests (pcpyh-free mask built
 * as c*0x0101.. with shifts/adds), an 8-byte path, then the byte scan returning
 * (*s == c) ? s : 0 (C movz in the jr slot). Toolchain: 2.9-ee-990721 cc1 + 2.9-ee-991111
 * as, -malign-loops=2.
 * Register-asm pins and volatile MMI asms give the roles and schedule; the image rebuilds the
 * 64-bit constants at the end of the 16-byte body because its vector registers reuse them.
 * asm() fences order the prologue and stop reorg's thread steals at the loop tops; PAD8 (12 empty
 * asms, no code) makes the 8-byte loop too long for jump.c's exit-test duplication; the
 * memory-clobber fences make the tail reload *s as in the image; shifted mask parts are
 * laundered so combine keeps daddu. */
#define PAD8 asm(""); asm(""); asm(""); asm(""); asm(""); asm(""); asm(""); asm(""); asm(""); asm(""); asm(""); asm("");
typedef unsigned int u_long128 __attribute__((mode(TI)));

char *func_00128CDC(const char *s1, int i)
{
  const unsigned char *s = (const unsigned char *) s1;
  register unsigned long v asm("$2");
  register unsigned long r0 asm("$3");
  unsigned long c = (unsigned char) i;

  if (((long)s & 7) == 0)
    {
      register unsigned long sh asm("$3"), m asm("$10"), t asm("$2"), mask asm("$7");
      register unsigned long ones asm("$6"), hi asm("$8");
      register long al asm("$3");
      sh = c << 8;
      asm("" : "=r"(sh) : "0"(sh));
      asm("");
      ones = 0x0101010101010101;
      asm("");
      m = sh + c;
      asm("");
      al = (long)s & 15;
      asm("");
      t = m << 16;
      asm("" : "=r"(t) : "0"(t));
      asm("");
      hi = 0x8080808080808080;
      asm("");
      t = t + m;
      m = t << 32;
      asm("" : "=r"(m) : "0"(m));
      mask = t + m;
      if (al == 0)
        {
          for (;;)
            {
              register u_long128 x asm("$9"), o asm("$10"), y asm("$3"), a asm("$2");
              register u_long128 h asm("$6"), mv asm("$8"), b2 asm("$2"), d asm("$3");
              register unsigned long u asm("$3"), r asm("$3"), u2 asm("$2"), r2 asm("$3");
              asm("");
              x = *(u_long128 *)s;
              asm volatile("pcpyld %0,%1,%1" : "=r"(o) : "r"(ones));
              asm volatile("pnor %0,$0,%1" : "=r"(y) : "r"(x));
              asm volatile("psubb %0,%1,%2" : "=r"(a) : "r"(x), "r"(o));
              asm volatile("pcpyld %0,%1,%1" : "=r"(h) : "r"(hi));
              asm volatile("pand %0,%1,%2" : "=r"(a) : "r"(a), "r"(y));
              asm volatile("pcpyld %0,%1,%1" : "=r"(mv) : "r"(mask));
              asm volatile("pand %0,%1,%2" : "=r"(a) : "r"(a), "r"(h));
              asm volatile("pcpyud %0,%1,%2" : "=r"(u) : "r"(a), "r"(mask));
              asm volatile("or %0,%1,%2" : "=r"(r) : "r"(a), "r"(u));
              if (r != 0)
                break;
              asm volatile("pxor %0,%1,%2" : "=r"(b2) : "r"(x), "r"(mv));
              asm volatile("psubb %0,%1,%2" : "=r"(d) : "r"(b2), "r"(o));
              asm volatile("pnor %0,$0,%1" : "=r"(b2) : "r"(b2));
              hi = 0x8080808080808080;
              asm volatile("pand %0,%1,%2" : "=r"(d) : "r"(d), "r"(b2));
              asm volatile("pand %0,%1,%2" : "=r"(d) : "r"(d), "r"(h));
              ones = 0x0101010101010101;
              asm volatile("pcpyud %0,%1,%2" : "=r"(u2) : "r"(d), "r"(c));
              asm volatile("or %0,%1,%2" : "=r"(r2) : "r"(u2), "r"(d));
              if (r2 != 0)
                break;
              s += 16;
            }
        }
      else
        {
          register unsigned long w asm("$9") = *(unsigned long *)s;
          register unsigned long n1 asm("$3"), d1 asm("$2");
          n1 = ~w;
          d1 = w - ones;
          d1 &= n1;
          d1 &= hi;
          if (d1 == 0)
            {
              register unsigned long q asm("$2"), e1 asm("$3"), n2 asm("$2");
              q = w ^ mask;
              e1 = q - ones;
              n2 = ~q;
              e1 &= n2;
              e1 &= hi;
              if (e1 == 0)
                {
                  register unsigned long o8 asm("$9");
                  asm("" : "=r"(o8) : "0"(ones));
                  s += 8;
                  for (;;)
                    {
                      register unsigned long x8 asm("$6");
                      register unsigned long f1 asm("$2"), g1 asm("$3"), z asm("$2"), g2 asm("$3"), f2 asm("$2");
                      PAD8 
                      x8 = *(unsigned long *)s;
                      f1 = x8 - o8;
                      g1 = ~x8;
                      f1 &= g1;
                      f1 &= hi;
                      if (f1 != 0)
                        goto test;
                      z = x8 ^ mask;
                      g2 = ~z;
                      f2 = z - o8;
                      f2 &= g2;
                      f2 &= hi;
                      if (f2 != 0)
                        break;
                      s += 8;
                    }
                }
            }
        }
    }
  v = *s;
  goto test2;
top:
  asm volatile("" : : : "memory");
  if (v == c)
    goto out;
  s++;
test:
  v = *s;
test2:
  if (v != 0)
    goto top;
  asm volatile("" : : : "memory");
out:
  r0 = *s;
  return (r0 ^ c) == 0 ? (char *) s : 0;
}
