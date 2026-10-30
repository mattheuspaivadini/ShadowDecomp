/* GAMECORE.XFF @ 0x00B230 (48 B) - nico_individualClothOverSurfDetectFunc
 * Evidence: frame 0x60 with `$ra` at 0x50, `$a3 = $a1`, `$v0 = *($a0+0xC)`,
 * `$a1 = *($v0+0x10)`, `$a2 = $a1`, `$a0 = $sp` and `jal
 * CheckUnderVariableXZSurface`; the result is returned as `sltiu $v0,$v0,1`
 * (i.e. `result == 0`).
 * UNCONFIRMED: the local buffer size/type, the struct field meanings and the
 * callee prototype.
 
 */
struct ClothOverSurfSrc {
    char pad[0x10];
    int surface;
};

struct ClothOverSurfObj {
    char pad[0xC];
    struct ClothOverSurfSrc *src;
};

int CheckUnderVariableXZSurface(void *out, int a, int b, int c);

int nico_individualClothOverSurfDetectFunc(struct ClothOverSurfObj *obj,
                                          int param) {
    char out[0x50];
    int surface = obj->src->surface;

    return CheckUnderVariableXZSurface(out, surface, surface, param) == 0;
}
