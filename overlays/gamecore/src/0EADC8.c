/* GAMECORE.XFF @ 0x0EADC8 (52 B) - copy_mode_common_camera_data
 * Evidence: stores $v0, 0x0($a0), $v1, 0x10($a0), $v0, 0x20($a0), $f0, 0x30($a0), $f1, 0x34($a0), $f0, 0x38($a0); loads $v0, 0x0($a1), $v1, 0x10($a1), $v0, 0x20($a1), $f0, 0x30($a1), $f1, 0x34($a1), $f0, 0x38($a1)
 */
/* STATUS: NOT MATCHING, lwc1/swc1 +0x30 hoisted above the lq/sq block (source order preserved in image)
 * Levers tried: struct copy *dst=*src (emits lwl/lwr); 12-byte float struct copy; -fno-schedule-insns; -fno-schedule-insns2; -fno-gcse
 */
/* GAMECORE.XFF @ 0x0EADC8 (52 B) - copy_mode_common_camera_data
 * Evidence: three `lq`/`sq` 16-byte copies then three `lwc1`/`swc1` at +0x30/+0x34/+0x38.
 * UNCONFIRMED: struct field meanings and callee argument/return types
 */
typedef unsigned int u_long128 __attribute__((mode(TI)));

void copy_mode_common_camera_data(char *dst, char *src) {
    *(u_long128 *)(dst + 0x00) = *(u_long128 *)(src + 0x00);
    *(u_long128 *)(dst + 0x10) = *(u_long128 *)(src + 0x10);
    *(u_long128 *)(dst + 0x20) = *(u_long128 *)(src + 0x20);
    *(float *)(dst + 0x30) = *(float *)(src + 0x30);
    *(float *)(dst + 0x34) = *(float *)(src + 0x34);
    *(float *)(dst + 0x38) = *(float *)(src + 0x38);
}
