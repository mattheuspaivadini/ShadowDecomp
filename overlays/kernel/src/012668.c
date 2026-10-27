/* KERNEL.XFF @ 0x012668 (72 B) - iosReleaseDC
 * Evidence: for a non-NULL dc: _isysDeleteGroup(dc, &.bss+0x1EAC8 (the DC group of iosInitDC), 0) then sibling isysRequestDeleteObj(dc).
 */
extern char D_kernel_bss_1EAC8[];
void _isysDeleteGroup(void *obj, void *group, int flag);
void isysRequestDeleteObj(void *obj);

void iosReleaseDC(void *dc) {
    if (dc != 0) {
        _isysDeleteGroup(dc, D_kernel_bss_1EAC8, 0);
        isysRequestDeleteObj(dc);
    }
}
