/* asm/cod/012C00.s -> sceSifAddCmdHandler.
 * sceSifAddCmdHandler; handler/harg/gp triples, $gp read by a memory-clobbering asm (forces the base reload) (Session 22)
 * MATCHED. */
struct CmdHandler {
    void *handler;      /* 0x00 */
    void *harg;         /* 0x04 */
    void *gp;           /* 0x08 */
};
struct CmdData {
    char pad00[0xC];
    struct CmdHandler *sys;     /* 0x0C */
    int nsys;                   /* 0x10 */
    struct CmdHandler *usr;     /* 0x14 */
};
extern struct CmdData D_0014B358;

void sceSifAddCmdHandler(int pos, void *handler, void *harg) {
    void *gp;
    unsigned int id;

    if (pos < 0) {
        id = pos & 0x7FFFFFFF;
        D_0014B358.sys[id].handler = handler;
        D_0014B358.sys[id].harg = harg;
        __asm__ volatile ("move %0, $gp" : "=r"(gp) : : "memory");
        D_0014B358.sys[id].gp = gp;
    } else {
        D_0014B358.usr[pos].handler = handler;
        D_0014B358.usr[pos].harg = harg;
        __asm__ volatile ("move %0, $gp" : "=r"(gp) : : "memory");
        D_0014B358.usr[pos].gp = gp;
    }
}
