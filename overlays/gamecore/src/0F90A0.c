/* GAMECORE.XFF @ 0x0F90A0 (32 B) - chkAttainExecOffsetRadius
 * Evidence: ops ld sd; data ZeroVector+0x0; calls j <.text>; frame
 * UNCONFIRMED: field names/types guessed from offsets
 */
extern char ZeroVector[];
void func_000F3848(int a, int b, int c, char *v, int d);
void chkAttainExecOffsetRadius(int a, int b, int c, int d) {
    func_000F3848(a, b, c, ZeroVector, d);
}
