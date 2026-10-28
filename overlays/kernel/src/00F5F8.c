/* KERNEL.XFF @ 0x00F5F8 (224 B) - GetMirrorQuaternion
 * Evidence: `lq v0,0x0(a1)` + `sq v0,0x0(a0)` copies the whole quad first, then
 * `sltiu a2,7` / `beqz` guards a 7-entry jump table at .rodata+0x10C0 whose
 * targets are the negate sequences (idx0 = x, 1 = y, 2 = z, 3 = x+z, 4 = x+y,
 * 5 = y+z, 6 and out-of-range = x+y+z); each case ends in its own `jr $ra` with
 * the last `swc1` in the delay slot.
 * UNCONFIRMED: enum names; the source order of the two 2-axis cases is taken
 * from the body addresses (x+y body first, x+z second).
 */
typedef unsigned int u_long128 __attribute__((mode(TI)));

void GetMirrorQuaternion(float *q, float *src, int type) {
    *(u_long128 *)q = *(u_long128 *)src;
    switch (type) {
    case 0:
        q[0] = -q[0];
        break;
    case 1:
        q[1] = -q[1];
        break;
    case 2:
        q[2] = -q[2];
        break;
    case 4:
        q[0] = -q[0];
        q[1] = -q[1];
        break;
    case 3:
        q[0] = -q[0];
        q[2] = -q[2];
        break;
    case 5:
        q[1] = -q[1];
        q[2] = -q[2];
        break;
    case 6:
    default:
        q[0] = -q[0];
        q[1] = -q[1];
        q[2] = -q[2];
        break;
    }
}
