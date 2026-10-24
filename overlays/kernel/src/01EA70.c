/* KERNEL.XFF @ 0x01EA70 (12 B) - soundGetRevMode
 * Shape `ret-load` recovered by tools/xff_shapes.py and proved by
 * recompiling it byte-exactly (relocations masked).
 * Evidence: `lui` + `jr $ra` + delay `lw $v0,lo(...)` against .data+0x0 - returns that object as `int`.
 */
extern int sg2NicoReverbMode;

int soundGetRevMode(void) {
    return sg2NicoReverbMode;
}
