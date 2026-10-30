/* GAMECORE.XFF @ 0x04B090 (56 B) - GetMeshObjInfo
 * Evidence: stores $a3, 0x4($a0), $zero, 0x0($a0)
 */
/* variant a: stores outside the guard, count then zero */
struct MeshObjInfo {
    int f0;
    int count;
};

void GetMeshObjInfo(struct MeshObjInfo *info, int a1, int a2) {
    int n = 1;

    if (a1 < a2) {
        do {
            a2 = a2 - a1 + 2;
            n++;
        } while (a1 < a2);
    }
    info->count = n;
    info->f0 = 0;
}
