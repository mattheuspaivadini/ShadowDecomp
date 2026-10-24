/* KERNEL.XFF @ 0x01DB08 (8 B) - isysGetSubThreadWorkSize
 * Evidence: `jr $ra` with `addiu $v0,$a0,0x33` in the delay slot: the requested
 * size plus the 0x33-byte control block.
 */
int isysGetSubThreadWorkSize(int size) {
    return size + 0x33;
}
