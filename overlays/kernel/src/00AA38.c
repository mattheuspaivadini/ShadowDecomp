/* KERNEL.XFF @ 0x00AA38 (160 B) - iosLoaderFOpen
 * STATUS: NON-MATCHING (~40/40 words differ, size 148-160 B vs 160). Frame 0x60 needs the stat buffer padded to 0x40 B (size at +8) -> prologue matches.
 * The image's 8-entry scan keeps a walking pointer (a0, post-increment, loaded before the add) plus a lagging &tbl[i] pointer (a1, copy via v1) and an
 * index counter a2; found -> s0 = a1, not found -> s0 = 0 (then stores through NULL: original bug).
 * Tried (all fail, gcc picks a different pointer/ counter allocation): goto-found loop, do/while, ternary `i < 8 ? &tbl[i] : 0`, slot++ in for header,
 * slot++ in body, static inline find() returning &tbl[i] / p++ / break+ternary (the ternary + for(i<8) forms reach the right size 160 B).
 */
extern int LoaderSysFOpen(const char *name, int mode, int flag);
extern int LoaderSysGetstat(const char *name, void *buf);
struct FileEntry { int fd; int size; };
extern struct FileEntry D_kernel_bss_DE68[8];
struct StatBuf { int pad[2]; int size; int pad2[13]; };

int iosLoaderFOpen(const char *name, int mode, int flag)
{

    int fd;
    int i;
    struct FileEntry *slot;
    struct StatBuf st;

    fd = LoaderSysFOpen(name, mode, flag);
    if (fd < 0)
        return fd;
    for (i = 0; i < 8; i++) {
        if (D_kernel_bss_DE68[i].fd == -1)
            goto found;
    }
found:
    slot = &D_kernel_bss_DE68[i];

    slot->fd = fd;
    LoaderSysGetstat(name, &st);
    slot->size = st.size;
    return fd;

}
