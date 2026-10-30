/* GAMECORE.XFF @ 0x00E7B0 (60 B) - initVuColiDispWork
 * Evidence: `$v0 = .bss+0x10`, `sw $a0,0x0`, `sw 2,0x4`, `sw $zero,0x1C`, then
 * a tail `j InitCollisionFinder` with `$a0 = $v0+8`, `$a1 = &rootPtn`,
 * `$a2 = 0x400`.
 * UNCONFIRMED: the collision display work layout.
 
 */
extern char D_kernel_bss_0000[];
extern int rootPtn;
void InitCollisionFinder(void *work, void *pattern, int size);

void initVuColiDispWork(int arg) {
    char *work = D_kernel_bss_0000 + 0x10;

    *(int *)(work + 0x0) = arg;
    *(int *)(work + 0x4) = 2;
    *(int *)(work + 0x1C) = 0;
    InitCollisionFinder(work + 8, &rootPtn, 0x400);
}
