/* KERNEL.XFF @ 0x01EB80 (208 B) - iosLoadIopModule
 * Evidence: fd = iosLoaderFOpen(path, 1, 0) (< 0 returns -1); size = iosLoaderGetFileSize(fd); buffer from rootPtn aligned 0x40; iosLoaderFRead; ret = LoaderSysLoadIopModuleFromEEBuffer(name, buf, size, a2, a3); iosFree; iosLoaderFClose; returns ret. UNCONFIRMED: parameter names/types.
 */
extern char rootPtn[];
int iosLoaderFOpen(const char *path, int mode, int arg);
int iosLoaderGetFileSize(int fd);
void *iosMallocAlign(void *ptn, int size, int align);
int iosLoaderFRead(int fd, void *buf, int size);
int LoaderSysLoadIopModuleFromEEBuffer(const char *name, void *buf, int size, int argc, const char *argv);
void iosFree(void *p);
int iosLoaderFClose(int fd);

int iosLoadIopModule(const char *path, const char *name, int argc, const char *argv) {
    int fd;
    int size;
    void *buf;
    int ret;

    fd = iosLoaderFOpen(path, 1, 0);
    if (fd < 0) {
        return -1;
    }
    size = iosLoaderGetFileSize(fd);
    buf = iosMallocAlign(rootPtn, size, 0x40);
    iosLoaderFRead(fd, buf, size);
    ret = LoaderSysLoadIopModuleFromEEBuffer(name, buf, size, argc, argv);
    iosFree(buf);
    iosLoaderFClose(fd);
    return ret;
}
