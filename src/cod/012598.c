/* asm/cod/012598.s -> sceTtyWrite.
 * DECI2 tty write: '\n' -> '\r\n' into the uncached packet, send, poll until done; volatile socket/len/busy, void sceDeci2Poll
 * MATCHED. */
struct Queue;

struct Tty {
    volatile int socket;        /* 0x00 DECI2 socket */
    volatile int len;           /* 0x04 packet length */
    int f08;                    /* 0x08 */
    volatile int busy;          /* 0x0C send in flight */
    char *pkt;                  /* 0x10 uncached send packet */
    int f14;                    /* 0x14 */
    struct Queue *q;            /* 0x18 */
};

extern struct Tty D_0014AFD0;
extern char D_0014B000[];

int DIntr(void);
int EIntr(void);
int sceDeci2ReqSend(int s, char dest);
void sceDeci2Poll(int s);

int sceTtyWrite(const char *buf, int len) {
    int n;
    int i;
    int g;
    char *pkt;
    char *p;

    i = 0;
    n = 0;
    if (D_0014AFD0.busy != 0)
        return -1;
    g = DIntr();
    D_0014AFD0.busy = 1;
    pkt = (char *)((unsigned int)D_0014B000 | 0x20000000);
    D_0014AFD0.pkt = pkt;
    p = pkt + 0xC;
    while (--len != -1) {
        if (*buf == '\n') {
            *p++ = '\r';
            if (++n >= 0x100)
                break;
        }
        *p++ = *buf++;
        n++;
        i++;
        if (n >= 0x100)
            break;
    }
    D_0014AFD0.len = n + 0xC;
    *(unsigned short *)pkt = D_0014AFD0.len;
    if (sceDeci2ReqSend(D_0014AFD0.socket, pkt[7]) < 0) {
        D_0014AFD0.busy = 0;
        if (g != 0)
            EIntr();
        return -1;
    }
    while (D_0014AFD0.busy != 0)
        sceDeci2Poll(D_0014AFD0.socket);
    if (g != 0)
        EIntr();
    return i;
}
