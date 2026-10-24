/* KERNEL.XFF @ 0x00A030 (12 B) - getModuleSize
 * Evidence: `lw $v1,0x1C($a0)` / `jr $ra` / `lw $v0,0x14($v1)`: loads a pointer
 * at +0x1C from the object, then the word at +0x14 from it. The pointed-to
 * layout is UNCONFIRMED beyond those two offsets, so they stay explicit.
 */
int getModuleSize(unsigned char *module) {
    unsigned char *hdr = *(unsigned char **)(module + 0x1C);
    return *(int *)(hdr + 0x14);
}
