/* KERNEL.XFF @ 0x033C20 (60 B) - isceGsPutIMR
 * Evidence: SCE libgraph interrupt-context variant: old = iGsGetIMR(); iGsPutIMR(imr); return old (cc=29 SDK compiler).
 */
unsigned long iGsGetIMR(void);
unsigned long iGsPutIMR(unsigned long imr);

unsigned long isceGsPutIMR(unsigned long imr) {
    unsigned long old = iGsGetIMR();

    iGsPutIMR(imr);
    return old;
}
