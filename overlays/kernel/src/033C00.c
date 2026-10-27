/* KERNEL.XFF @ 0x033C00 (28 B) - sceGsGetIMR
 * Evidence: SCE libgraph: returns GsGetIMR() (cc=29 SDK compiler).
 */
unsigned long GsGetIMR(void);

unsigned long sceGsGetIMR(void) {
    return GsGetIMR();
}
