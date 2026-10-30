/* GAMECORE.XFF @ 0x043900 (40 B) - SCRDeleteAllActiveScriptAnimationObj
 * Evidence: `jal allArrowRelease`, `jal DeleteAllActiveScriptAnimationObj`,
 * then `$v0 = 0` before the return.
 * UNCONFIRMED: the callee prototypes.
 
 */
void allArrowRelease(void);
void DeleteAllActiveScriptAnimationObj(void);

int SCRDeleteAllActiveScriptAnimationObj(void) {
    allArrowRelease();
    DeleteAllActiveScriptAnimationObj();
    return 0;
}
