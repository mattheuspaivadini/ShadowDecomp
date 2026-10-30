/* GAMECORE.XFF @ 0x00C078 (52 B) - setFrameRateMode
 * Evidence: `jal iosGetTCount`, then the 64-bit result is stored twice
 * (`sd $v0,0(.data+0x600)` and `sd $v0,0(gcGlobalVar)`), then a sibling `j`.
 * The `.data+0x600` address is materialised into `$s0` (`lui`+`addiu`) and its
 * `lui` lands in the call's delay slot, which only happens when the address is
 * taken through a pointer local.
 * UNCONFIRMED: the two field meanings and the callee prototype.
 
 */
long iosGetTCount(void);
extern long D_kernel_data_0600;
struct GcGlobal {
    long frameTCount;
};
extern struct GcGlobal gcGlobalVar;
void func_00C228(void);

void setFrameRateMode(void) {
    long *p = &D_kernel_data_0600;

    *p = iosGetTCount();
    gcGlobalVar.frameTCount = *p;
    func_00C228();
}
