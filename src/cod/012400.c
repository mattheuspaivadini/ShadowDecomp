/* asm/cod/012400.s -> func_00112400.
 * DECI2 tty event handler (recv/send/done); all Tty fields volatile, param reused as recv count and copy index, send result passed to the error kprintf (Session 34)
 * MATCHED. */
struct Queue {
    int f00;                    /* 0x00 */
    int f04;                    /* 0x04 */
    int f08;                    /* 0x08 */
    char *wp;                   /* 0x0C write pointer */
};

struct Tty {
    volatile int socket;        /* 0x00 DECI2 socket */
    volatile int len;           /* 0x04 packet length */
    volatile int rlen;          /* 0x08 received bytes */
    volatile int busy;          /* 0x0C send in flight */
    char *pkt;                  /* 0x10 send packet */
    char *rbuf;                 /* 0x14 receive packet */
    struct Queue *q;            /* 0x18 */
};

extern char D_00138278[];
extern char D_001382A0[];
extern char D_001382B8[];
extern char D_001382D0[];

int kprintf(const char *fmt, ...);
int sceDeci2ExRecv(int s, void *buf, unsigned short len);
int sceDeci2ExSend(int s, void *buf, unsigned short len);
void func_00112380(struct Queue *q);

void func_00112400(int event, int param, struct Tty *t) {
    unsigned short *hdr;
    int n;

    switch (event) {
    case 1:
    case 2:
        if (param != 0) {
            if ((unsigned int)(t->rlen + param) > 0x140)
                kprintf(D_00138278);
            param = sceDeci2ExRecv(t->socket, t->rbuf + t->rlen, param);
            if (param < 0)
                kprintf(D_001382A0);
            t->rlen += param;
        } else {
            hdr = (unsigned short *)t->rbuf;
            for (param = 12; param < *hdr; param++) {
                *t->q->wp = t->rbuf[param];
                func_00112380(t->q);
            }
            t->rlen = 0;
        }
        break;
    case 3:
        n = sceDeci2ExSend(t->socket, t->pkt, t->len);
        if (n < 0) {
            kprintf(D_001382B8, n);
            t->busy = 0;
        } else {
            t->pkt += n;
            t->len -= n;
        }
        break;
    case 4:
        if (t->len != 0)
            kprintf(D_001382D0, t->len);
        t->busy = 0;
        break;
    }
}
