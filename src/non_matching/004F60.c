/* STATUS (Session 7, 2026-10-14): NON_MATCHING. best score 11 [cc=296, default].
 * CreateSema + CreateThread blocks.
 * The original .s stays in the build (asm/cod/004F60.s); this C
 * draft (subagent-produced, Session 7) is kept for the record. */
/* asm/cod/004F60.s -> func_00104F60 @ 0x00104F60 (0x8C bytes, 35 insns)
 *
 * Thread bootstrap. Two stack parameter blocks:
 *
 *   sema at $sp+0x00 (CreateSema block: +0x04 = 1, +0x08 = 0, +0x14 = 0)
 *   D_0013A118 = func_00106FE0(&sema);        ; 0x40 syscall = CreateSema
 *   th at $sp+0x20 (CreateThread block: +0x04 = func_00104FF0, +0x08 =
 *     D_0013DAC0, +0x0C = 0x1000, +0x10 = D_00141D70, +0x14 = 1)
 *   func_00106DE0(&th);                       ; 0x20 syscall = CreateThread
 *   func_00107AD0(thread_id, 0);
 *   func_00117138(D_001050A0, 0);
 *
 * func_00106DE0 is `addiu $v1,$zero,0x20; syscall 0` and func_00106FE0 is the
 * 0x40 sibling (asm/cod/006DE0.s / 006FE0.s), i.e. the EE CreateThread /
 * CreateSema calls; func_00106DE0's one register argument is why $a1/$a2 still
 * hold stale values at the call site. D_00141D70 is the linker's `_gp`
 * ($gp = 0x00141D70) stored as the thread's gp; D_0013DAC0 is the stack and
 * 0x1000 its size. The store order in the asm is 0x14, 0x10, 0x0C, 0x04, 0x08
 * (scheduler interleaving) and D_0013A118 is %gp_rel (a .sbss scalar).
 *
 * The frame is 0x60 with $s0 at 0x50 and $ra at 0x58 -> 0x50 bytes of locals
 * (sema slot 0x20 + thread slot 0x30). The thread block's slot size is not
 * observable from the stores (they stop at +0x14); 0x30 reproduces the frame.
 * UNCONFIRMED: thread-block slot/pad size 0x30.
 * MATCH GUESS: cc=296 (8-byte-spaced $s0/$ra pair; 0x00104xxx is a 2.96 TU) */
struct S004F60Sema {
    int  count;     /* 0x00 */
    int  max;       /* 0x04 */
    int  init;      /* 0x08 */
    int  wait;      /* 0x0C */
    int  attr;      /* 0x10 */
    int  option;    /* 0x14 */
    char pad[8];    /* 0x18-0x1F */
};

struct S004F60Thread {
    int   status;   /* 0x00 */
    void *entry;    /* 0x04 */
    void *stack;    /* 0x08 */
    int   size;     /* 0x0C */
    int   gp;       /* 0x10 */
    int   option;   /* 0x14 */
    char  pad[0x18];/* 0x18-0x2F (UNCONFIRMED slot size) */
};

int  CreateSema(void *param);          /* syscall 0x40: CreateSema  */
int  CreateThread(void *param);          /* syscall 0x20: CreateThread */
int  StartThread(int thread, int a1);
void sceCdPOffCallback(int entry, int arg);
int  func_00104FF0(void);                 /* the thread entry point   */

extern int  D_0013A118;      /* .sbss, %gp_rel: the semaphore handle     */
extern char D_0013DAC0[];    /* thread stack (lui/%lo address)           */
extern char _gp[];    /* _gp itself (lui/%lo address)             */
extern char D_001050A0[];    /* entry installed by func_00117138         */

void PreparePowerOff(void) {
    struct S004F60Sema sema;
    struct S004F60Thread th;

    sema.max = 1;
    sema.init = 0;
    sema.option = 0;
    D_0013A118 = CreateSema(&sema);
    th.entry = (void *)func_00104FF0;
    th.stack = D_0013DAC0;
    th.size = 0x1000;
    th.gp = (int)_gp;
    th.option = 1;
    StartThread(CreateThread(&th), 0);
    sceCdPOffCallback((int)D_001050A0, 0);
}
