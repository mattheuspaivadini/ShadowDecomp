/* GAMECORE.XFF @ 0x03B960 (48 B) - nico_IK_recomputeAll
 * Evidence: six words loaded from the object and passed in
 * `$a0..$a3`/`$t0`/`$t1` (offsets 0x8, 0xC, 0x10, 0x4, 0xB4, 0xB8) before a
 * sibling `j` to `GetMotionMatrix`.
 * UNCONFIRMED: the struct field meanings and the callee prototype.
 
 */
struct IkRecomputeObj {
    char pad4[4];
    int f4;
    int f8;
    int fC;
    int f10;
    char padB4[0xA0];
    int fB4;
    int fB8;
};

void GetMotionMatrix(int a, int b, int c, int d, int e, int f);

void nico_IK_recomputeAll(struct IkRecomputeObj *obj) {
    GetMotionMatrix(obj->f8, obj->fC, obj->f10, obj->f4, obj->fB4, obj->fB8);
}
