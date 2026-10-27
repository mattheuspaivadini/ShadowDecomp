/* KERNEL.XFF @ 0x00A728 (84 B) - loadtest
 * Evidence: size = iosLoaderGetFileSizeName(name); when size >= 0 the static loader at .text+0x8B78 gets (name, size, dst); returns its result or 0. UNCONFIRMED: callee prototype.
 */
int iosLoaderGetFileSizeName(const char *name);
int func_008B78(const char *name, int size, void *dst);

int loadtest(const char *name, void *dst) {
    int size = iosLoaderGetFileSizeName(name);
    int ret = 0;

    if (size >= 0) {
        ret = func_008B78(name, size, dst);
    }
    return ret;
}
