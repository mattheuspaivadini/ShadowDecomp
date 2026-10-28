/* KERNEL.XFF @ 0x0009A0 (192 B) - iosAddIntcHandler
 * Evidence: 11-entry 0xC-stride {id, num, handler} table at .data+0x10; the
 * scan tests tab[i].id against the first argument and keeps the byte offset in
 * a second cursor (`addu v0,t0,a1` in the found block), i.e. two subscripts with
 * an `unsigned int` index (`sltiu $v0,$a3,0xB`).  Not found (or handler already
 * set) is a tail call to iosJumpRecoverPoint (.rodata+0x58 / .rodata+0xA0).
 * Found: tab[i].handler = arg2, then AddIntcHandler(tab[i].num, arg2, 0), its
 * result to LoaderSysEntryExternalIntcHandlerList(result, tab[i].num) and
 * EnableIntc(tab[i].num).
 * LEVER: both error paths must be `return iosJumpRecoverPoint(...)` - the emitted
 * `j` (tail jump, `ld ra`/`addiu sp` before it) is what keeps arg2 live in $a1
 * across the second check and keeps the frame at 0x10 with a single saved
 * register; a plain call costs a 0x30 frame with s1-s3 and 20 extra bytes.
 * UNCONFIRMED: table/slot names, the third AddIntcHandler argument.
 */
extern char D_kernel_rodata_58[];
extern char D_kernel_rodata_A0[];
extern void iosJumpRecoverPoint(const char *fmt, ...);
extern int AddIntcHandler(int num, int handler, int arg);
extern void LoaderSysEntryExternalIntcHandlerList(int handler, int num);
extern void EnableIntc(int num);

struct IntcEntry {
    int id;
    int num;
    int handler;
};
extern struct IntcEntry D_kernel_data_10[];

void iosAddIntcHandler(int id, int handler) {
    unsigned int i;
    int h;

    for (i = 0; i < 11; i++) {
        if (D_kernel_data_10[i].id == id)
            goto found;
    }
    return iosJumpRecoverPoint(D_kernel_rodata_58);
found:
    if (D_kernel_data_10[i].handler != 0)
        return iosJumpRecoverPoint(D_kernel_rodata_A0);
    D_kernel_data_10[i].handler = handler;
    h = AddIntcHandler(D_kernel_data_10[i].num, handler, 0);
    LoaderSysEntryExternalIntcHandlerList(h, D_kernel_data_10[i].num);
    EnableIntc(D_kernel_data_10[i].num);
}
