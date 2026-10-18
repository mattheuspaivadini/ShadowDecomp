/* asm/cod/009C58.s -> sceSifRegisterRpc.
 * sceSifRegisterRpc; field types (int / void pointer / SD pointer) drive the TBAA deps that order the queue-link load (Session 22)
 * MATCHED. */
typedef struct SD {
    int sid;
    void * func;
    void * buff;
    int size;
    void * cfunc;
    void * cbuff;
    char pad18[0x20];
    struct SD * link;
    struct SD * next;
    void * base;
} SD;
/* SifRpcDataQueue_t */
typedef struct QD { int thread_id; int active; struct SD * link; } QD;
int DIntr(void);
void EIntr(void);
void sceSifRegisterRpc(SD *sd, int sid, void * func, void * buff, void * cfunc, void * cbuff, QD *qd) {
    SD *server;
    DIntr();
    sd->next = 0;
    sd->link = 0;
    sd->sid = sid;
    sd->func = func;
    sd->buff = buff;
    sd->cfunc = cfunc;
    sd->cbuff = cbuff;
    sd->base = (void *)qd;
    if (qd->link == 0) {
        qd->link = (struct SD *)sd;
    } else {
        server = (SD *)qd->link;
        while (server->link != 0)
            server = (SD *)server->link;
        server->link = (struct SD *)sd;
    }
    EIntr();
}
