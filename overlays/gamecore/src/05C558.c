/* GAMECORE.XFF @ 0x05C558 (64 B) - SCRFuncHorseEscapeCounterMain
 * Evidence: `$f0 = mtc1 $zero`, `$f1 = lwc1 0x422C($v1)`, `c.lt.s $f0,$f1`
 * with `bc1f` skipping the body, then `lwc1 gcGlobalVar+0x180`, `sub.s` and
 * `swc1` back to +0x422C.
 * UNCONFIRMED: the AI work field at +0x422C and the delta at gcGlobalVar+0x180.
 
 */
void *GetSCRCharaAIWorkPtr(void);
extern char gcGlobalVar[];

void SCRFuncHorseEscapeCounterMain(void) {
    char *work = GetSCRCharaAIWorkPtr();

    if (*(float *)(work + 0x422C) > 0.0f)
        *(float *)(work + 0x422C) -= *(float *)(gcGlobalVar + 0x180);
}
