/* GAMECORE.XFF @ 0x0313C0 (28 B) - active_demo_end
 * Evidence: a0 = bss+0x4E64, sibling j demoManEnd
 * UNCONFIRMED: none
 */
extern int D_kernel_bss_4E64[];
void demoManEnd(int d);

void active_demo_end(void) {
    demoManEnd(D_kernel_bss_4E64[0]);
}
