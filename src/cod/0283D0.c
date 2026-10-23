/* memset (KERNEL.XFF symbol; kept as func_001283D0, see config/symbol_addrs.txt).
 * Newlib 1.9.0 string/memset.c with a pcpyh/pcpyld 16-byte fill. Toolchain: 2.9-ee-990721
 * cc1 + 2.9-ee-991111 as, -malign-loops=2 -fno-strength-reduce.
 * Register-asm pins give the image's roles; asm("") fences order the aligned-pointer copy
 * (so reorg puts it in the bnez slot) and stop reorg in the byte loop.
 * UNCONFIRMED: the image pads both short loops with two nops before the branch (R5900
 * short-loop workaround). None of the installed assemblers does this for store-only loops
 * (they also delete explicit `nop`s), so the padding is emitted as `.word 0, 0`. The 8-byte
 * loop is written as goto-into-do-while so the test is not duplicated, as in the image. */
typedef unsigned int size_t;
typedef unsigned int u_long128 __attribute__((mode(TI)));

#define LBLOCKSIZE (sizeof(long))
#define UNALIGNED(X)   ((long)X & (sizeof(u_long128) - 1))
#define TOO_SMALL(LEN) ((LEN) < LBLOCKSIZE)

void *func_001283D0(void *m, int c, size_t n)
{
  char *s = (char *) m;
  unsigned long *aligned_addr;

  if (!TOO_SMALL (n) && !UNALIGNED (m))
    {
      register unsigned long d asm("$9"), buffer asm("$8"), h asm("$3");
      register int big asm("$10");
      aligned_addr = (unsigned long*)m;
      asm("");
      d = c & 0xff;
      big = n < LBLOCKSIZE*4;
      asm("" : "=r"(buffer) : "0"(d));
      {
        register unsigned long t asm("$3") = buffer << 8;
        buffer = t | d;
      }
      asm("pcpyh %0,%1" : "=r"(h) : "r"(buffer));
      if (!big)
        {
          register u_long128 q asm("$8");
          asm("pcpyld %0,%1,%1" : "=r"(q) : "r"(h));
          do
            {
              *(u_long128 *)aligned_addr = q;
              n -= 4*LBLOCKSIZE;
              aligned_addr += 2;
              *(u_long128 *)aligned_addr = q;
              aligned_addr += 2;
            }
          while (n >= LBLOCKSIZE*4);
        }

      {
        register int lt asm("$2");
        goto test;
        do
          {
            *aligned_addr++ = h;
            n -= LBLOCKSIZE;
          test:
            lt = n < LBLOCKSIZE;
            asm(".word 0, 0");
          }
        while (!lt);
      }
      s = (char*)aligned_addr;
    }

  n--;
  if (n != (size_t)-1)
    do
      {
        asm("");
        n--;
        *s++ = (char)c;
        asm(".word 0, 0");
      }
    while (n != (size_t)-1);

  return m;
}
