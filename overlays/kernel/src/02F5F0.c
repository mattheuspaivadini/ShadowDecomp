/* KERNEL.XFF @ 0x02F5F0 (20 B) - Sg2ExPcmOutputSetVol
 * Shape `tail-call` recovered by tools/xff_shapes.py and proved by
 * recompiling it byte-exactly (relocations masked).
 * Evidence: frame whose only work is a single tail `j`.
 */
void Sg2ExPcmOutputSetVol(void) {
    Sg2StPcmSetVolume();
}
