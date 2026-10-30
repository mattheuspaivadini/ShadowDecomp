/* GAMECORE.XFF @ 0x0FDC20 (32 B) - _resetBaseMoveWork
 * Evidence: ops ld sd sw; calls j <.text>; frame
 * UNCONFIRMED: field names/types guessed from offsets
 */
#define F(p, T, o) (*(T *)((char *)(p) + (o)))
void func_000FE5E0(char *p);
void _resetBaseMoveWork(int a, char *p) {
    F(p, int, 4) = 0;
    F(p, int, 0x24) = 0;
    func_000FE5E0(p);
}
