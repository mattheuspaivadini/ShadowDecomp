/* GAMECORE.XFF @ 0x0C07C0 (52 B) - startAttackEffect
 * Evidence: build/s79/b/dis_all.txt (authority). Fills the attack-effect work
 * record: state = 1, two 0.5f scale fields, the caller's value and a copy of
 * gcGlobalVar+0x178. Declaring the record as a struct keeps the symbol base in
 * one register and the field offsets as displacements.
 * NOTE: the image emits the stores in the order fC, state, f8, f10, f4; GCC
 * swaps the first and last source store, hence the source order below.
 * UNCONFIRMED: struct/field names.
 
 */
struct AttackEffectWork {
    int   state;  /* 0x0 */
    float f4;     /* 0x4 */
    float f8;     /* 0x8 */
    float fC;     /* 0xC */
    float f10;    /* 0x10 */
};

extern struct AttackEffectWork D_kernel_bss_19208;
extern char gcGlobalVar[];

void startAttackEffect(float v) {
    D_kernel_bss_19208.f4 = 0.5f;
    D_kernel_bss_19208.state = 1;
    D_kernel_bss_19208.f8 = 0.5f;
    D_kernel_bss_19208.f10 = *(float *)(gcGlobalVar + 0x178);
    D_kernel_bss_19208.fC = v;
}
