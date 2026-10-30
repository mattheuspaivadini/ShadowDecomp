/* GAMECORE.XFF @ 0x02C168 (64 B) - GetStageName
 * Evidence: 0x50 frame with a 0x40-byte scratch block at sp+0, `$s0` at 0x40
 * and `$ra` at 0x48; `sw (gcGlobalVar+0x340), 0x4($sp)` in the `jal` delay
 * slot of `func_02B3C8($sp)`, then `strcpy(dst, $sp)`.
 * UNCONFIRMED: the scratch block's layout and func_02B3C8's role.
 
 */
int func_02B3C8(void *block);
char *strcpy(char *dst, const char *src);
extern char gcGlobalVar[];

void GetStageName(char *dst) {
    int buf[0x10];

    *(void **)(buf + 1) = gcGlobalVar + 0x340;
    func_02B3C8(buf);
    strcpy(dst, (char *)buf);
}
