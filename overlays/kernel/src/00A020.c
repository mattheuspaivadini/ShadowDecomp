/* KERNEL.XFF @ 0x00A020 (12 B) - GetExecModuleSize
 * Evidence: `lui $v1,%hi` / `jr $ra` / `lw $v0,%lo($v1)` against .data +0x370:
 * returns one int-sized global. UNCONFIRMED name.
 */
extern int D_kernel_000370;

int GetExecModuleSize(void) {
    return D_kernel_000370;
}
