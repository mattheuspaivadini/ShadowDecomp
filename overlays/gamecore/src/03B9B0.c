/* GAMECORE.XFF @ 0x03B9B0 (52 B) - nico_IK_TargetFromRoot
 * Evidence: seven words loaded from the object and passed in
 * `$a0..$a3`/`$t0`/`$t1`/`$t2` (offsets 0x8, 0xC, 0x10, 0x4, 0xB4, 0xB8,
 * 0x14) before a sibling `j` to `GetMotionMatrixOfTargetFromRoot`.
 * UNCONFIRMED: the struct field meanings and the callee prototype.
 
 */
struct IkTargetObj {
    char pad4[4];
    int f4;
    int f8;
    int fC;
    int f10;
    int f14;
    char padB4[0x9C];
    int fB4;
    int fB8;
};

void GetMotionMatrixOfTargetFromRoot(int a, int b, int c, int d, int e, int f,
                                     int g);

void nico_IK_TargetFromRoot(struct IkTargetObj *obj) {
    GetMotionMatrixOfTargetFromRoot(obj->f8, obj->fC, obj->f10, obj->f4,
                                    obj->fB4, obj->fB8, obj->f14);
}
