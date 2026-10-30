/* GAMECORE.XFF @ 0x121018 (48 B) - pauseEventDemoManger
 * Evidence: stores $v0, 0x0($a1); loads $v0, 0x0($a1); relocs <.data>
 * The address is materialised once in $a1 and the value is stored after the
 * join, so the source keeps a pointer in a local.
 
 */
extern int D_kernel_data_2008;

void pauseEventDemoManger(int mode) {
    int *p = &D_kernel_data_2008;
    int v;
    if (mode == 1)
        v = *p + 1;
    else
        v = *p - 1;
    *p = v;
}
