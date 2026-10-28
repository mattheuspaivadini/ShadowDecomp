/* KERNEL.XFF @ 0x00AAD8 (116 B) - iosLoaderFClose   [MATCH: -G0]
 * Evidence: ret = LoaderSysFClose(fd) is kept in $a3 and returned on every
 * path.  The image searches the 8 8-byte records at .bss+0xDE68 for the first
 * whose id word (+0) equals fd, keeping three independent induction values
 * (load cursor $a0, the store cursor $a1 = &D[i] and the counter $a2).  The
 * exhausted path executes a `break` instruction and branches over the store;
 * the found path writes -1 into that record's id and falls into the shared
 * epilogue `daddu v0,a3` -> return value.
 * UNCONFIRMED: record field names, the `break` trap semantics.
 * Lever: the single trailing return with an explicit `goto end;` after the
 * trap (instead of a second `return ret;`) is what merges the two exit paths
 * into the shared `move v0,a3` epilogue and puts `ld s0` back into the b's
 * delay slot.
 */
struct FileEnt {
    int id;
    int size;
};
extern struct FileEnt D_kernel_bss_DE68[8];
extern int LoaderSysFClose(int fd);

int iosLoaderFClose(int fd) {
    int ret = LoaderSysFClose(fd);
    int i;

    for (i = 0; i < 8; i++) {
        if (D_kernel_bss_DE68[i].id == fd)
            goto found;
    }
    __asm__ __volatile__("break 0");
    goto end;
found:
    D_kernel_bss_DE68[i].id = -1;
end:
    return ret;
}
