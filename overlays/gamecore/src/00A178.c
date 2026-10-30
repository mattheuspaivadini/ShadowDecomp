/* GAMECORE.XFF @ 0x00A178 (64 B) - GAMEUTIL_constructor_col_plane_info
 * Evidence: `sw $zero` at +0, +4, +8; `sd $zero, 0x10` (one 64-bit zero);
 * `lq`/`sq` 16-byte copies of YUnitVector to +0x20, ZeroPoint to +0x30 and
 * ZeroPoint again to +0x40; `sw $zero, 0x50` in the `jr` delay slot.
 * The TImode (lq/sq) copy idiom follows the already-matched 009CD0/010968.
 * UNCONFIRMED: the plane-info layout (+0xC and +0x18 untouched) and the
 * `.data` object names.
 
 */
typedef unsigned int u_long128 __attribute__((mode(TI)));

extern u_long128 YUnitVector;
extern u_long128 ZeroPoint;

void GAMEUTIL_constructor_col_plane_info(void *p) {
    *(int *)((char *)p + 0x00) = 0;
    *(int *)((char *)p + 0x04) = 0;
    *(int *)((char *)p + 0x08) = 0;
    *(long long *)((char *)p + 0x10) = 0;
    *(u_long128 *)((char *)p + 0x20) = YUnitVector;
    *(u_long128 *)((char *)p + 0x30) = ZeroPoint;
    *(u_long128 *)((char *)p + 0x40) = ZeroPoint;
    *(int *)((char *)p + 0x50) = 0;
}
