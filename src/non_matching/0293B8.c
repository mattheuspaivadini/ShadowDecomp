/* STATUS (Session 62, 2026-10-23): NON_MATCHING (45 diffs, cc=2.9-990721).
 * REA/Ghidra dossier ev_341c6d0bdc72ed984eac8ce6f29c6791330f7d3ba094d5c2057faa3d0c6d3862
 * re-read; the -malign-loops=3 hypothesis (8-byte alignment of L94E8/0x129520/
 * 0x129550, target pad 0x1294E4) was tested and changes nothing (45 at =2 and
 * =3; -malign-jumps=3 regresses to 66). LATENT UB, kept for codegen: copy8's
 * haszero reads o8/h8, which are only assigned on the 8-byte path; on the
 * reload16 path they were never assigned in C. At run time $9/$10 already hold
 * the same constants from the 16-byte path (o/h), so the image's behaviour
 * matches, but the C is undefined.
 * STATUS (Session 60, 2026-10-23): NON_MATCHING. best score 48 (was asm-permanent; diff lines,
 * 46 positional words) [cc=ee-gcc2.9-990721-as991111 -malign-loops=2].
 * strncpy (KERNEL.XFF symbol), Newlib 1.9.0 string/strncpy.c shape with an alignment-dependent
 * block size (movz picks 16 or 8), a 16-byte path whose first null test runs psubb on ~x (as in
 * the image), one 16-byte lq/sq copy, then a second 16-byte test that continues in the 8-byte
 * copy loop (the image's beql jumps into the ld/sd loop with an lq in its slot).
 * Matching: the 16-byte path through the first copy (register pins, volatile MMI asms, an
 * opaque `move` asm for dst0 so CSE keeps the aligned pseudo as the store base), the byte loop
 * and the zero-fill loop (asm() fences + `.word 0` for the short-loop pad, as in memset).
 * Residual: (1) prologue order (move t0,a0 first; sltu into v0 not the blk register);
 * (2) the image predicts the 16->8 continuation and the 8-byte loop-back as likely (beql with the
 * reload stolen into the slot): that needs a NOTE_INSN_LOOP_BEG at the target, but a real loop
 * there brings loop.c/jump.c restructuring; the out-of-line reload blocks used here end up
 * placed after the return; (3) the lone nop before the 8-byte copy label (L94E8 is 8-aligned:
 * probably a label alignment after a deleted jump/barrier).
 * The original .s stays in the build (asm/cod/0293B8.s); this C draft is kept for the record. */
typedef unsigned int size_t;
typedef unsigned int u_long128 __attribute__((mode(TI)));

char *func_001293B8(char *dst0, const char *src0, size_t count)
{
  register char *ret asm("$8");
  char *dst;
  const char *src = src0;
  register long al asm("$7");
  register size_t b16 asm("$10") = 16;
  register size_t blk asm("$9") = 8;
  register unsigned long w asm("$3");
  register unsigned long o8 asm("$9"), h8 asm("$10");
  char *adst;

  asm("move %0,%1" : "=r"(ret) : "r"(dst0));
  dst = dst0;
  al = (long)src | (long)dst0;

  if ((al & 7) == 0)
    {
      register long a15 asm("$2") = al & 15;
      asm("movz %0,%1,%2" : "=r"(blk) : "r"(b16), "r"(a15), "0"(blk));
      if (a15 == 0)
        {
          if (count >= blk)
            {
              register unsigned long ones asm("$7"), hi asm("$7");
              register u_long128 o asm("$9"), h asm("$10"), x asm("$3"), a asm("$2");
              register unsigned long r asm("$3"), u asm("$3");
              ones = 0x0101010101010101;
              x = *(u_long128 *)src;
              asm volatile("pcpyld %0,%1,%1" : "=r"(o) : "r"(ones));
              asm volatile("pnor %0,$0,%1" : "=r"(x) : "r"(x));
              hi = 0x8080808080808080;
              asm volatile("psubb %0,%1,%2" : "=r"(a) : "r"(x), "r"(o));
              asm volatile("pcpyld %0,%1,%1" : "=r"(h) : "r"(hi));
              asm volatile("pand %0,%1,%2" : "=r"(a) : "r"(a), "r"(x));
              asm volatile("pand %0,%1,%2" : "=r"(a) : "r"(a), "r"(h));
              asm volatile("pcpyud %0,%1,%2" : "=r"(u) : "r"(a), "r"(dst));
              asm volatile("or %0,%1,%2" : "=r"(r) : "r"(a), "r"(u));
              adst = ret;
              if (r != 0)
                goto out;
              {
                register u_long128 v asm("$3") = *(u_long128 *)src;
                count -= 16;
                src += 16;
                *(u_long128 *)adst = v;
                adst += 16;
                if (count < 16)
                  goto out;
              }
              {
                register u_long128 y asm("$2"), z asm("$3");
                register unsigned long r2 asm("$2"), u2 asm("$3");
                y = *(u_long128 *)src;
                asm volatile("pnor %0,$0,%1" : "=r"(z) : "r"(y));
                asm volatile("psubb %0,%1,%2" : "=r"(y) : "r"(y), "r"(o));
                asm volatile("pand %0,%1,%2" : "=r"(y) : "r"(y), "r"(z));
                asm volatile("pand %0,%1,%2" : "=r"(y) : "r"(y), "r"(h));
                asm volatile("pcpyud %0,%1,%2" : "=r"(u2) : "r"(y), "r"(dst));
                asm volatile("or %0,%1,%2" : "=r"(r2) : "r"(y), "r"(u2));
                if (r2 == 0)
                  goto reload16;
                dst = adst;
                goto bytes;
              }
            }
        }
      else
        {
          if (count >= blk)
            {
              register unsigned long w1 asm("$3") = *(unsigned long *)src;
              register unsigned long d1 asm("$2"), n1 asm("$3");
              o8 = 0x0101010101010101;
              h8 = 0x8080808080808080;
              d1 = w1 - o8;
              n1 = ~w1;
              d1 &= n1;
              d1 &= h8;
              adst = ret;
              if (d1 != 0)
                goto out;
              w = *(unsigned long *)src;
            copy8:
              count -= 8;
              src += 8;
              *(unsigned long *)adst = w;
              adst += 8;
              if (count < 8)
                goto out;
              {
                register unsigned long y8 asm("$2"), z8 asm("$3");
                y8 = *(unsigned long *)src;
                z8 = ~y8;
                y8 = y8 - o8;
                y8 &= z8;
                y8 &= h8;
                if (y8 == 0)
                  goto reload8;
              }
            out:
              dst = adst;
            }
        }
    }
bytes:
  while (count > 0)
    {
      --count;
      if ((*dst++ = *src++) == '\0')
        break;
    }

  if (count-- > 0)
    do
      {
        asm("");
        *dst++ = '\0';
      }
    while (({ size_t t = count; count--; asm(".word 0"); t != 0; }));
  asm("");

  return ret;

reload16:
  {
    register u_long128 v16 asm("$3") = *(u_long128 *)src;
    asm("" : "=r"(w) : "0"(v16));
    goto copy8;
  }
reload8:
  w = *(unsigned long *)src;
  goto copy8;
}
