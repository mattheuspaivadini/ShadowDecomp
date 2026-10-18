/* asm/cod/0153B8.s -> scePad2GetState.
 * scePad2GetState; u_long bitfield request union, both success paths join a shared out: return of the stack byte (Session 22)
 * MATCHED. */
typedef struct {
    unsigned long f0:14;
    unsigned long f1:2;
    unsigned long f2:8;
    unsigned long f3:8;
} DbcParam;
struct PadRec {
    int open;
    int ready;               /* 0x04 */
    char pad08[0x334 - 8];
};
struct PadFrame {
    unsigned char state;     /* 0x00 */
    unsigned char f01, f02, f03;
    int valid;               /* 0x04 */
};
extern struct PadRec D_0014B598[];

int func_00115650(int port);
int func_00115778(int port);
struct PadFrame *func_00115710(int port);
void func_001155D8(int port);
int sceDbcReceiveData(int port, int param, int *size, unsigned char *data);

int scePad2GetState(int port) {
    union { unsigned long l; DbcParam s; } t;
    struct PadFrame *p;
    unsigned char state;
    int size;

    if (D_0014B598[port].ready == 0 && func_00115650(port) < 0)
        return 0;
    if (func_00115778(port) != 0) {
        p = func_00115710(port);
        if (p->valid == 0 && func_00115650(port) < 0)
            goto fail;
        state = p->state;
        goto out;
    }
    t.s.f0 = 0xC;
    t.s.f1 = 2;
    t.s.f2 = 1;
    t.s.f3 = 1;
    if (sceDbcReceiveData(port, (int)t.l, &size, &state) >= 0)
        goto out;
fail:
    D_0014B598[port].ready = 0;
    func_001155D8(port);
    return 0;
out:
    return state;
}
