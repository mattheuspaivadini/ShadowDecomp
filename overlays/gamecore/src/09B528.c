/* GAMECORE.XFF @ 0x09B528 (64 B) - AI_CheckDamage_SoundBow
 * Evidence: stores $ra, 0x0($sp); loads $a0, 0x0($v0), $v1, 0x60($v0), $ra, 0x0($sp); calls GetDamageClass; frame
 * The `&&` chain is what makes the image keep a real `bnel` instead of folding
 * the equality tests into `xor`+`sltiu`.
 
 */
char *GetDamageClass(int obj);

int AI_CheckDamage_SoundBow(void *unused, int obj) {
    char *d = GetDamageClass(obj);
    if (d != 0 && *(int *)d == 3 && *(int *)(d + 0x60) == *(int *)d)
        return 1;
    return 0;
}
