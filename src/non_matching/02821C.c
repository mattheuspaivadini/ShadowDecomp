/* STATUS (Session 54, 2026-10-23): NON_MATCHING. best score 23 [cc=ee-gcc2.9-990721-as991111 -malign-loops=2].
 * Formerly classed asm-permanent ("hand-vectorised MMI memcpy"). It is Newlib 1.9.0
 * string/memcpy.c with the 4x-long big block replaced by two 16-byte (TImode lq/sq) copies and
 * 16-byte alignment; no inline asm needed. Toolchain: see src/non_matching/0290C4.c.
 * With -fno-strength-reduce the loop bodies become identical to the image (16 diff lines) but
 * the function is 4 bytes short; without it loop.c turns the pointer bumps into offset givs.
 * Residual: dst0 is copied to t0 at entry in the image (a0 then holds the big-loop flag and
 * the -1 byte-loop bound), ours keeps dst0 in a0; the byte-loop bne slot is a nop in the image
 * (ours fills it and the assembler pads before the branch).
 * Tried: len -= first, save pointer for the return, size_t len, cast-lvalue
 * *((u_long128 *)p)++ copies (worse: offset givs), cc=29 (40), cc=296 (41), other 2.9/2.95 cc1s.
 * The original .s stays in the build (asm/cod/02821C.s); this C
 * draft (Session 54) is kept for the record. */
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
          *(u_long128 *)aligned_dst = *(u_long128 *)aligned_src;
          aligned_dst += 2; aligned_src += 2;
          *(u_long128 *)aligned_dst = *(u_long128 *)aligned_src;
          aligned_dst += 2; aligned_src += 2;
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

  while (len--)
    *dst++ = *src++;

  return dst0;
}
