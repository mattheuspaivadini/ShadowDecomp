/* asm/cod/0052D8.s -> usbSerialSysInit.
 * Sema id stored to its own .sbss word D_0013A188 (fills the bne delay slot), and the delay-loop bound -1 held in a local assigned before i = 0xFFFF, which fixes the constant order (Session 26).
 * MATCHED. */
typedef struct { int count; int max_count; int init_count; int wait_threads; unsigned int attr; void *option; int pad[2]; } ee_sema_t;
struct SifRpcClientData { char pad00[0x24]; void *server; char pad28[0x10]; };

extern int D_0013A188;
extern struct SifRpcClientData D_0013EAC0;
extern char D_00137410[];
extern char D_00137428[];
int CreateSema(ee_sema_t *s);
int func_001285C0(const char *fmt, ...);   /* printf */
void sceSifInitRpc(int mode);
int sceSifBindRpc(struct SifRpcClientData *cd, int rpc, int mode);
#define NOP() __asm__ volatile ("nop")

int usbSerialSysInit(void) {
    ee_sema_t s;
    int i;
    int sema;
    int end;

    s.init_count = 1;
    s.max_count = 1;
    sema = CreateSema(&s);
    D_0013A188 = sema;
    if (sema == -1) {
        func_001285C0(D_00137410);
        while (1) NOP();
    }
    sceSifInitRpc(0);
    while (1) {
        if (sceSifBindRpc(&D_0013EAC0, 0x80000220, 0) < 0) {
            func_001285C0(D_00137428);
            while (1) NOP();
        }
        if (D_0013EAC0.server != 0)
            break;
        end = -1;
        i = 0xFFFF;
        do {
            i -= 4;
            NOP();
        } while (i != end);
    }
    return 0;
}
