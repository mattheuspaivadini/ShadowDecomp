/* KERNEL.XFF @ 0x0105A8 (292 B) - GetEulerYXZFromQuaternionZHalfPI
 * Evidence: `jal func_00DEE8` with `a0 = euler`; then two range tests on
 * euler[2] (kept live in $f2 for the whole body): `c.lt.s f2,f0` (z < 0) with
 * the `-1.5707963f` (0xBFC90FDA) arm using `bc1tl` into the body and the
 * `1.5707963f < z` arm using `bc1fl` to the epilogue - i.e.
 * `if (z < 0) { if (!(z < -pi/2)) return; } else { if (!(pi/2 < z)) return; }`.
 * The three wrap-arounds are written straight on the array fields (no
 * temporaries): `euler[1] = euler[1] +/- 3.1415926f` (0x40490FDA),
 * `euler[0] = +/-3.1415926f - euler[0]` (the 0xC0490FDA literal in the negative
 * arm) and the z arm reuses the live $f2, so each result lands in $f0 (the
 * constant's register) and the store is not sunk into the next branch.
 * Using a local `float z/y/x` instead keeps the result in the loaded register
 * and costs 8 B.
 * UNCONFIRMED: the callee prototype.
 */
void func_00DEE8(float *euler);

void GetEulerYXZFromQuaternionZHalfPI(float *euler) {
    func_00DEE8(euler);
    if (euler[2] < 0.0f) {
        if (!(euler[2] < -1.5707963f))
            return;
    } else {
        if (!(1.5707963f < euler[2]))
            return;
    }
    if (euler[1] < 0.0f)
        euler[1] = euler[1] + 3.1415926f;
    else
        euler[1] = euler[1] - 3.1415926f;
    if (0.0f < euler[0])
        euler[0] = 3.1415926f - euler[0];
    else
        euler[0] = -3.1415926f - euler[0];
    if (0.0f < euler[2])
        euler[2] = euler[2] - 3.1415926f;
    else
        euler[2] = euler[2] + 3.1415926f;
}
