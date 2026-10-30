/* GAMECORE.XFF @ 0x02CE78 (12 B) - getWorldLayoutHead
 * Shape `ret-load` recovered by tools/xff_shapes.py and proved by
 * recompiling it byte-exactly (relocations masked).
 * Evidence: `lui` + `jr $ra` + delay `lw $v0,lo(...)` against .data+0xfbc - returns that object as `int`.
 */
extern int D_kernel_data_0FBC;

int getWorldLayoutHead(void) {
    return D_kernel_data_0FBC;
}
