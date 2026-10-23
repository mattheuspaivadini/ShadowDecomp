/* STATUS (Session 56, 2026-10-23): NON_MATCHING. best score 3 [cc=ee-gcc2.9-990721-as991111 -malign-loops=2 -fno-strength-reduce] (was 9).
 * Newlib 1.9.0 string/memcpy.c with the 4x-long big block replaced by two 16-byte (TImode lq/sq)
 * copies and 16-byte alignment; no inline asm. Toolchain: see src/non_matching/0290C4.c.
 * Lever (Session 56): source order load/store/load/store (as Ghidra shows) with the first
 * temporary pinned by `register u_long128 a asm ("$3")`. The big loop and entry are then
 * byte-exact (lq1 in v1, lq2 in v0, loop flag in a0, dst0 copied to t0). Without the pin the
 * two temporaries do not overlap and both take v0 (flag v1, no t0 copy); Session 55's
 * loads-first order got the registers but not the lq/sq order.
 * Residual (3 words, byte loop): the image loads the -1 bound as `move a0,v0` in the beq slot
 * and leaves the loop's bne slot empty (nop after `addiu v1,v1,1`); ours emits `li a0,-1` and
 * 990721's reorg fills the slot with the dst bump (991111 as then pads the short loop with nop).
 * Tried (S56): flag sweep (cse/gcse/loop/sched/regmove/peephole/thread-jumps, -O1/-O3),
 * all 2.9 cc1s, const/non-const src, u_long128 pointers, int/size_t len, temp scope and
 * declaration order (72-variant grid, floor 9 without the pin), register-asm pins on dst,
 * src, len, aligned_dst and the -1 bound, 12 byte-loop forms (!= 0, for, do-while, char temp,
 * named/pinned -1 bound).
 * Tried (S57): pin the -1 sentinel to $v0 in a nested byte-loop scope and compare against it;
 * GCC rematerializes it in earlier loop guards and changes the register allocation throughout.
 * Also tied a fixed $a0 local to the $v0 sentinel through an empty asm output; same early
 * register-allocation changes and no closer output. Both variants were worse than score 3.
 * Tried (S58): volatile empty-asm fences after the byte copy (no operands, memory clobber,
 * and a tied dst operand) prevent the dst bump from filling the bne slot, but make GCC rotate
 * the loop and emit bnel with a load in its slot; register-input forms also change earlier
 * allocations. A do-while form with the fence has the same result. A long -1 sentinel and an
 * int sentinel held through an empty asm both disturb register allocation. The 991111-01 cc1
 * leaves the byte-loop bne slot empty, but moves the 8-byte dst bump before its beqz instead
 * of into the delay slot. No variant improved on the score-3 baseline.
 * Tried (S59): `ee-gcc2.9-991111-01 -fno-schedule-insns` changes register allocation and
 * instruction order across both vector loops; a block-local `long end = -1L` also changes the
 * loop guards and register roles throughout. Neither is viable for the residual.
 * Tried (S55): all 198 dependency-respecting orders of the 8 load/store/bump statements,
 * const-qualified loads, -fargument-noalias(-global), -fstrict-aliasing, K&R definition,
 * wine ee-gcc2.9-991111 (15+), cc=29/dtls13010 (13+).
 * The original .s stays in the build (asm/cod/02821C.s); this C draft is kept for the record. */
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

  while (len--)
    *dst++ = *src++;

  return dst0;
}
