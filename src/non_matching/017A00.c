/* STATUS (Session 23, 2026-10-18): NON_MATCHING. best score 11 [cc=29] (was 36).
 * The original tests the ids linearly in an unsorted order (8001 8003 8002 8004 8011 8013 8012 8014)
 * with the bodies laid out in reverse after the tests. A switch never gives that with any 2.9 build
 * (dense range -> jump table; sparse -> sorted balanced tree, probe build/s23/probe/sw.c), and an
 * if/else chain gives bne-over-body. This goto dispatch reproduces the layout; it is a structural
 * model (UNCONFIRMED: the real source shape is unknown). Residuals: 0x8011 stores *out itself and
 * skips the shared store; 0x8014 is the fall-through with default as bnel (v0 = 0).
 * The original .s stays in the build (asm/cod/017A00.s). */
extern int _sceCd_ncmd_semid[];
extern int _sceCd_scmd_semid[];
extern char _sceCd_ncmdrdata[];
extern char _sceCd_ncmdsdata[];
extern char _sceCd_cd_ncmd[];
extern char _sceCd_scmdrdata[];
extern char _sceCd_scmdsdata[];
extern char _sceCd_cd_scmd[];

int _sceCdSC(int id, int *out) {
    int v;
    if (id == 0x8001) goto l0;
    if (id == 0x8003) goto l1;
    if (id == 0x8002) goto l2;
    if (id == 0x8004) goto l3;
    if (id == 0x8011) goto l4;
    if (id == 0x8013) goto l5;
    if (id == 0x8012) goto l6;
    if (id == 0x8014) goto l7;
    v = 0;
    goto done;
l7:
    v = (int)_sceCd_cd_scmd;
    goto done;
l6:
    v = (int)_sceCd_scmdsdata;
    goto done;
l5:
    v = (int)_sceCd_scmdrdata;
    goto done;
l4:
    v = _sceCd_scmd_semid[0];
    goto done;
l3:
    v = (int)_sceCd_cd_ncmd;
    goto done;
l2:
    v = (int)_sceCd_ncmdsdata;
    goto done;
l1:
    v = (int)_sceCd_ncmdrdata;
    goto done;
l0:
    v = _sceCd_ncmd_semid[0];
    goto done;
done:
    *out = v;
    return 1;
}
