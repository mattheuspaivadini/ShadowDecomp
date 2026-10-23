/* STATUS (Session 42, 2026-10-21): NON_MATCHING. best score 2 (was 4; sw.py diff lines).
 * Empty asm ("+r") on buf after the "m" fence moves move a0,s0 after the mult. Residual: addiu %lo(D_0014B598) before li 0x334/mult (image: after); the "m" fence makes the full address available before the multiply. Tried: second-level fence grid (168), offset temps with asm, int-sum address forms, base pointer local with asm.
 * Volatile asm fence with an "m"(D_0014B598[0]) operand after the s < 0 return puts the base lui into the bltz slot like the image (7 -> 4 instructions). Residual: the lo addiu and move a0,s0 are scheduled before li 0x334/mult (image: after). Tried X/p/m operand forms, fence placement, if (s >= 0) block, 49 address-form pairs (base+off / off+base / int sums: CSE merges the two sums).
 * Residual = lui %hi(D_0014B598) comes before li 0x334 in the original (bltz delay slot holds the lui); ours puts the li first. Tried store order f00/f10, record pointer, (D + s)->f, s[D], table base local, unsigned s, if (s >= 0) block, D_0014B598[16], sharing the 1 constant.
 * Session 61 (2026-10-23): REA/Ghidra dossier ev_77e41be23974c7510b0b38cd9ab226ddb73d844786c72d924e6ef9d649b1bbe4 confirms the socket setup/update flow. The recorded 990721 compiler still scores 2. An offset memory-barrier variant scored 6; a hard-pinned base/lui-addiu variant scored 7. A volatile inline-asm tail (explicit bltz/lui delay slot, mult, store, jal+delay) reproduced that region but scored 3, leaving the call-argument a0/a1/a2 moves in a different order; pinning the call setup regressed to 11-14. Restored the score-2 C baseline.
 * The original .s stays in the build (asm/cod/0150B0.s); this C
 * draft (Session 29) is kept for the record. */
struct Pad2Name {               /* 16-byte name block, byte-aligned (ldl/ldr copy) */
    unsigned char c[16];
};

struct Pad2SockParam {
    int f00;                    /* 0x00 */
    int f04;                    /* 0x04 */
    int f08;                    /* 0x08 */
    int f0C;                    /* 0x0C */
    struct Pad2Name name;       /* 0x10 */
};

struct Pad2SockReq {
    int f00;                    /* 0x00 */
    int f04;                    /* 0x04 */
    int f08;                    /* 0x08 */
    int f0C;                    /* 0x0C */
    int f10;                    /* 0x10 */
    struct Pad2Name name;       /* 0x14 */
};

struct Pad2Rec {
    int  f00;                   /* 0x00 */
    int  f04;                   /* 0x04 */
    int  f08;                   /* 0x08 */
    int  f0C;                   /* 0x0C */
    int  f10;                   /* 0x10 */
    char rest[0x334 - 0x14];
};

extern struct Pad2Rec D_0014B598[];
extern char D_00138560[];

int scePrintf(const char *fmt, ...);
int sceDbcCreateSocket(struct Pad2SockReq *req, int buf, int end);
void func_001155D8(int index);

int scePad2CreateSocket(struct Pad2SockParam *param, int buf) {
    struct Pad2SockReq req;
    int s;

    if (buf & 0x3F) {
        scePrintf(D_00138560);
        return -1;
    }
    if (param) {
        req.f00 = param->f00;
        req.f08 = param->f04;
        req.f0C = param->f08;
        req.f10 = param->f0C;
        req.name = param->name;
    } else {
        req.f00 = 0;
        req.f08 = 0;
        req.f0C = 0;
        req.f10 = 0;
        req.name.c[0] = 0;
    }
    req.f04 = 1;
    req.f00 |= 1;
    s = sceDbcCreateSocket(&req, buf, buf + 0x80);
    if (s < 0)
        return s;
    __asm__ __volatile__ ("" : : "m" (D_0014B598[0]));
    asm("" : "+r"(buf));
    D_0014B598[s].f10 = buf;
    D_0014B598[s].f00 = 1;
    func_001155D8(s);
    return s;
}
