/* GAMECORE.XFF @ 0x0FDFF0 (48 B) - calcProgRotRatioForMove2
 * Evidence: stores $ra, 0x0($sp); loads $f14, 0x190($v0), $v1, 0x1C($a0), $f15, 0xA8($a0), $a1, 0x0($v1), $f13, 0xA4($a0), $f16, 0x78($a1), $ra, 0x0($sp); relocs gcGlobalVar, gcGlobalVar+0x190; calls j calcProgRotRatio; frame
 
 */
/* UNCONFIRMED: same work layout; gcGlobalVar+0x190 supplies the progress ratio
 * limit.
 */
extern char gcGlobalVar[];

void calcProgRotRatio(float angle, float a, float b, float c, float d);

void calcProgRotRatioForMove2(char *p, float angle) {
    char *work = *(char **)(p + 0x1C);
    char *owner = *(char **)work;
    calcProgRotRatio(angle, *(float *)(p + 0xA4), *(float *)(gcGlobalVar + 0x190),
                     *(float *)(p + 0xA8), *(float *)(owner + 0x78));
}
