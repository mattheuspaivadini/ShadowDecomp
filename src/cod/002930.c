/* asm/cod/002930.s -> func_00102930 @ 0x00102930 (0x30 bytes)
 * Same shape as func_001028F0 but on D_0013BB90 (256-entry int table in .bss,
 * size 0x400, evidence: asm/data/cod/0013A200.bss.s).
 */
extern int D_0013BB90[256];

int func_00102930(int key) {
    int i;

    for (i = 0; i < 256; i++) {
        if (D_0013BB90[i] == key) {
            D_0013BB90[i] = -1;
            return key;
        }
    }
    return -1;
}
