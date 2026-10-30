/* GAMECORE.XFF @ 0x0FDCD8 (60 B) - _compPassagePos
 * Evidence: stores $ra, 0x0($sp); loads $v0, 0xC($a0), $a0, 0x0($a0), $ra, 0x0($sp); calls memcmp; frame
 
 */
/* UNCONFIRMED: +0x0C points at the reference passage position block, +0x00 at
 * the owning passage whose +0x10 holds the 0x0C-byte position to compare.
 */
int memcmp(const void *a, const void *b, unsigned int n);

int _compPassagePos(char *p) {
    char *other = *(char **)(p + 0xC);
    if (other != 0 && memcmp(*(char **)p + 0x10, other, 0xC) != 0)
        return 1;
    return 0;
}
