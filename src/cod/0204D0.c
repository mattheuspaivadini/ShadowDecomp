/* asm/cod/0204D0.s -> _sceMcpReadSysInfo.
 * Struct assignment of the 0x184-byte sys-info page (int-aligned block move; memcpy gives the unaligned lwl/lwr tail) (Session 28).
 * MATCHED. */
struct Mc2SysInfo {
    int data[0x184 / 4];
};

extern struct Mc2SysInfo D_001634C0;
extern struct Mc2SysInfo gSceMc2SysInfo[];

int _sceMcCoreReadPage2(int port, void *buf, int page, int count, int unk);

int _sceMcpReadSysInfo(int port) {
    if (_sceMcCoreReadPage2(port, &D_001634C0, 0, 1, 0) == 0) {
        return 0;
    }
    gSceMc2SysInfo[port] = D_001634C0;
    return 1;
}
