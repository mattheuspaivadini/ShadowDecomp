/* asm/cod/017588.s -> func_00117588 @ 0x00117588 (0x20 bytes)
 *   jal func_00117288
 *    daddu a2,zero,zero
 * Forwards a0/a1 and zeroes the third argument.
 */
extern int sceCdLayerSearchFile();

int sceCdSearchFile(int a0, int a1) {
    return sceCdLayerSearchFile(a0, a1, 0);
}
