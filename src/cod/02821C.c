/* memcpy (KERNEL.XFF symbol; kept as func_0012821C, see config/symbol_addrs.txt).
 * Newlib 1.9.0 string/memcpy.c with the big block as two 16-byte (TImode lq/sq) copies and
 * 16-byte alignment. Toolchain: 2.9-ee-990721 cc1 + 2.9-ee-991111 as, -malign-loops=2
 * -fno-strength-reduce (Sessions 54-60).
 * The `$3` pin on the first temporary gives the big loop's registers (Session 56). In the
 * byte loop the empty asm()s stop reorg's slot search (an asm ends it), so the bne slot stays
 * empty as in the image; the -1 bound is laundered through an empty asm so CSE keeps
 * `move a0,v0` instead of re-materialising `li a0,-1`. */
typedef unsigned int size_t;
typedef unsigned int u_long128 __attribute__((mode(TI)));

#define UNALIGNED(X, Y) \
  (((long)X & (sizeof (u_long128) - 1)) | ((long)Y & (sizeof (u_long128) - 1)))
#define BIGBLOCKSIZE    (sizeof (long) << 2)
#define LITTLEBLOCKSIZE (sizeof (long))
#define TOO_SMALL(LEN)  ((LEN) < BIGBLOCKSIZE)

void *func_0012821C(void *dst0, const void *src0, size_t len0)
{
  char *dst = dst0;
  const char *src = src0;
  long *aligned_dst;
  const long *aligned_src;
  int   len =  len0;

  if (!TOO_SMALL(len) && !UNALIGNED (src, dst))
    {
      aligned_dst = (long*)dst;
      aligned_src = (long*)src;

      while (len >= BIGBLOCKSIZE)
        {
          register u_long128 a asm ("$3"), b;
          a = *(u_long128 *)aligned_src;
          aligned_src += 2;
          *(u_long128 *)aligned_dst = a;
          aligned_dst += 2;
          b = *(u_long128 *)aligned_src;
          aligned_src += 2;
          *(u_long128 *)aligned_dst = b;
          aligned_dst += 2;
          len -= BIGBLOCKSIZE;
        }

      while (len >= LITTLEBLOCKSIZE)
        {
          *aligned_dst++ = *aligned_src++;
          len -= LITTLEBLOCKSIZE;
        }

      dst = (char*)aligned_dst;
      src = (char*)aligned_src;
    }

  {
    register int e1 asm("$2"), e2 asm("$4");
    len--;
    e1 = -1;
    if (len != e1)
      {
        asm("" : "=r"(e2) : "0"(e1));
        do
          {
            asm("");
            len--;
            *dst++ = *src++;
            asm("");
          }
        while (len != e2);
      }
  }

  return dst0;
}
