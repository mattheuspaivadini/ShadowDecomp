/* GAMECORE.XFF @ 0x0937E8 (56 B) - player_resetSlipEffect
 * Evidence: `$s0 = $a1`, `lw $v0,0x0($s0)`, null-guarded `jal
 * isysRequestDeleteObj` (handle forwarded in `$a0`), then `sw $zero,0x0($s0)`.
 * UNCONFIRMED: the second parameter's role (object handle slot).
 
 */
void isysRequestDeleteObj(void *obj);

void player_resetSlipEffect(void *unused, int *handle) {
    if (*handle != 0) {
        isysRequestDeleteObj((void *)*handle);
        *handle = 0;
    }
}
