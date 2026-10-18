/* asm/cod/020748.s -> _sceMcpWriteClust.
 * _sceMcpWriteClust; twin of 020708 (Session 23)
 * MATCHED. */
struct R { char pad00[0x2A]; unsigned short w; char rest[0x184 - 0x2C]; };
extern struct R gSceMc2SysInfo[];
int _sceMcCoreWritePage(int a0, int a1, int a2, int a3);

int _sceMcpWriteClust(int index, int a1, int a2, int a3) {
    struct R *p = &gSceMc2SysInfo[index];
    return _sceMcCoreWritePage(index, a1, a2 * p->w, p->w * a3);
}
