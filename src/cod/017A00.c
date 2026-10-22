/* asm/cod/017A00.s -> _sceCdSC.
 * SCE libcdvd _sceCdSC: linear id tests (goto dispatch), default jumps over the 0x8014 body, volatile _sceCd_scmd_semid keeps its load out of the slot (Session 41)
 * MATCHED. */
extern int _sceCd_ncmd_semid[];
extern volatile int _sceCd_scmd_semid[];
extern char _sceCd_ncmdrdata[];
extern char _sceCd_ncmdsdata[];
extern char _sceCd_cd_ncmd[];
extern char _sceCd_scmdrdata[];
extern char _sceCd_scmdsdata[];
extern char _sceCd_cd_scmd[];

/* UNCONFIRMED: the goto dispatch is a structural model; the original tests the ids linearly in
 * this unsorted order with the bodies laid out in reverse, which no 2.9 switch produces. */
int _sceCdSC(int id, int *out) {
    int v;
    if (id == 0x8001) goto l0;
    if (id == 0x8003) goto l1;
    if (id == 0x8002) goto l2;
    if (id == 0x8004) goto l3;
    if (id == 0x8011) goto l4;
    if (id == 0x8013) goto l5;
    if (id == 0x8012) goto l6;
    if (id != 0x8014)
        goto ldef;
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
ldef:
    v = 0;
done:
    *out = v;
    return 1;
}
