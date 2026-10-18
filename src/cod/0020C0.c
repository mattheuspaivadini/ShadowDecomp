/* asm/cod/0020C0.s -> InitException.
 * InitException; switch over the EE exception codes (0/8 skipped, 9 = break handler), typed eeRegInfo clear, $sp stored through a register-asm local (Session 23)
 * MATCHED. */
struct RegInfo { int gpr[32][2]; int cop0[32][2]; };
struct ExcEnt { int code; int pad; };
extern struct RegInfo eeRegInfo;
extern struct ExcEnt D_00131D00[];
extern char start[];
int SetDebugHandler(int code, void (*fn)());
void func_001021E0();
void func_00102360();

void InitException(void) {
    int i;
    register int sp asm ("$29");
    for (i = 0; (unsigned int)i < 14; i++) {
        switch (i) {
        case 0:
        case 8:
            break;
        case 9:
            SetDebugHandler(D_00131D00[9].code, func_00102360);
            break;
        default:
            SetDebugHandler(D_00131D00[i].code, func_001021E0);
            break;
        }
    }
    for (i = 63; i >= 0; i--)
        ((int (*)[2])&eeRegInfo)[i][0] = 0;
    eeRegInfo.gpr[29][0] = sp;
    eeRegInfo.gpr[31][0] = (int)start;
    eeRegInfo.cop0[14][0] = (int)start;
}
