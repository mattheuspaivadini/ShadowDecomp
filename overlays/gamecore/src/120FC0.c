/* GAMECORE.XFF @ 0x120FC0 (64 B) - createScrDemoManager
 * Evidence: stores $ra, 0x0($sp); loads $ra, 0x0($sp); relocs rootPtn, <.text>, <.rodata>; calls j _gcCreateChildScriptObj; frame
 
 */
int _gcCreateChildScriptObj(int, int, int, int, int, int, int, int);
void func_001205B8(void);
extern char rootPtn[];
extern char D_kernel_rodata_56A8[];

/* UNCONFIRMED: the 8 arguments mirror the $a0-$a3/$t0-$t3 loads; rootPtn is an
 * external symbol and .text+0x5B8 is the script-object callback.
 */
void createScrDemoManager(void *parent) {
    _gcCreateChildScriptObj((int)func_001205B8, (int)parent, (int)rootPtn, 0x4000,
                            0, 4, (int)D_kernel_rodata_56A8, (int)parent);
}
