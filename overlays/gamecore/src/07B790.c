/* GAMECORE.XFF @ 0x07B790 (64 B) - torchObjRelease
 * Evidence: `lw 0x150($s0)` null-tested with `$a0 = obj` in the delay slot,
 * `jal isysRequestDeleteObj`, then `sw $zero, 0x150($s0)` outside the guard
 * (the `beqz` target), so the slot is cleared on both paths.
 * UNCONFIRMED: the AI work field at +0x150.
 
 */
void *GetSCRCharaAIWorkPtr(void);
void isysRequestDeleteObj(void *obj);

void torchObjRelease(void) {
    char *work = GetSCRCharaAIWorkPtr();
    void *obj = *(void **)(work + 0x150);

    if (obj != 0)
        isysRequestDeleteObj(obj);
    *(void **)(work + 0x150) = 0;
}
