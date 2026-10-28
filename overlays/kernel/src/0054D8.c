/* KERNEL.XFF @ 0x0054D8 (484 B) - iosPadTickProc
 * Evidence: two 0x78-byte pad records at .data+0x270 (`lui` + `addiu 0x270`,
 * stride 0x78) walked by one loop (slti 2). Per record: prev = +0 (lw/sw to
 * +4), cur = (lbu +0x104 << 8) | lbu +0x105 of padSysGet(i,0), +0x10 = 0,
 * press = (cur^prev)&cur at +8, release = (cur^prev)&~cur at +0xC, cur at +0.
 * The 16-entry float timer array at +0x14 is retriggered when the *press* bit
 * is set (now + 0.4f, 0x3ECCCCCC) or, for a held button (+0) whose timer is
 * below `now`, reloaded with now + 0.08f (0x3DA3D70A); both OR the bit into
 * the auto-repeat word +0x10. `now` = iosGetSecondFromTCount(
 * iosGetTCountExtension()) is taken before padSysTickProc(). The four status
 * bytes at +0x104..+0x109 are copied to +0x56/+0x57/+0x54/+0x55, the shock list
 * at +0x58 gets Shock_Decode(&list,&dir(+0x68),&amp(+0x69)) and, for
 * pad+0x118 == 1, Shock_SetMotor(dir, amp, &+0x6C, i, 0) + padSysVibSetAcrParam
 * (pad, +0x70). Tail: call the .data+0x268 hook when non-null (beql with the
 * `ld s0` epilogue in its delay slot).
 * -fno-strict-aliasing is required: without it GCC hoists the +8/+0 loads out of
 * the timer loop (alias analysis against the float stores) and the body differs.
 * UNCONFIRMED: struct/field names, callee prototypes (Shock_Decode takes the
 * 16-byte list at +0x58), the meaning of pad+0x118 == 1.
 */
struct ShockList {
    void *head;
    int unk4;
    void (*done)(void *w, int arg);
    int arg;
};

struct PadShock {
    struct ShockList list;
    unsigned char dir;
    unsigned char amp;
    char unk[2];
    int motor;
    char vib[8];
};

struct PadRec {
    unsigned int button;
    unsigned int prev;
    unsigned int press;
    unsigned int release;
    unsigned int repeat;
    float timer[16];
    unsigned char b54;
    unsigned char b55;
    unsigned char b56;
    unsigned char b57;
    struct PadShock shk;
};

extern struct PadRec D_kernel_data_0270[2];
extern void (*D_kernel_data_0268)(void);

unsigned long iosGetTCountExtension(void);
float iosGetSecondFromTCount(unsigned long t);
void padSysTickProc(void);
char *padSysGet(int port, int slot);
void Shock_Decode(struct ShockList *list, unsigned char *dir, unsigned char *amp);
void Shock_SetMotor(unsigned char dir, unsigned char amp, void *param, int id, int unk);
void padSysVibSetAcrParam(void *pad, void *param);

void iosPadTickProc(void) {
    struct PadRec *rec;
    struct PadShock *sh;
    char *pad;
    int i;
    int j;
    unsigned int cur;
    unsigned int prev;
    unsigned int diff;
    float now;

    now = iosGetSecondFromTCount(iosGetTCountExtension());
    padSysTickProc();
    for (i = 0; i < 2; i++) {
        rec = &D_kernel_data_0270[i];
        pad = padSysGet(i, 0);
        prev = rec->button;
        rec->prev = prev;
        cur = ((unsigned char)pad[0x104] << 8) | (unsigned char)pad[0x105];
        rec->repeat = 0;
        diff = cur ^ prev;
        rec->press = diff & cur;
        rec->release = diff & ~cur;
        rec->button = cur;
        for (j = 0; j < 16; j++) {
            if (rec->press & (1 << j)) {
                rec->timer[j] = now + 0.4f;
                rec->repeat |= 1 << j;
            } else if ((rec->button & (1 << j)) && rec->timer[j] < now) {
                rec->timer[j] = now + 0.08f;
                rec->repeat |= 1 << j;
            }
        }
        sh = &rec->shk;
        rec->b56 = (unsigned char)pad[0x106];
        rec->b57 = (unsigned char)pad[0x107];
        rec->b54 = (unsigned char)pad[0x108];
        rec->b55 = (unsigned char)pad[0x109];
        Shock_Decode(&sh->list, &sh->dir, &sh->amp);
        if (*(int *)(pad + 0x118) == 1) {
            Shock_SetMotor(sh->dir, sh->amp, &sh->motor, i, 0);
            padSysVibSetAcrParam(pad, sh->vib);
        }
    }
    if (D_kernel_data_0268 != 0) {
        D_kernel_data_0268();
    }
}
