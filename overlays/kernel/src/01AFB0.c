/* KERNEL.XFF @ 0x01AFB0 (92 B) - isysGetLinkNum
 * Evidence: walks the group list from the head at .bss+0x79180 counting entries and returns 0x36B0 (isysGetLinkMax) minus the count. Group entries are 24-byte records in the .bss+0x27100 pool, linked by the 16-bit index at +0xE (0 = end); see isysGetGroupSrhNext. UNCONFIRMED: layout names.
 */
struct IsysObj {
    char pad[9];
    unsigned char ref;
};
struct GroupEnt {
    struct IsysObj *obj;
    char pad[10];
    unsigned short next;
    char pad2[8];
};
extern struct GroupEnt D_kernel_bss_27100[];
extern struct GroupEnt *D_kernel_bss_79180;

int isysGetLinkNum(void) {
    struct GroupEnt *g = D_kernel_bss_79180;
    int n = 0;

    while (g != 0) {
        n++;
        g = g->next ? &D_kernel_bss_27100[g->next] : 0;
    }
    return 0x36B0 - n;
}
