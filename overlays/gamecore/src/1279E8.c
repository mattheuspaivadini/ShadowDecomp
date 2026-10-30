/* GAMECORE.XFF @ 0x1279E8 (40 B) - updateGazeIKWork
 * Evidence: stores $v0, 0x0($v1), $f0, 0xC($v1); loads $v1, 0x110C($a0), $v0, 0x0($a1)
 
 */
typedef unsigned int u_long128 __attribute__((mode(TI)));
void updateGazeIKWork(char *obj, u_long128 *src) {
    char *w = *(char **)(obj + 0x110C);
    if (w != 0) {
        *(u_long128 *)w = *src;
        *(float *)(w + 0xC) = 1.0f;
    }
}
