/* KERNEL.XFF @ 0x009580 (12 B) - IosGetMergeDataFileName
 * Evidence: `lui $v0,%hi` / `jr $ra` / `addiu $v0,%lo` against .rodata +0xCA0:
 * returns the address of a module string. UNCONFIRMED: the string lives in
 * .rodata and is not referenced by any decoded string xref here.
 */
extern char D_kernel_rodata_CA0[];

void *IosGetMergeDataFileName(void) {
    return D_kernel_rodata_CA0;
}
