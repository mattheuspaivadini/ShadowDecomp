/* asm/cod/021EF8.s -> _sceMcCoreCreateSocket.
 * _sceMcCoreCreateSocket; request block padded to its real size (0x70 frame), fields copied in order, per-statement record indexing (Session 23)
 * MATCHED. */
struct S021EF8_SUB {          /* 10-byte block copied from D_00138DC0 */
    unsigned short w0;        /* 0x00 */
    unsigned short w2;        /* 0x02 */
    unsigned short w4;        /* 0x04 */
    unsigned short w6;        /* 0x06 */
    unsigned short w8;        /* 0x08 */
};

struct S021EF8_REQ {          /* the stack request block */
    int f00;                  /* 0x00 */
    int f04;                  /* 0x04 */
    int f08;                  /* 0x08 */
    int f0C;                  /* 0x0C */
    int f10;                  /* 0x10 */
    struct S021EF8_SUB sub;   /* 0x14 */
    char pad1E[0x28 - 0x1E];
};

struct R021EF8 {              /* 0x24-byte D_00163CC8 record */
    int  field0;              /* 0x00 */
    int  field4;              /* 0x04 socket */
    int  field8;              /* 0x08 */
    int  fieldC;              /* 0x0C */
    int  field10;             /* 0x10 */
    char pad14[8];
    int  field1C;             /* 0x1C */
    int  field20;             /* 0x20 */
};

extern struct S021EF8_SUB D_00138DC0;   /* lui/%lo source block */
extern int D_00165DC0[];                /* .bss 0x00165DC0, 0x80 bytes */
extern struct R021EF8 D_00163CC8[];     /* .bss 0x00163CC8, 0x24-byte records */

int func_00121EC0(void);
int func_001283D0(void *dst, int value, int size);
int sceDbcCreateSocket(int *a0, int a1, int a2);

int _sceMcCoreCreateSocket(int *a0) {
    struct S021EF8_REQ req;
    int i;
    int s;

    i = func_00121EC0();
    if (i < 0)
        return -1;
    req.f00 = a0[0];
    req.f08 = a0[1];
    req.f0C = a0[2];
    req.f10 = a0[3];
    req.sub = D_00138DC0;
    req.f04 = 2;
    req.f00 |= 1;
    func_001283D0((int)D_00165DC0, 0, 0x100);
    s = sceDbcCreateSocket((int *)&req, (int)D_00165DC0, (int)D_00165DC0 + 0x80);
    D_00163CC8[i].field4 = s;
    if (s < 0)
        return -1;
    D_00163CC8[i].field0 = 1;
    D_00163CC8[i].field1C = 0;
    D_00163CC8[i].field20 = 0;
    D_00163CC8[i].field8 = 0x200;
    D_00163CC8[i].fieldC = 0x10;
    D_00163CC8[i].field10 = 0x4000;
    return i;
}
