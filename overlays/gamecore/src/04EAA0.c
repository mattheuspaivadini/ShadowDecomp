/* GAMECORE.XFF @ 0x04EAA0 (60 B) - StartFilmBurn
 * Evidence: tail `j gcCreateScriptObj` with `$a0 = .text+0x4DD60`, `$a1 = 0`,
 * `$a2 = &rootPtn`, `$a3 = 0x2000`, `$t0 = 0`, `$t1 = 8`,
 * `$t2 = .rodata+0x12E0`.
 * UNCONFIRMED: the script entry and its data object.
 
 */
extern char D_kernel_rodata_0000[];
extern int rootPtn;
void func_0004DD60(void);
void gcCreateScriptObj(void *entry, int a1, void *a2, int a3, int a4, int a5,
                       void *data);

void StartFilmBurn(void) {
    gcCreateScriptObj(func_0004DD60, 0, &rootPtn, 0x2000, 0, 8,
                      D_kernel_rodata_0000 + 0x12E0);
}
