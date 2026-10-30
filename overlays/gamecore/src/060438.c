/* GAMECORE.XFF @ 0x060438 (36 B) - Init_TimeFVECTORInter
 * Evidence: three `lq`/`sq` 128-bit copies: `*$a2` into +0x00, `*$a1` into
 * +0x10, `*$a2` again into +0x20; `swc1 $f13, 0x34` lands between the second
 * and third copy and `swc1 $f12, 0x30` in the return slot, i.e. both float
 * stores are kept at the end of the body.
 * UNCONFIRMED: the argument roles (which vector is the "inter" source) and the
 * struct layout past +0x38.
 
 */
typedef unsigned int u_long128 __attribute__((mode(TI)));

void Init_TimeFVECTORInter(char *p, void *b, void *c, float x, float y) {
    *(u_long128 *)(p + 0x00) = *(u_long128 *)c;
    *(u_long128 *)(p + 0x10) = *(u_long128 *)b;
    *(u_long128 *)(p + 0x20) = *(u_long128 *)c;
    *(float *)(p + 0x30) = x;
    *(float *)(p + 0x34) = y;
}
