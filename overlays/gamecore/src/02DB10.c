/* GAMECORE.XFF @ 0x02DB10 (60 B) - CreateStageBoundaryManager
 * Evidence: `$t1 = $a0` (6th arg), tail `j gcCreateScriptObj` with
 * `$a0 = .text+0x2D710`, `$a1 = 0`, `$a2 = &rootPtn`, `$a3 = 0x2000`,
 * `$t0 = 0`, `$t2 = .rodata+0xE60`.
 * UNCONFIRMED: the script entry and its data object.
 
 */
extern char D_kernel_rodata_0000[];
extern int rootPtn;
void func_0002D710(void);
void gcCreateScriptObj(void *entry, int a1, void *a2, int a3, int a4, int a5,
                       void *data);

void CreateStageBoundaryManager(int arg) {
    gcCreateScriptObj(func_0002D710, 0, &rootPtn, 0x2000, 0, arg,
                      D_kernel_rodata_0000 + 0xE60);
}
