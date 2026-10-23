/* STATUS (Session 55, 2026-10-23): NON_MATCHING. best score 9 [cc=ee-gcc2.9-990721-as991111 -malign-loops=2 -fno-strength-reduce] (was 23).
 * Newlib 1.9.0 string/memcpy.c with the 4x-long big block replaced by two 16-byte (TImode lq/sq)
 * copies and 16-byte alignment; no inline asm. Toolchain: see src/non_matching/0290C4.c.
 * Lever (Session 55): load both 16-byte words into temporaries before the two stores. The two
 * live TImode values then take v0/v1, local-alloc puts the loop flag in a0, and global-alloc
 * moves dst0 to t0 (the image's `move t0,a0` entry copy). With -fno-strength-reduce the loop
 * pointer bumps stay plain addiu like the image.
 * Residual (9 words, two spots): (1) big loop: the image orders lq1/sq1/lq2/sq2 with lq1 in v1 and
 * lq2 in v0; ours keeps the source order lq1/lq2/sq1/sq2 (v0/v1). sched2 does not move it
 * (-fno-schedule-insns2 is a no-op here). (2) byte loop: the image loads the -1 bound as
 * `move a0,v0` and leaves the bne slot empty; 990721's reorg fills it (991111-01 cc1s leave it
 * empty but miss the 8-byte loop fill the image has).
 * Tried: all 198 dependency-respecting orders of the 8 load/store/bump statements plus len -=
 * (none below 8 diff lines), const-qualified loads, -fargument-noalias(-global),
 * -fstrict-aliasing, K&R definition, casts, save/ret pointers, int len parameter, byte-loop
 * forms (len-- != 0, --len != -1, braces, char temporary, for loop, named -1 bound), wine
 * ee-gcc2.9-991111 (15+), cc=29/dtls13010 (13+).
 * The original .s stays in the build (asm/cod/02821C.s); this C
 * draft (Session 55) is kept for the record. */
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
          u_long128 a, b;
          a = *(u_long128 *)aligned_src;
          aligned_src += 2;
          b = *(u_long128 *)aligned_src;
          aligned_src += 2;
          *(u_long128 *)aligned_dst = a;
          aligned_dst += 2;
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

  while (len--)
    *dst++ = *src++;

  return dst0;
}
