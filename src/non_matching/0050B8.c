/* STATUS (Session 8, 2026-10-14): NON_MATCHING. best score 25 [cc=296].
 * R3 famC: 0x0A->0x0D rewrite loop (3 unexplained nops before the bnez); cc=296 (8-byte slots)
 * The original .s stays in the build (asm/cod/0050B8.s); this C
 * draft (Session 8) is kept for the record. */
struct S40 {
    int w[16];              /* 0x00..0x3F */
};

extern int D_0013A180;      /* .sbss 0x0013A180 blob: small -> %gp_rel (+8) */
extern int D_0013EB00[];    /* .bss 0x0013EB00 (the staging buffer) -> lui/%lo */
extern int D_0013EB40[];    /* .bss 0x0013EB40 (the reply) -> lui/%lo */
extern int D_0013EAC0[];    /* .bss 0x0013EAC0 (the request) -> lui/%lo */

int SceSifrpcCall(int a0, int a1, int a2, int a3, int a4, int a5, int a6,
                  int a7, int a8);
int func_001290C4(char *a0);
void func_00128FB0(int a0, int a1);
void func_00107020(int a0);
int func_001053F0(void);

int func_001050B8(char *a0) {
    int total;
    int chunk;
    int n;
    int r;
    char *p;
    char *q;

    total = func_001290C4(a0);
    if (total <= 0)
        return D_0013EB40[0];
    p = a0;
    do {
        if (total < 0x40) {
            func_00128FB0((int)D_0013EB00, (int)p);
            D_0013EB00[0x3F] = 0;
            chunk = total;
        } else {
            chunk = 0x40;
            *(struct S40 *)D_0013EB00 = *(struct S40 *)p;
        }
        if (chunk > 0) {
            n = chunk;
            q = (char *)D_0013EB00;
            do {
                if (*q == 0xA)
                    *q = 0xD;
                q++;
            } while (--n != 0);
        }
        func_00107020(*(int *)((char *)&D_0013A180 + 8));
        r = SceSifrpcCall((int)D_0013EAC0, 0x10, 0, (int)D_0013EB00, 0x40,
                          (int)D_0013EB40, 0x20, (int)func_001053F0, 0);
        if (r != 0)
            return r;
        total -= chunk;
        p += chunk;
    } while (total > 0);
    return D_0013EB40[0];
}
