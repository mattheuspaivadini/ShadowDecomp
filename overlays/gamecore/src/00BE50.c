/* GAMECORE.XFF @ 0x00BE50 (40 B) - PauseGame
 * Evidence: no loads/stores; data gcGlobalVar+0x24630000; calls <.text>
 */
/* variant: struct member */
struct GcGlobal {
    char pad[0x1AC];
    int flags;
};
extern struct GcGlobal gcGlobalVar;
void func_0000BB18(void);

void PauseGame(int mask) {
    gcGlobalVar.flags |= mask;
    func_0000BB18();
}
