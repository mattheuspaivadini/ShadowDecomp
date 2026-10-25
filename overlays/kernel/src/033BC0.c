/* KERNEL.XFF @ 0x033BC0 (60 B) - sceGsPutIMR
 * Evidence: SCE libgraph: old = GsGetIMR(); GsPutIMR(imr); return old. The 16-byte register save slots identify the cc=29 (2.9-991111) SDK compiler, as for the boot ELF's SCE libraries.
 */
unsigned long GsGetIMR(void);
unsigned long GsPutIMR(unsigned long imr);

unsigned long sceGsPutIMR(unsigned long imr) {
    unsigned long old = GsGetIMR();

    GsPutIMR(imr);
    return old;
}
