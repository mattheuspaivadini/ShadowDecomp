/* KERNEL.XFF @ 0x02D998 (20 B) - vab_get_splitchunk
 * Evidence: returns vab + 8, or NULL for a NULL vab (if-converted with movz).
 */
char *vab_get_splitchunk(char *vab) {
    if (vab == 0) {
        return 0;
    }
    return vab + 8;
}
