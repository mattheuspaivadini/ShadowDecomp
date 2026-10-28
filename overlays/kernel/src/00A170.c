/* KERNEL.XFF @ 0x00A170 (92 B) - func_00A170 (static, no symbol in the shipped .symtab)
 * Evidence: fd = iosLoaderFOpen(name, 1, 0); iosLoaderFRead(fd, buf, size); returns iosLoaderFClose(fd) (tail call). UNCONFIRMED: name, FOpen third argument; Ghidra FUN_0020a170.
 */
int iosLoaderFOpen(const char *name, int mode, int arg);
int iosLoaderFRead(int fd, void *buf, int size);
int iosLoaderFClose(int fd);

int func_00A170(void *buf, const char *name, int size) {
    int fd = iosLoaderFOpen(name, 1, 0);

    iosLoaderFRead(fd, buf, size);
    return iosLoaderFClose(fd);
}
