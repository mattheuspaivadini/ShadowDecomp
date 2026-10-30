/* GAMECORE.XFF @ 0x00BEB8 (28 B) - ChangeGameTimeScaleRatio
 * Evidence: swc1 f12 -> gcGlobalVar+0x19C, sibling j .text+0xBB18
 * UNCONFIRMED: callee unnamed static
 */
extern float gcGlobalVar[];
void func_0000BB18(float r);

void ChangeGameTimeScaleRatio(float r) {
    gcGlobalVar[0x19C / 4] = r;
    func_0000BB18(r);
}
