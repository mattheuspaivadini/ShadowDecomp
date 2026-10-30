/* GAMECORE.XFF @ 0x030C98 (60 B) - CreateBgmThread
 * Evidence: `adpcmScriptTickProc = .text+0x30688`, `memset(.bss+0x4DC8, 0,
 * 0x9C)` with the store in the `jal` delay slot, then `return 0`.
 * UNCONFIRMED: the function pointer's type.
 
 */
extern char D_kernel_bss_0000[];
extern void *adpcmScriptTickProc;
void *memset(void *dst, int c, unsigned int n);
void func_00030688(void);

int CreateBgmThread(void) {
    adpcmScriptTickProc = func_00030688;
    memset(D_kernel_bss_0000 + 0x4DC8, 0, 0x9C);
    return 0;
}
