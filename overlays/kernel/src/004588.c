/* KERNEL.XFF @ 0x004588 (160 B) - func_004588 (static, no symbol in the shipped .symtab)
 * Evidence: for both 0x28-byte memory-card socket records at .bss+0x92C0 with an open socket (+4 >= 0): sceMc2Sync(0, 0), sceMc2DeleteSocket(sock) (a failure is printed with .rodata+0x718 via LoaderSysPrintf(i, sock, result)), sock = -1; then sceMc2Sync(0, 0) and sceMc2End() as a tail call. UNCONFIRMED: names; Ghidra FUN_00204588.
 */
struct McSock {
    int unk0;
    int sock;
    char pad8[0x28 - 8];
};
extern struct McSock D_kernel_bss_092C0[2];
extern char D_kernel_rodata_0718[];
int sceMc2Sync(int mode, int *cmd);
int sceMc2DeleteSocket(int sock);
int sceMc2End(void);
int LoaderSysPrintf(const char *fmt, ...);

int func_004588(void) {
    struct McSock *s = D_kernel_bss_092C0;
    int i;
    int r;

    for (i = 0; i < 2; i++, s++) {
        if (s->sock >= 0) {
            sceMc2Sync(0, 0);
            r = sceMc2DeleteSocket(s->sock);
            if (r) {
                LoaderSysPrintf(D_kernel_rodata_0718, i, s->sock, r);
            }
            s->sock = -1;
        }
    }
    sceMc2Sync(0, 0);
    return sceMc2End();
}
