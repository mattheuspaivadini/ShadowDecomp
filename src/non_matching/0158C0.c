/* STATUS (Session 8, 2026-10-14): NON_MATCHING. best score 22 [cc=29].
 * R4 w25a_2: 64-bit mask chain materialisation
 * The original .s stays in the build (asm/cod/0158C0.s); this C
 * draft (Session 8) is kept for the record. */
int sceDbcReceiveData(int a0, int a1, void *a2, int a3);

int sceVibGetProfile(int a0, int a1) {
    unsigned long long v;
    int buf;
    int r;

    v = 0xFFFFC000;
    v = v & 0xFFFFC000;
    v = v | 2;
    v = v & 0xFFFF3FFF;
    v = v | 0x8000;
    v = v & 0xFF00FFFF;
    v = v | 0x30000;
    v = v & 0xFFFFFFFFFF00FFFFULL;
    r = sceDbcReceiveData(a0, (int)(v | 0x1000000), &buf, a1);
    if (r >= 0)
        return buf;
    return r;
}
/* func_001158C0 */
