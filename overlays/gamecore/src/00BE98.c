/* GAMECORE.XFF @ 0x00BE98 (28 B) - ChangeGameTimeScale
 * Evidence: frame, HI16/LO16 pair against `gcGlobalVar` + 0x260 (an `sw` of the
 * argument), then a sibling `j` to the static function at .text+0xBB18 with the
 * argument still live. UNCONFIRMED: callee name (unnamed static) and the
 * `gcGlobalVar` field name.
 */
extern int gcGlobalVar;
int func_0000BB18(int value);

void ChangeGameTimeScale(int value) {
    *(int *)((unsigned char *)&gcGlobalVar + 0x260) = value;
    func_0000BB18(value);
}
