/* GAMECORE.XFF @ 0x013D80 (36 B) - checkFadeParam
 * Evidence: `lwc1 $f1, 4($a0)` and `lwc1 $f0, gcGlobalVar+0x168`, then
 * `c.le.s $f0, $f1` + `bc1t` returning 1 (constant in the delay slot), else 0.
 * So the predicate is `gcGlobalVar[0x168] <= param->field_4`.
 * UNCONFIRMED: field meaning (a fade threshold compared against a timer).
 
 */
extern int gcGlobalVar[];

int checkFadeParam(float *param) {
    if (*(float *)((char *)gcGlobalVar + 0x168) <= param[1]) {
        return 1;
    }
    return 0;
}
