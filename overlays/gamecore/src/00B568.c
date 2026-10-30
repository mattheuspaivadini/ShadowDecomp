/* GAMECORE.XFF @ 0x00B568 (60 B) - initgcchartest
 * Evidence: tail `j gcCreateScriptObj` with `$a0 = .text+0xACC0`,
 * `$a1 = 0`, `$a2 = gcGlobalVar+0x308` (loaded), `$a3 = 0x10000`, `$t0 = 0`,
 * `$t1 = 1`, `$t2 = .rodata+0x8F0`.
 * UNCONFIRMED: the script callback and its data object.
 
 */
extern char D_kernel_rodata_0000[];
struct GcGlobal {
    char pad[0x308];
    int field308;
};
extern struct GcGlobal gcGlobalVar;
void func_0000ACC0(void);
void gcCreateScriptObj(void *entry, int a1, int a2, int a3, int a4, int a5,
                       void *data);

void initgcchartest(void) {
    gcCreateScriptObj(func_0000ACC0, 0, gcGlobalVar.field308, 0x10000, 0, 1,
                      D_kernel_rodata_0000 + 0x8F0);
}
