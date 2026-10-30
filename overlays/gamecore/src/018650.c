/* GAMECORE.XFF @ 0x018650 (12 B) - gameflowGetJumpSekiban
 * Shape `ret-load` recovered by tools/xff_shapes.py and proved by
 * recompiling it byte-exactly (relocations masked).
 * Evidence: `lui` + `jr $ra` + delay `lw $v0,lo(...)` against .data+0x7d0 - returns that object as `int`.
 */
extern int D_kernel_data_07D0;

int gameflowGetJumpSekiban(void) {
    return D_kernel_data_07D0;
}
