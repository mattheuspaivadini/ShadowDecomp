/* MANAGER.XFF @ 0x085980 (20 B) - GetSkeletonFocusNodeDirect
 * Evidence: `beqz $a0` to the `jr` (delay slot sets $v0 = -1), fall-through
 * `lw $v0,0x8($a0)`: null-safe accessor returning -1 for a null node.
 */
int GetSkeletonFocusNodeDirect(unsigned char *node) {
    if (node == 0)
        return -1;
    return *(int *)(node + 0x8);
}
