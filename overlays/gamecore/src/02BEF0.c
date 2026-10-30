/* GAMECORE.XFF @ 0x02BEF0 (44 B) - gcGetNbStages
 * Evidence: `lw $a0, 0(DldSysUndefSymbol)` (a pointer variable), `xor` against
 * the address of `SH_StageDataDEFAULT` + `movz $v1, $zero, $a0` (the select
 * idiom for `p = (x != y) ? SH_StageDataDEFAULT : 0`), then a null test and
 * `lw 0xC($v1)`.
 * UNCONFIRMED: why the stage count is read from the default block and the
 * meaning of the DldSysUndefSymbol comparison.
 
 */
extern void *DldSysUndefSymbol;
extern char SH_StageDataDEFAULT[];

int gcGetNbStages(void) {
    char *stages = DldSysUndefSymbol == SH_StageDataDEFAULT
                       ? 0
                       : SH_StageDataDEFAULT;

    return stages != 0 ? *(int *)(stages + 0xC) : 0;
}
