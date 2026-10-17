/* asm/cod/004E98.s -> padSysReadForLoader.
 * boot pad read for the loader; unsigned button bytes (Session 19)
 * MATCHED. */
struct pad_sys {
    char          pad000[0x104];
    unsigned char data[0x18];   /* 0x104: scePad2Read buffer */
    int           port;         /* 0x11C */
};

extern struct pad_sys D_0013D840;
int scePad2Read(int port, unsigned char *data);

int padSysReadForLoader(void) {
    struct pad_sys *p = &D_0013D840;

    if (scePad2Read(p->port, p->data) < 0)
        return 0;
    return ((p->data[0] << 8) | p->data[1]) ^ 0xFFFF;
}
