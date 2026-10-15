/* STATUS (Session 8, 2026-10-14): NON_MATCHING. best score 4 [cc=29].
 * R2 w45a_1: stack/store-order (0x90 frame, thread/sema split)
 * The original .s stays in the build (asm/cod/007768.s); this C
 * draft (Session 8) is kept for the record. */
struct S007768Thread {
    int  f00;
    int  f04;   /* 0x04 entry */
    int  f08;   /* 0x08 stack */
    int  f0C;   /* 0x0C size  */
    int  f10;   /* 0x10 gp    */
    int  f14;   /* 0x14 option */
    int  f18;
    int  f1C;
    int  f20;   /* 0x20 argument pointer */
    char pad[0x0C];
};

struct S007768Sema {
    int  f00;
    int  f04;   /* 0x04 */
    int  f08;   /* 0x08 */
    int  f0C;
    int  f10;
    int  f14;   /* 0x14 */
    char pad[0x08];
};

extern int  D_00132280[];   /* lui/%lo (thread handle, 0 when unset) */
extern int  D_00143C90[];   /* lui/%lo (sema handle) */
extern int  D_00143C98[];   /* lui/%lo (2-word init block) */
extern char D_00143890[];   /* thread stack */
extern char D_00141D70[];   /* _gp itself */
extern char D_00137CB0[];   /* name/parameter block */

int  func_00106FE0(void *param);    /* syscall 0x40: CreateSema  */
int  func_00106DE0(void *param);    /* syscall 0x20: CreateThread */
int  func_00106FF0(int a0);         /* syscall 0x41: DeleteSema  */
int  func_00107AD0(int thread, int a1);
int  func_00106ED0(void);
int  func_00106E70(int a0, int a1);
void func_00107690(char *a0);       /* the thread entry point */

int func_00107768(void) {
    struct S007768Thread th;
    struct S007768Sema sema;
    int r;

    if (D_00132280[0] > 0)
        return -1;
    sema.f04 = 0xFF;
    sema.f08 = 0;
    sema.f14 = (int)D_00137CB0;
    r = func_00106FE0(&sema);
    D_00143C90[0] = r;
    if (r < 0)
        return -1;
    th.f04 = (int)func_00107690;
    th.f08 = (int)D_00143890;
    th.f0C = 0x400;
    th.f10 = (int)D_00141D70;
    th.f20 = (int)D_00137CB0;
    th.f14 = 0;
    r = func_00106DE0(&th);
    D_00132280[0] = r;
    if (r < 0) {
        func_00106FF0(D_00143C90[0]);
        return -1;
    }
    D_00143C98[0] = 0;
    D_00143C98[1] = 0;
    func_00107AD0(r, (int)D_00143C98);
    func_00106E70(func_00106ED0(), 1);
    return D_00132280[0];
}
