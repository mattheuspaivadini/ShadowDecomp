/* STATUS (Session 54, 2026-10-23): NON_MATCHING. best score 27 [cc=ee-gcc2.9-990721-as991111].
 * Formerly classed asm-permanent ("hand-vectorised MMI memset"). Newlib 1.9.0 string/memset.c
 * with 16-byte alignment, the byte pattern widened by pcpyh/pcpyld (inline asm) and a 2x
 * 16-byte sq big loop; the byte loop's 0xFFFFFFFF bound (lui/ori pair, emitted twice) is the
 * unsigned size_t n-- compare. Toolchain: see src/non_matching/0290C4.c (here the default loop
 * alignment scores better: with -malign-loops=2 the function is 4 bytes short).
 * Residual: scheduling/registers of the pattern set-up (andi a5 / sltiu a6 / pcpyh before the
 * n >= 32 branch) and the 8-byte loop entry (image: b into the test, sltiu in the slot).
 * Tried: cc=29 (35), cc=296 (size mismatch).
 * The original .s stays in the build (asm/cod/0283D0.s); this C
 * draft (Session 54) is kept for the record. */
typedef unsigned int size_t;
typedef unsigned int u_long128 __attribute__((mode(TI)));

#define LBLOCKSIZE (sizeof(long))
#define UNALIGNED(X)   ((long)X & (sizeof(u_long128) - 1))
#define TOO_SMALL(LEN) ((LEN) < LBLOCKSIZE)

void *func_001283D0(void *m, int c, size_t n)
{
  char *s = (char *) m;
  unsigned long buffer;
  unsigned long *aligned_addr;

  if (!TOO_SMALL (n) && !UNALIGNED (m))
    {
      u_long128 qbuffer;
      aligned_addr = (unsigned long*)m;
      c &= 0xff;
      buffer = c;
      buffer = (buffer << 8) | c;
      asm("pcpyh %0,%1" : "=r"(buffer) : "r"(buffer));
      if (n >= LBLOCKSIZE*4)
        {
          asm("pcpyld %0,%1,%1" : "=r"(qbuffer) : "r"(buffer));
          while (n >= LBLOCKSIZE*4)
            {
              *(u_long128 *)aligned_addr = qbuffer;
              aligned_addr += 2;
              *(u_long128 *)aligned_addr = qbuffer;
              aligned_addr += 2;
              n -= 4*LBLOCKSIZE;
            }
        }

      while (n >= LBLOCKSIZE)
        {
          *aligned_addr++ = buffer;
          n -= LBLOCKSIZE;
        }
      s = (char*)aligned_addr;
    }

  while (n--)
    {
      *s++ = (char)c;
    }

  return m;
}
