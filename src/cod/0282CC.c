/* memmove (KERNEL.XFF symbol; kept as func_001282CC, see config/symbol_addrs.txt).
 * Newlib 1.9.0 string/memmove.c with memcpy's 16-byte lq/sq big block (src/cod/02821C.c).
 * Toolchain: 2.9-ee-990721 cc1 + 2.9-ee-991111 as, -malign-loops=2 -fno-strength-reduce.
 * Same byte-loop levers as memcpy (asm() reorg stoppers, laundered -1 bound); the `$5`/`$7`
 * pins give src and src + len the image's registers, and the asm() after the backward loop
 * keeps reorg from stealing the return-value move into its bne slot. */
typedef unsigned int size_t;
typedef unsigned int u_long128 __attribute__((mode(TI)));

#define UNALIGNED(X, Y) \
  (((long)X & (sizeof (u_long128) - 1)) | ((long)Y & (sizeof (u_long128) - 1)))
#define BIGBLOCKSIZE    (sizeof (long) << 2)
#define LITTLEBLOCKSIZE (sizeof (long))
#define TOO_SMALL(LEN)  ((LEN) < BIGBLOCKSIZE)

void *func_001282CC(void *dst_void, const void *src_void, size_t length)
{
  char *dst = dst_void;
  register const char *src asm("$5") = src_void;
  long *aligned_dst;
  const long *aligned_src;
  int   len =  length;
  register const char *end asm("$7");

  if (src < dst && dst < (end = src + len))
    {
      register int e1 asm("$2"), e2 asm("$4");
      src = end;
      dst += len;
      len--;
      e1 = -1;
      if (len != e1)
        {
          asm("" : "=r"(e2) : "0"(e1));
          do
            {
              asm("");
              len--;
              *--dst = *--src;
              asm("");
            }
          while (len != e2);
          asm("");
          return dst_void;
        }
    }
  else
    {
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
    }
  return dst_void;
}
