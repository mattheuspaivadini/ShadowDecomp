/* KERNEL.XFF @ 0x0158B0 (108 B) - iosResetGraph
 * Evidence: four short arguments (sll/sra 16); for a non-zero first argument only GS CSR = 0x100; otherwise CSR = 0x200 and sibling sceGsResetGraph(0, inter & 1, omode, ffmode & 1).
 */
void sceGsResetGraph(short mode, short inter, short omode, short ffmode);

void iosResetGraph(short mode, short inter, short omode, short ffmode) {
    if (mode != 0) {
        *(volatile unsigned long *)0x12001000 = 0x100;
        return;
    }
    *(volatile unsigned long *)0x12001000 = 0x200;
    sceGsResetGraph(0, inter & 1, omode, ffmode & 1);
}
