/* GAMECORE.XFF @ 0x041998 (12 B) - menuSelected
 * Shape `ret-load` recovered by tools/xff_shapes.py and proved by
 * recompiling it byte-exactly (relocations masked).
 * Evidence: `lui` + `jr $ra` + delay `lw $v0,lo(...)` against .data+0x10ec - returns that object as `int`.
 */
extern int D_kernel_data_10EC;

int menuSelected(void) {
    return D_kernel_data_10EC;
}
