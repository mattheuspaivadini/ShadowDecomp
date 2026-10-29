/* KERNEL.XFF @ 0x00AB68 (76 B) - iosLoaderGetFileSize
 * Evidence: searches the 8 8-byte records at .bss+0xDE68 for the first whose id word (+0) equals fd and returns its +4 word, 0 when none matches. Shape from m2c (tools/xff_m2c.py).
 * Lever: register-asm pins on i/q/e/id (cur left free) give the image's a3/a2/v1/v0 roles and the lui $v0 + addiu $a1 pair. UNCONFIRMED: record field names.
 */
struct FileEnt {
    int id;
    int size;
};
extern struct FileEnt D_kernel_bss_DE68[8];

int iosLoaderGetFileSize(int fd) {
    register int i asm("$7") = 0;
    struct FileEnt *cur = D_kernel_bss_DE68;
    register struct FileEnt *q asm("$6") = cur;
    register struct FileEnt *e asm("$3");
    register int id asm("$2");

    do {
        id = cur->id;
        cur++;
        e = q;
        if (id == fd)
            goto found;
        i++;
        q = e + 1;
    } while (i < 8);
    e = 0;
found:
    return e ? e->size : 0;
}
