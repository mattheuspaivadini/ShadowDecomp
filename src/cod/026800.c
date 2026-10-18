/* asm/cod/026800.s -> func_00126800.
 * DWARF location-op decoder (DW_OP_reg/breg/regx/bregx/deref/plus_uconst); unsigned op switch with ranges, noreturn abort keeps p out of a saved register (Session 23)
 * MATCHED. */
struct Loc { char pad00[8]; long f08; long offset; char pad18[0x3F8 - 0x18]; unsigned short reg; char pad3FA[0x477 - 0x3FA]; unsigned char deref; };
unsigned char *func_00125998(unsigned char *p, int *val);
unsigned char *func_001259E0(unsigned char *p, int *val);
void func_00127448(void) __attribute__((noreturn));   /* abort */

unsigned char *func_00126800(unsigned char *p, struct Loc *s) {
    int v;
    unsigned int op = *p++;

    switch (op) {
    case 0x50 ... 0x6F:
        s->reg = op - 0x50;
        break;
    case 0x90:
        p = func_001259E0(p, &v);
        s->reg = v;
    case 0x70 ... 0x8F:
        s->reg = op - 0x70;
        p = func_001259E0(p, &v);
        s->offset = v;
        break;
    case 0x92:
        p = func_001259E0(p, &v);
        s->reg = v;
        p = func_001259E0(p, &v);
        s->offset = v;
        break;
    case 0x06:
        s->deref = 1;
        break;
    case 0x23:
        p = func_00125998(p, &v);
        s->f08 = v;
        break;
    default:
        func_00127448();
    }
    return p;
}
