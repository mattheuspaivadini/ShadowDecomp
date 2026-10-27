/* KERNEL.XFF @ 0x00AB50 (20 B) - iosLoaderFRead
 * Shape `tail-call` recovered by tools/xff_shapes.py and proved by
 * recompiling it byte-exactly (relocations masked).
 * Evidence: frame whose only work is a single tail `j`.
 */
void iosLoaderFRead(void) {
    LoaderSysFRead();
}
