/* asm/cod/020708.s -> _sceMcpReadClust.
 * _sceMcpReadClust; record pointer + dtls13010 -g0 (Session 23)
 * MATCHED. */
struct R { char pad00[0x2A]; unsigned short w; char rest[0x184 - 0x2C]; };
extern struct R gSceMc2SysInfo[];
int _sceMcCoreReadPage(int a0, int a1, int a2, int a3);

int _sceMcpReadClust(int index, int a1, int a2, int a3) {
    struct R *p = &gSceMc2SysInfo[index];
    return _sceMcCoreReadPage(index, a1, a2 * p->w, p->w * a3);
}
