/* asm/cod/010670.s -> func_00110670 @ 0x00110670 (0x90 bytes, 36 insns)
 *
 * Enable Timer 2 through the func_0010FB20/func_0010FB70 guard pair:
 *
 *   g = func_0010FB20();
 *   mode = T2_MODE;                                  ; lw 0x10001010
 *   if (mode & 0x80) {                               ; bit 7 = the timer's flag
 *       if (g) func_0010FB70();
 *       return 1;                                    ; $v0 = 1 around the call
 *   }
 *   func_00110410((mode & 0xFFFFF3FF) | 0x80);        ; MODE write helper
 *   func_00110780(func_00110C78());                   ; arms the software base
 *   if (g) func_0010FB70();
 *   return 0;
 *
 * `mode` is read once into $v0 and used for both the bit-7 test and the mask
 * (no reload); the `andi $v1,$v0,0x80` + `and` with 0xFFFFF3FF then `ori 0x80`
 * are the exact constant shapes. func_00110410 is the matched `MODE` writer
 * (src/cod/010410.c: tail-calls func_00110390 with 0xB0001010) and
 * func_00110C78 is the 64-bit timer readout (non_matching/010C78.c), so
 * func_00110780 takes a 64-bit value in $a0.
 * MATCH GUESS: cc=29 (the whole func_0010FB20 wrapper family is 2.9) */
#include "symbols.h"

int  func_0010FB20(void);
int  func_0010FB70(void);
void func_00110410(int a0);
unsigned long long func_00110C78(void);
void func_00110780(unsigned long long t);

int func_00110670(void) {
    int g = func_0010FB20();
    unsigned int mode = HWREG(EE_T2_MODE);

    if (mode & 0x80) {
        if (g != 0)
            func_0010FB70();
        return 1;
    }
    func_00110410((mode & 0xFFFFF3FF) | 0x80);
    func_00110780(func_00110C78());
    if (g != 0)
        func_0010FB70();
    return 0;
}
