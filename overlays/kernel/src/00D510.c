/* KERNEL.XFF @ 0x00D510 (88 B) - iosMulMvec
 * Evidence: both 128-bit operands are copied to stack slots (sd pairs at
 * sp+0/+8 and sp+0x10/+0x18) and reloaded with `lq`; the image then runs the
 * MMI chain pmultw / qfsrv / qfsrv / pmultw / pmthi / pmtlo / pmfhl.lw - the
 * 128-bit product built from two 16-bit-lane multiplies - and stores it with
 * `sq`. Same idiom as the matched neighbour 00D410 iosAddMvec. The window
 * temporaries sit in $8..$11 (t0..t3) with the result in $2, which only
 * reproduces when they are spelled as fixed registers in the template plus
 * clobbers: named output operands give a different allocation.
 * UNCONFIRMED: parameter names/types beyond the 128-bit MMI data.
 */
/* KERNEL.XFF @ 0x00D510 (88 B) - iosMulMvec
 * Evidence: both 128-bit operands are copied into stack slots (sd pairs at
 * sp+0/+8 and sp+0x10/+0x18), reloaded with `lq` and fed to the MMI chain
 * pmultw/qfsrv/qfsrv/pmultw/pmthi/pmtlo/pmfhl.lw, then stored with `sq` - the
 * 128-bit product built from two 16-bit-lane multiplies. Same idiom as the
 * matched neighbour 00D410 iosAddMvec. The window temporaries sit in $8..$11
 * with the result in $2, which only reproduces when they are spelled as fixed
 * registers in the asm template + clobbers (named operands change allocation).
 * UNCONFIRMED: parameter names/types beyond the 128-bit MMI data.
 */
typedef unsigned int u_long128 __attribute__((mode(TI)));
typedef union { long long l[2]; u_long128 q; } MV;

void iosMulMvec(u_long128 *d, MV *a, MV *b) {
    MV x = *a;
    MV y = *b;
    u_long128 r;

    __asm__ __volatile__("pmultw $8, %1, %2\n\t"
                         "mtsab $0, 4\n\t"
                         "qfsrv $9, %1, %2\n\t"
                         "qfsrv $10, %2, %1\n\t"
                         "pmultw $11, $9, $10\n\t"
                         "pmthi $11\n\t"
                         "pmtlo $8\n\t"
                         "pmfhl.lw %0"
                         : "=r"(r)
                         : "r"(x.q), "r"(y.q)
                         : "$8", "$9", "$10", "$11");
    *d = r;
}
