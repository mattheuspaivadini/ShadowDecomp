/* GAMECORE.XFF @ 0x04B030 (40 B) - AI_GetDeathTentWorkSize
 * Evidence: `lw +0x1C` (count), `lw +0x14` (n) `sll 5` (n * 32) + 0x429, and
 * `slt $a1, $a1, $v1` + `bnez`: when the argument is NOT below the count the
 * `+0x4C` field is added on top.
 * UNCONFIRMED: the work-struct fields and the unit sizes.
 
 */
int AI_GetDeathTentWorkSize(char *work, int index) {
    int size = (*(int *)(work + 0x14) << 5) + 0x429;

    if (!(index < *(int *)(work + 0x1C))) {
        size += *(int *)(work + 0x4C);
    }
    return size;
}
