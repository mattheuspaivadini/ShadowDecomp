/* GAMECORE.XFF @ 0x030CD8 (60 B) - CreateWindThread
 * Evidence: tail `j createScriptObj` with `$a0 = .text+0x30D18`, `$a1 = arg0`,
 * `$a2 = arg1`, `$a3 = 0x1000`, `$t0 = 0`, `$t1 = 1`, `$t2 = 0`, `$t3 = 0`.
 * UNCONFIRMED: the script entry.
 
 */
void func_00030D18(void);
void createScriptObj(void *entry, void *a1, void *a2, int a3, int a4, int a5,
                     int a6, int a7);

void CreateWindThread(void *a1, void *a2) {
    createScriptObj(func_00030D18, a1, a2, 0x1000, 0, 1, 0, 0);
}
