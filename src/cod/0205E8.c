/* asm/cod/0205E8.s -> _sceMcpWriteSysInfo.
 * Struct assignment into the page buffer after the 0xFF fill (counterpart of 0204D0) (Session 28).
 * MATCHED. */
struct Mc2SysInfo {
    int data[0x184 / 4];
};

extern struct Mc2SysInfo D_001634C0;
extern struct Mc2SysInfo gSceMc2SysInfo[];

void *func_001283D0(void *dst, int c, unsigned int size);
int _sceMcCoreWritePage(int port, void *buf, int page, int count);

int _sceMcpWriteSysInfo(int port) {
    func_001283D0(&D_001634C0, 0xFF, 0x800);
    D_001634C0 = gSceMc2SysInfo[port];
    return _sceMcCoreWritePage(port, &D_001634C0, 0, 1) != 0;
}
