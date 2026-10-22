/* asm/cod/001EC0.s -> func_00101EC0.
 * exception register dump; switch on an unsigned mode (1/0/2 case tree), epc param reused as the row counter, u_long128 staging global (Session 35)
 * MATCHED. */
typedef unsigned int u_long128 __attribute__((mode(TI)));
struct RegEnt { unsigned int val; char *name; };
struct ExcName { int code; char *name; };
extern struct ExcName D_00131D00[];
extern union { u_long128 q; unsigned int w[4]; } D_0013B780;
extern char D_00136750[];   /* "     %s:%08x %s:%08x %s:%08x %s:%08x \n" */
extern char D_00136778[];   /* "      %s\n\n" */
extern char D_00136788[];   /* "   pc:%08x " */
extern char D_00136798[];   /* "bva:%08x bpa:%08x " */
extern char D_001367B0[];   /* "cause:%08x\n" */
extern char D_001367C0[];   /* "%s=%8.8x_%8.8x_%8.8x_%8.8x\n" */
extern char D_00139FF0[];
void PutString(int color, const char *fmt, ...);

void func_00101EC0(int code, int cause, int epc, int bva, int bpa, struct RegEnt *r, unsigned int mode)
{
    int i;

    switch (mode) {
    case 0:
        PutString(0xFFC04000, D_00136778, D_00131D00[code].name);
        PutString(0x40FFC000, D_00136788, epc);
        PutString(0x40C0FF00, D_00136798, bva, bpa);
        PutString(0xC0C0C000, D_001367B0, cause);
        PutString(0xFFFFFF00, D_00139FF0);
        for (epc = 0; epc < 8; epc++) {
            PutString(0x80A0C000, D_00136750, r[0].name, r[0].val, r[1].name, r[1].val,
                      r[2].name, r[2].val, r[3].name, r[3].val);
            r += 4;
        }
        break;
    case 1:
        for (i = 0; i < 16; i++) {
            D_0013B780.q = r->val;
            PutString(0xFFFFFF00, D_001367C0, r->name, D_0013B780.w[3], D_0013B780.w[2],
                      D_0013B780.w[1], D_0013B780.w[0]);
            r++;
        }
        break;
    case 2:
        r += 16;
        for (i = 0; i < 16; i++) {
            D_0013B780.q = r->val;
            PutString(0xFFFFFF00, D_001367C0, r->name, D_0013B780.w[3], D_0013B780.w[2],
                      D_0013B780.w[1], D_0013B780.w[0]);
            r++;
        }
        break;
    }
}
