/* GAMECORE.XFF @ 0x0344D8 (60 B) - allArrowRelease
 * Evidence: `lw .bss+0x62D4` head guard, then a loop calling `.text+0x31790`
 * with `lw 0xC0($a0)` fetched in the `jal` delay slot and `bnez` back.
 * The next link must be loaded before the call so the load lands in the
 * `jal` delay slot and the loop pointer stays in $a0.
 * UNCONFIRMED: the `.bss` list head and the +0xC0 next link.
 
 */
extern char D_kernel_bss_0000[];
void func_031790(void *arrow);

void allArrowRelease(void) {
    void *arrow = *(void **)(D_kernel_bss_0000 + 0x62D4);

    while (arrow != 0) {
        void *next = *(void **)((char *)arrow + 0xC0);

        func_031790(arrow);
        arrow = next;
    }
}
