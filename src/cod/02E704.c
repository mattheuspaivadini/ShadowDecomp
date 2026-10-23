/* memchr: Newlib 1.9.0 string/memchr.c shape with a 16-byte MMI search (pxor against a
 * pcpyh/pcpyld-replicated byte, then the psubb/pnor/pand null test).
 * Toolchain: 2.9-ee-990721 cc1 + 2.9-ee-991111 as, -malign-loops=2.
 * Register-asm pins and volatile MMI asms give the roles and schedule; d is an unsigned long
 * and the shifted copy is laundered through an empty asm so combine keeps `daddu` (it turns a
 * disjoint-bits add into `or`); the asm() fence puts the aligned-pointer copy in the bnez
 * slot. The found-return block sits after `return 0` (goto found), as in the image. */
typedef unsigned int size_t;
typedef unsigned int u_long128 __attribute__((mode(TI)));

void *memchr(const void *src_void, int c, size_t length)
{
  const unsigned char *src = (const unsigned char *) src_void;
  unsigned long d = (unsigned char) c;

  if (length >= 16 && !((long)src & 15))
    {
      register const unsigned char *asrc asm("$7");
      register unsigned long mask asm("$10");
      register unsigned long ones asm("$2");
      register unsigned long hi asm("$3");
      register u_long128 m asm("$9"), h asm("$8"), t asm("$8");
      register unsigned long o64 asm("$4");
      asrc = src;
      asm("");
      {
        register unsigned long sh asm("$3") = (unsigned long)d << 8;
        asm("" : "=r"(sh) : "0"(sh));
        ones = 0x0101010101010101;
        mask = sh + d;
      }
      hi = 0x8080808080808080;
      asm volatile("pcpyh %0,%1" : "=r"(t) : "r"(mask));
      asm volatile("pcpyld %0,%1,%1" : "=r"(m) : "r"(t));
      asm("" : "=r"(o64) : "0"(ones));
      asm volatile("pcpyld %0,%1,%1" : "=r"(h) : "r"(hi));
      do
        {
          register u_long128 x asm("$2"), y asm("$3"), o asm("$10");
          register unsigned long r asm("$2"), u asm("$3");
          x = *(u_long128 *)asrc;
          asm volatile("pxor %0,%1,%2" : "=r"(x) : "r"(x), "r"(m));
          asm volatile("pcpyld %0,%1,%1" : "=r"(o) : "r"(o64));
          asm volatile("pnor %0,$0,%1" : "=r"(y) : "r"(x));
          asm volatile("psubb %0,%1,%2" : "=r"(x) : "r"(x), "r"(o));
          asm volatile("pand %0,%1,%2" : "=r"(x) : "r"(x), "r"(y));
          asm volatile("pand %0,%1,%2" : "=r"(r) : "r"(x), "r"(h));
          asm volatile("pcpyud %0,%1,%2" : "=r"(u) : "r"(r), "r"(m));
          r = r | u;
          if (r != 0)
            break;
          length -= 16;
          asrc += 16;
        }
      while (length >= 16);
      src = asrc;
    }

  while (length--)
    {
      if (*src == d)
        goto found;
      src++;
    }
  return 0;

found:
  return (void *) src;
}
