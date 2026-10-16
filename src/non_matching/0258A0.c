/* STATUS (Session 7, 2026-10-14): NON_MATCHING. best score 9 [cc=296, default].
 * part-block decompose + movz select.
 * The original .s stays in the build (asm/cod/0258A0.s); this C
 * draft (subagent-produced, Session 7) is kept for the record. */
/* asm/cod/0258A0.s -> func_001258A0 @ 0x001258A0 (0x54 bytes, 21 insns)
 *
 * Decompose the 64-bit float argument (func_001271B0 writes the 0x20-byte part
 * block at sp+0x00) and forward the four part words to func_001270A8, which
 * packs them into a fresh stack block and hands them to func_00127390:
 *   func_001270A8(pa.type @0x00, pa.sign @0x04, pa.exp @0x08, x)
 * where x is derived from the 64-bit mantissa at 0x10:
 *   dsll   $v1, $v0, 2          ; v1 = mant << 2        (64-bit)
 *   dsra32 $v1, $v1, 0          ; v1 = (mant << 2) >> 32 (arithmetic!)
 *   and    $v0, $v0, 0x3FFFFFFF ; the movz test operand
 *   ori    $a3, $v1, 1          ; the "true" arm
 *   movz   $a3, $v1, $v0        ; a3 = (mant & mask) ? (v1|1) : v1
 * The `dsra32` (arithmetic, not `dsrl`) is what pins the mantissa to a *signed*
 * 64-bit type; the two-shift sequence is load-bearing (GCC cannot fold
 * `(x << 2) >> 32` into `x >> 30` for a signed value).
 *
 * Frame 0x40: the part block at 0x00, the argument home at 0x20 and $ra at
 * 0x30 - the 16-byte-spaced slots of the 2.9 (cc=29) generation.
 * MATCH GUESS: cc=29 */
struct D25768 {
    int type;                       /* 0x00 */
    int sign;                       /* 0x04 */
    int exp;                        /* 0x08 */
    int pad0C;                      /* 0x0C */
    long long mant;                 /* 0x10 (signed: `dsra32`) */
    long long pad18;                /* 0x18 */
};

int __unpack_d(long long *in, struct D25768 *out);
int __make_fp(int a0, int a1, int a2, int a3);

int dptofp(long long a0) {
    struct D25768 pa;
    int v;

    __unpack_d(&a0, &pa);
    v = (int)((pa.mant << 2) >> 32);
    return __make_fp(pa.type, pa.sign, pa.exp,
                         (pa.mant & 0x3FFFFFFF) ? (v | 1) : v);
}
