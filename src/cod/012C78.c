/* asm/cod/012C78.s -> sceSifRemoveCmdHandler.
 * SCE sifcmd: typed 12-byte handler tables (Session 19)
 * MATCHED. */
struct cmd_handler {
    void *func;     /* 0x00 */
    void *data;     /* 0x04 */
    void *gp;       /* 0x08 */
};

extern struct cmd_handler *D_0014B364 __attribute__((section(".data")));  /* system handlers */
extern struct cmd_handler *D_0014B36C __attribute__((section(".data")));  /* user handlers */

void sceSifRemoveCmdHandler(unsigned int cid) {
    if (cid & 0x80000000)
        D_0014B364[cid & 0x7FFFFFFF].func = 0;
    else
        D_0014B36C[cid].func = 0;
}
