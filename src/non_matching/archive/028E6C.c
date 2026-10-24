/* ARCHIVED (Session 63, 2026-10-24): codegen-tuned attempt for 028E6C,
 * kept as the matching reference (it is the closest C form: see the STATUS
 * below).  The build now uses src/cod/028E6C.c, an instruction-stream
 * transcription; the readable reconstruction is
 * src/non_matching/equiv/028E6C.c.
 */
/* STATUS (Session 60, 2026-10-23): NON_MATCHING. best score 44 (was asm-permanent; diff lines,
 * 36 positional words) [cc=ee-gcc2.9-990721-as991111 -malign-loops=2].
 * strcmp (KERNEL.XFF symbol), Newlib 1.9.0 string/strcmp.c with a 16-byte MMI equality test
 * (psubw/pcpyud/or) and null test, explicit first tests + goto loops. Prologue, both first
 * tests and the 16-byte loop body match (register pins, volatile MMI asms, an "or" asm on the
 * TImode difference, a memory-clobber fence so the 8-byte path reloads *s1, a laundered 0 so
 * the two `return 0` blocks are not cross-jumped).
 * BLOCKER: the image's 16-byte loop ends `beql a5,zero,L8EE4` with the loop-top `pnor` in its
 * delay slot. pnor only exists as inline asm (no cc1 here has TImode logic patterns: `~x` on
 * u_long128 is "unsupported wide integer operation"), and none of the installed cc1s
 * (990721, 991111/-01/a/dtls13010, 2.96) ever puts an asm into a delay slot (checked with a
 * minimal loop whose only slot candidate is the asm). With real loop notes (needed for the
 * likely prediction) loop.c also moves both `return 0` blocks out of line. Remaining after that:
 * the 8-byte loop beq vs beql (prediction), and the byte loop: the image tests *s1 at the
 * bottom and reuses the unsigned *s1 load (lbu in the bnez slot, sll/sra at the top).
 * Tried: do-while/goto/for(;;) loop forms, non-volatile pnor, empty do-while(0) loop notes
 * before the goto labels, asm volatile vs plain, explicit return-0 laundering.
 * The original .s stays in the build (asm/cod/028E6C.s); this C draft is kept for the record. */
typedef unsigned int u_long128 __attribute__((mode(TI)));

int func_00128E6C(const char *s1, const char *s2)
{
  register long al asm("$8") = (long)s1 | (long)s2;

  if ((al & 7) == 0)
    {
      register long a15 asm("$9") = al & 15;
      register unsigned long ones asm("$7") = 0x0101010101010101;
      register unsigned long hi asm("$6") = 0x8080808080808080;
      register unsigned long b8 asm("$2") = *(unsigned long *)s2;
      if (a15 == 0)
        {
          register u_long128 o asm("$8"), h asm("$10");
          register u_long128 A asm("$3"), B asm("$2"), D asm("$7"), X asm("$2"), Y asm("$3");
          register unsigned long U asm("$6"), R asm("$3"), M asm("$2"), U2 asm("$3"),
                                 R2 asm("$6"), R3 asm("$9");
          A = *(u_long128 *)s1;
          asm volatile("pcpyld %0,%1,%1" : "=r"(o) : "r"(ones));
          B = *(u_long128 *)s2;
          asm volatile("pcpyld %0,%1,%1" : "=r"(h) : "r"(hi));
          asm volatile("psubw %0,%1,%2" : "=r"(D) : "r"(B), "r"(A));
          asm volatile("pcpyud %0,%1,%2" : "=r"(U) : "r"(D), "r"(s1));
          asm volatile("or %0,%1,%2" : "=r"(R) : "r"(U), "r"(D));
          if (R == 0)
            {
              X = *(u_long128 *)s1;
            top16:
                {
                  asm volatile("pnor %0,$0,%1" : "=r"(Y) : "r"(X));
                  asm volatile("psubb %0,%1,%2" : "=r"(X) : "r"(X), "r"(o));
                  asm volatile("pand %0,%1,%2" : "=r"(X) : "r"(X), "r"(Y));
                  asm volatile("pand %0,%1,%2" : "=r"(M) : "r"(X), "r"(h));
                  asm volatile("pcpyud %0,%1,%2" : "=r"(U2) : "r"(M), "r"(s1));
                  R2 = U2 | M;
                  if (R2 != 0)
                    return 0;
                  s1 += 16;
                  s2 += 16;
                  X = *(u_long128 *)s1;
                  Y = *(u_long128 *)s2;
                  asm volatile("psubw %0,%1,%2" : "=r"(D) : "r"(X), "r"(Y));
                  asm volatile("pcpyud %0,%1,%2" : "=r"(U) : "r"(D), "r"(s1));
                  asm volatile("or %0,%1,%2" : "=r"(R3) : "r"(U), "r"(D));
                }
              if (R3 == 0)
                goto top16;
            }
        }
      else
        {
          register unsigned long a8 asm("$3") = *(unsigned long *)s1;
          if (a8 == b8)
            {
              register unsigned long x asm("$2"), n asm("$8"), y asm("$3");
              asm volatile("" : : : "memory");
              x = *(unsigned long *)s1;
            top8:
                {
                  n = ~x;
                  x = x - ones;
                  x &= n;
                  x &= hi;
                  if (x != 0)
                    {
                      int z;
                      asm("" : "=r"(z) : "0"(0));
                      return z;
                    }
                  s1 += 8;
                  s2 += 8;
                  x = *(unsigned long *)s1;
                  y = *(unsigned long *)s2;
                }
              if (y == x)
                goto top8;
            }
        }
    }
  goto test;
top:
  if (*s1 != *s2)
    goto out;
  s1++;
  s2++;
test:
  if (*s1 != '\0')
    goto top;
out:
  return (*(unsigned char *) s1) - (*(unsigned char *) s2);
}
