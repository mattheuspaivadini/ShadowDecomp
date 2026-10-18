/* asm/cod/0146B8.s -> SCE_GS_SET_TEST.
 * sceGsSetDefClear; sceGsClear struct + SCE_GS_SET_* macros, statement order found by permutation (Session 22)
 * MATCHED. */
typedef unsigned long u_long;
typedef unsigned int u_int;
typedef unsigned char u_char;
typedef struct {
    u_long testa;      u_long testaaddr;   /* 0x00 */
    u_long prim;       u_long primaddr;    /* 0x10 */
    u_long rgbaq;      u_long rgbaqaddr;   /* 0x20 */
    u_long xyz2a;      u_long xyz2aaddr;   /* 0x30 */
    u_long xyz2b;      u_long xyz2baddr;   /* 0x40 */
    u_long testb;      u_long testbaddr;   /* 0x50 */
} sceGsClear;

#define SCE_GS_PRIM      0x00
#define SCE_GS_RGBAQ     0x01
#define SCE_GS_XYZ2      0x05
#define SCE_GS_TEST_1    0x47
#define SCE_GS_SET_TEST(ate, atst, aref, afail, date, datm, zte, ztst)     ((u_long)(ate) | ((u_long)(atst) << 1) | ((u_long)(aref) << 4) |      ((u_long)(afail) << 12) | ((u_long)(date) << 14) | ((u_long)(datm) << 15) |      ((u_long)(zte) << 16) | ((u_long)(ztst) << 17))
#define SCE_GS_SET_PRIM(prim, iip, tme, fge, abe, aa1, fst, ctxt, fix)     ((u_long)(prim) | ((u_long)(iip) << 3) | ((u_long)(tme) << 4) |      ((u_long)(fge) << 5) | ((u_long)(abe) << 6) | ((u_long)(aa1) << 7) |      ((u_long)(fst) << 8) | ((u_long)(ctxt) << 9) | ((u_long)(fix) << 10))
#define SCE_GS_SET_RGBAQ(r, g, b, a, q)     ((u_long)(r) | ((u_long)(g) << 8) | ((u_long)(b) << 16) |      ((u_long)(a) << 24) | ((u_long)(q) << 32))
#define SCE_GS_SET_XYZ(x, y, z)     ((u_long)(x) | ((u_long)(y) << 16) | ((u_long)(z) << 32))

int sceGsSetDefClear(sceGsClear *cp, short ztest, short x, short y, short w, short h,
                     u_char r, u_char g, u_char b, u_char a, u_int z) {
    cp->testaaddr = SCE_GS_TEST_1;
    cp->testa = SCE_GS_SET_TEST(0, 0, 0, 0, 0, 0, 1, 1);
    cp->prim = SCE_GS_SET_PRIM(6, 0, 0, 0, 0, 0, 0, 0, 0);
    cp->primaddr = SCE_GS_PRIM;
    cp->rgbaqaddr = SCE_GS_RGBAQ;
    cp->rgbaq = SCE_GS_SET_RGBAQ(r, g, b, a, 0x3f800000);
    cp->xyz2a = SCE_GS_SET_XYZ(x << 4, y << 4, z);
    cp->xyz2aaddr = SCE_GS_XYZ2;
    cp->xyz2baddr = SCE_GS_XYZ2;
    cp->xyz2b = SCE_GS_SET_XYZ((x + w) << 4, (y + h) << 4, z);
    cp->testbaddr = SCE_GS_TEST_1;
    if (ztest)
        cp->testb = SCE_GS_SET_TEST(0, 0, 0, 0, 0, 0, 1, ztest & 3);
    else
        cp->testb = SCE_GS_SET_TEST(0, 0, 0, 0, 0, 0, 1, 1);
    __asm__ __volatile__("sync" ::: "memory");
    return 6;
}
