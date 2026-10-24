/* ARCHIVED (Session 63, 2026-10-24): codegen-tuned attempt for 029200,
 * kept as the matching reference (it is the closest C form: see the STATUS
 * below).  The build now uses src/cod/029200.c, an instruction-stream
 * transcription; the readable reconstruction is
 * src/non_matching/029200.c.
 */
/* STATUS (Session 60, 2026-10-23): NON_MATCHING. best score 60 (was asm-permanent; diff lines
 * with -malign-jumps=3, 82 positional words) [cc=ee-gcc2.9-990721-as991111 -malign-loops=2].
 * strncmp (KERNEL.XFF symbol), Newlib 1.9.0 string/strncmp.c with a 16-byte MMI block
 * (psubw/pcpyud/or equality, psubb/pnor/pand null test) and an 8-byte block, both entered only
 * when (s1|s2)&15 / n allow it; every `return 0` is cross-jumped into the initial n==0 block.
 * The prologue, the first 16-byte test and most of the 16-byte loop body match.
 * Residual: (1) the image computes ((s1|s2)&15)|(n<16) into one register (we get it but the
 * scheduler interleaves the constant differently); (2) the a1/a2 pointer registers: the image
 * keeps them in a3/t0 and bumps them in the delay slots; pinned hard-reg pointers make expand
 * go through a temporary (addiu v1,a3,16; move a3,v1), unpinned ones get t3/a3; (3) the byte
 * loop needs the 8-byte alignment nop after `b` (L9380 follows a barrier: -malign-jumps=3
 * gives it) and the image's rotation.
 * The original .s stays in the build (asm/cod/029200.s); this C draft is kept for the record. */
typedef unsigned int size_t;
typedef unsigned int u_long128 __attribute__((mode(TI)));

int func_00129200(const char *s1, const char *s2, size_t n)
{
  if (n == 0)
    return 0;

  if ((((long)s1 | (long)s2) & 7) == 0)
    {
      register unsigned long ones asm("$9") = 0x0101010101010101;
      register const char *a1 asm("$7"), *a2 asm("$8");
      register long q asm("$2") = ((long)s1 | (long)s2) & 15;
      long lt = n < 16;
      q |= lt;
      if (q == 0)
        {
          register u_long128 o asm("$10"), h asm("$9");
          register unsigned long hi asm("$8");
          register u_long128 A asm("$3"), B asm("$2");
          register unsigned long u asm("$2"), r asm("$3");
          a1 = s1;
          A = *(u_long128 *)s1;
          asm volatile("pcpyld %0,%1,%1" : "=r"(o) : "r"(ones));
          B = *(u_long128 *)s2;
          hi = 0x8080808080808080;
          asm volatile("psubw %0,%1,%2" : "=r"(A) : "r"(A), "r"(B));
          asm volatile("pcpyld %0,%1,%1" : "=r"(h) : "r"(hi));
          asm volatile("pcpyud %0,%1,%2" : "=r"(u) : "r"(A), "r"(s1));
          a2 = s2;
          asm volatile("or %0,%1,%2" : "=r"(r) : "r"(u), "r"(A));
          if (r != 0)
            goto bytes;
          n -= 16;
          for (;;)
            {
              register u_long128 X asm("$2"), Y asm("$3");
              register unsigned long m asm("$3"), u2 asm("$2"), r2 asm("$2"), r3 asm("$2");
              if (n == 0)
                return 0;
              X = *(u_long128 *)a1;
              asm volatile("pnor %0,$0,%1" : "=r"(Y) : "r"(X));
              asm volatile("psubb %0,%1,%2" : "=r"(X) : "r"(X), "r"(o));
              asm volatile("pand %0,%1,%2" : "=r"(X) : "r"(X), "r"(Y));
              asm volatile("pand %0,%1,%2" : "=r"(m) : "r"(X), "r"(h));
              asm volatile("pcpyud %0,%1,%2" : "=r"(u2) : "r"(m), "r"(s1));
              asm volatile("or %0,%1,%2" : "=r"(r2) : "r"(u2), "r"(m));
              a1 += 16;
              if (r2 != 0)
                return 0;
              a2 += 16;
              if (n < 16)
                break;
              Y = *(u_long128 *)a1;
              X = *(u_long128 *)a2;
              asm volatile("psubw %0,%1,%2" : "=r"(Y) : "r"(Y), "r"(X));
              asm volatile("pcpyud %0,%1,%2" : "=r"(u2) : "r"(Y), "r"(s1));
              asm volatile("or %0,%1,%2" : "=r"(r3) : "r"(u2), "r"(Y));
              if (r3 != 0)
                break;
              n -= 16;
            }
          s1 = a1;
          s2 = a2;
        }
      else
        {
          a1 = s1;
          a2 = s2;
          if (n >= 8)
            {
              if (*(unsigned long *)s1 != *(unsigned long *)s2)
                goto bytes;
              n -= 8;
              {
                register unsigned long hi8 asm("$10") = 0x8080808080808080;
                for (;;)
                  {
                    register unsigned long x asm("$2"), y asm("$3");
                    if (n == 0)
                      return 0;
                    x = *(unsigned long *)a1;
                    y = ~x;
                    x = x - ones;
                    x &= y;
                    x &= hi8;
                    a1 += 8;
                    if (x != 0)
                      return 0;
                    a2 += 8;
                    if (n < 8)
                      break;
                    if (*(unsigned long *)a1 != *(unsigned long *)a2)
                      break;
                    n -= 8;
                  }
              }
            }
          s1 = a1;
          s2 = a2;
        }
    }
bytes:
  while (n-- > 0 && *s1 == *s2)
    {
      if (n == 0 || *s1 == '\0')
        return 0;
      s1++;
      s2++;
    }
  return (*(unsigned char *) s1) - (*(unsigned char *) s2);
}
