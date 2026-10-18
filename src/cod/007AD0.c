/* asm/cod/007AD0.s -> StartThread.
 * StartThread; the thread-context initialisation is a single asm volatile block (sq $0 x36, sll/sd arg, lw/sd sign-extension of four register slots through $8) between plain C status checks (Session 23)
 * MATCHED. */
extern int QueryIntrContext(void);
extern int DIntr(void);
extern int EIntr(void);
extern int ReferThreadStatus(int tid, int *buf);
extern int _StartThread(int tid, int arg);

int StartThread(int tid, int arg) {
    int st[12];
    int r;
    char *p;

    if (QueryIntrContext() != 0)
        return -1;
    if (DIntr() == 0)
        return -1;
    r = ReferThreadStatus(tid, st);
    if (r < 0) {
        EIntr();
        return r;
    }
    if (st[0] != 0x10) {
        EIntr();
        return -1;
    }
    p = (char *)(st[2] + st[3] - 0x2A0);
    __asm__ volatile (
        "sq $0, 0x0(%0)
	"
        "sq $0, 0x10(%0)
	"
        "sq $0, 0x20(%0)
	"
        "sq $0, 0x30(%0)
	"
        "sq $0, 0x40(%0)
	"
        "sq $0, 0x50(%0)
	"
        "sq $0, 0x60(%0)
	"
        "sq $0, 0x70(%0)
	"
        "sq $0, 0x80(%0)
	"
        "sq $0, 0x90(%0)
	"
        "sq $0, 0xA0(%0)
	"
        "sq $0, 0xB0(%0)
	"
        "sq $0, 0xC0(%0)
	"
        "sq $0, 0xD0(%0)
	"
        "sq $0, 0xE0(%0)
	"
        "sq $0, 0xF0(%0)
	"
        "sq $0, 0x100(%0)
	"
        "sq $0, 0x110(%0)
	"
        "sq $0, 0x120(%0)
	"
        "sq $0, 0x130(%0)
	"
        "sq $0, 0x140(%0)
	"
        "sq $0, 0x150(%0)
	"
        "sq $0, 0x160(%0)
	"
        "sq $0, 0x170(%0)
	"
        "sq $0, 0x180(%0)
	"
        "sq $0, 0x190(%0)
	"
        "sq $0, 0x1A0(%0)
	"
        "sq $0, 0x1B0(%0)
	"
        "sq $0, 0x200(%0)
	"
        "sq $0, 0x210(%0)
	"
        "sq $0, 0x220(%0)
	"
        "sq $0, 0x230(%0)
	"
        "sq $0, 0x240(%0)
	"
        "sq $0, 0x250(%0)
	"
        "sq $0, 0x260(%0)
	"
        "sq $0, 0x270(%0)
	"
        "sll $8, %1, 0
	"
        "sd $8, 0x40(%0)
	"
        "lw $8, 0x1C0(%0)
	"
        "sd $8, 0x1C0(%0)
	"
        "sd $0, 0x1C8(%0)
	"
        "lw $8, 0x1D0(%0)
	"
        "sd $8, 0x1D0(%0)
	"
        "sd $0, 0x1D8(%0)
	"
        "lw $8, 0x1E0(%0)
	"
        "sd $8, 0x1E0(%0)
	"
        "sd $0, 0x1E8(%0)
	"
        "lw $8, 0x1F0(%0)
	"
        "sd $8, 0x1F0(%0)
	"
        "sd $0, 0x1F8(%0)
	"
        : : "r" (p), "r" (arg) : "$8", "memory");
    EIntr();
    return _StartThread(tid, arg);
}
