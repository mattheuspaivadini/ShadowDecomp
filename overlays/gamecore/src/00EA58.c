/* GAMECORE.XFF @ 0x00EA58 (48 B) - activeDemoAbort
 * Evidence: `lui`/`addiu` build `.data+0x6D0`, `lw $v1,0xC` is tested for zero
 * and skipped when clear; `$a0 = *($v0+0x8)` then a sibling `j` to the abort
 * routine at 0x00EAF0.
 * UNCONFIRMED: the struct field meanings and the callee prototype.
 
 */
struct ActiveDemoState {
    char pad[8];
    int handle;
    int active;
};

extern struct ActiveDemoState D_kernel_data_06D0;
void func_00EAF0(int handle);

void activeDemoAbort(void) {
    if (D_kernel_data_06D0.active != 0)
        func_00EAF0(D_kernel_data_06D0.handle);
}
