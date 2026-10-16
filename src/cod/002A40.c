/* asm/cod/002A40.s -> func_00102A40 @ 0x00102A40 (0x3C bytes)
 * Same shape as func_00102A00 but on D_0013B790 (256-entry int table in .bss).
 */
extern int D_0013B790[256];

void LoaderSysInitExternalThreadList(void) {
    int value = -1;
    int i;

    for (i = 255; i >= 0; i--)
        D_0013B790[i] = value;
}
