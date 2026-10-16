/* STATUS (Session 9, 2026-10-15): NON_MATCHING. best score 80 [cc=29].
 * session9 R2 waveA; residual class not auto-classified
 * The original .s stays in the build (asm/cod/00CB60.s); this C
 * draft (Session 9) is kept for the record. */
struct SemaParam_00CB60 {
    int f00;    /* 0x00 */
    int f04;    /* 0x04 */
    int f08;    /* 0x08 */
    int f0C;    /* 0x0C */
    int f10;    /* 0x10 */
    int f14;    /* 0x14  name pointer */
};

struct Blk64 {
    char b[0x40];
};

struct Req_00CB60 {
    int  handle;      /* 0x000 */
    int  reply;       /* 0x004  pointer to the 4-byte reply */
    int  replysize;   /* 0x008 */
    int  mode;        /* 0x00C */
    struct Blk64 stat;/* 0x010  the caller stat block, 0x40 bytes */
    char name[0x400]; /* 0x050; byte 0x44F is name[0x3FF] */
};

extern int D_00132314 __attribute__((section(".data")));
extern struct Req_00CB60 D_001459C0;
extern char D_001380D0[];
extern int D_00146600[];
extern int D_001470C0[];

int func_0010A798(int a0);
int sceFsInit(void);
int CreateSema(void *param);
int DeleteSema(int sema);
int WaitSema(int sema);
int func_0010A7C8(void);
int func_0010A228(int a0, int a1, int a2, int a3, int a4, int a5, int a6,
                  int a7, int a8, int a9);
int sceSifWriteBackDCache(int a0, int a1);

int sceChstat(unsigned char *path, struct Blk64 *stat, int mode) {
    struct SemaParam_00CB60 buf;
    int reply;
    int i;
    unsigned char c;
    int h;
    int r;
    int v;

    func_0010A798(0xD);
    if (D_00132314 == 0)
        sceFsInit();
    c = path[0];
    i = 0;
    D_001459C0.name[0] = (char)c;
    if (c != 0) {
        do {
            i++;
            if (i >= 0x400)
                break;
            c = path[i];
            D_001459C0.name[i] = (char)c;
        } while (c != 0);
    }
    if (i == 0x400) {
        D_001459C0.name[0x3FF] = 0;
        i = 0x3FF;
    }
    D_001459C0.stat = *stat;
    D_001459C0.mode = mode;
    buf.f04 = 1;
    buf.f14 = (int)D_001380D0;
    buf.f08 = 0;
    h = CreateSema(&buf);
    D_001459C0.reply = (int)&reply;
    D_001459C0.replysize = 4;
    D_001459C0.handle = h;
    sceSifWriteBackDCache((int)&D_001459C0, 0x450);
    r = func_0010A228((int)D_001470C0, 0xD, 0, (int)&D_001459C0, i + 0x51,
                      (int)D_00146600, 4, 0, 0, 0);
    if (r < 0) {
        DeleteSema(h);
        func_0010A7C8();
        return -0xB;
    }
    v = *(int *)((unsigned int)D_00146600 | 0x20000000);
    func_0010A7C8();
    if (v == 0) {
        DeleteSema(h);
        return -0xB;
    }
    WaitSema(h);
    DeleteSema(h);
    return reply;
}
