/* GAMECORE.XFF @ 0x02C020 (24 B) - SetupStageManager
 * Evidence: frame, `$a1 = 0` and the first argument untouched, then a sibling
 * `j` to the static function at .text+0x2BA80. UNCONFIRMED: callee name
 * (unnamed static).
 */
int func_0002BA80(int a0, int a1);

void SetupStageManager(int a0) {
    func_0002BA80(a0, 0);
}
