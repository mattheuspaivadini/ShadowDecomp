/* GAMECORE.XFF @ 0x00C5F0 (60 B) - initgcmain
 * Evidence: tail `j gcCreateScriptObj` with `$a0 = .text+0xC630`,
 * `$a1 = 0`, `$a2 = &rootPtn`, `$a3 = 0x1000`, `$t0 = 0`, `$t1 = 1`,
 * `$t2 = .rodata+0x928`.
 * UNCONFIRMED: the script callback and its data object.
 
 */
extern char D_kernel_rodata_0000[];
extern int rootPtn;
void func_0000C630(void);
void gcCreateScriptObj(void *entry, int a1, void *a2, int a3, int a4, int a5,
                       void *data);

void initgcmain(void) {
    gcCreateScriptObj(func_0000C630, 0, &rootPtn, 0x1000, 0, 1,
                      D_kernel_rodata_0000 + 0x928);
}
