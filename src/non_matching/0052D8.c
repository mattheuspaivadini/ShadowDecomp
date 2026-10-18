/* STATUS (Session 23, 2026-10-18): NON_MATCHING. best score 8 [cc=296] (was 40).
 * Hang/delay loops use asm("nop") (ee-gcc adds 4 nops after an asm), ee_sema_t + SifRpcClientData typed, sema id in an .sbss record. Residuals: the sema-id store is not taken into the bne delay slot (ours: bnel with the target insn), the delay-loop constants' order, and .p2align nops follow from that.
 * The original .s stays in the build (asm/cod/0052D8.s); this C
 * draft (Session 23) is kept for the record. */
typedef struct { int count; int max_count; int init_count; int wait_threads; unsigned int attr; void *option; int pad[2]; } ee_sema_t;
struct SifRpcClientData { char pad00[0x24]; void *server; char pad28[0x10]; };
struct UsbSys { int f00; int f04; int sema; };
extern struct UsbSys D_0013A180 __attribute__((section(".sbss")));
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

    s.init_count = 1;
    s.max_count = 1;
    sema = CreateSema(&s);
    D_0013A180.sema = sema;
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
        i = 0xFFFF;
        do {
            i -= 4;
            NOP();
        } while (i != -1);
    }
    return 0;
}
