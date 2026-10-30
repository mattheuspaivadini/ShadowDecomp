/* KERNEL.XFF @ 0x014250 (1012 B) - iosDumpGIFStatus  [MATCHED, -G0 -fno-strict-aliasing]
 * Evidence: argument-free GIF diagnostic dump, same family as 013eb0: eight
 * aggregate local initialisers whose .rodata templates (0x1898 {Enable,
 * Disable}, 0x18C0 {連続転送,断続転送}, 0x18E0 {通常,一時停止}, 0x18E8
 * {なし,あり}, 0x1900 {待機中,出力中}, 0x1920 {アイドル,PATH1..3}, 0x1940
 * {EE->GS,GS->EE}, 0x1988 {PACKED/REGLIST/IMAGE転送,使用禁止}) are copied into
 * the 224-byte frame with ldl/ldr+sdl/sdr at sp+0,16,32,48,64,80,96,112.
 * `lw` of 0x10003020 (GIF_STAT) into the callee-saved s0 is the live
 * statistic; the printed masks are (stat >> n) & {1,3} (the image folds
 * index*4 into `srl n-2 / andi 4` or `andi 0xc`).
 * LEVER (this is what closed it): every STAT field must be pre-extracted into
 * its own local *once* (m0..m12, dev, cnt) before the prints.  Written inline
 * as `tab[(stat >> 1) & 1]` the compiler folds the scale into the mask
 * (`sll 1 / andi 4`) and keeps all eight table bases in callee-saved
 * registers: 932 B instead of 1012 B.  With the extractions as statements the
 * image's `srl n / andi sX,1` + `sll sX,2`-at-the-use shape appears, the eight
 * base addresses are rematerialised as `addiu tN,sp,K` per print, and the
 * pressure spills dev (sp+132), cnt (sp+136) and the STAT pointer (sp+128,
 * reloaded for the last `*gif`) exactly as shipped.
 * 0x10003040/0x10003050 are re-read three/four times inside one argument list
 * (`lw a1,0(v0)` x3 from one address), so they are read through a volatile
 * pointer; 0x10003070/0x10003060 are the GIFTAG REGS pair and 0x10003080 the
 * P3CNT block (LOOPCNT/REGCNT/VUADDR).  Format strings 0x19D0..0x1BA0 give the
 * field roles; 0x1688 ("-----") is shared with 013eb0.
 * UNCONFIRMED: exact roles of the 0x3040/0x3050 words beyond the masks decoded
 * from the format string (NLOOP/EOP/PRE/PRIM/FLG/NREG).
 */
typedef unsigned int u32;

extern int LoaderSysPrintf(const char *fmt, ...);

extern char D_kernel_rodata_1898[];
extern char D_kernel_rodata_18C0[];
extern char D_kernel_rodata_18E0[];
extern char D_kernel_rodata_18E8[];
extern char D_kernel_rodata_1900[];
extern char D_kernel_rodata_1920[];
extern char D_kernel_rodata_1940[];
extern char D_kernel_rodata_1988[];
extern char D_kernel_rodata_1998[];
extern char D_kernel_rodata_19D0[];
extern char D_kernel_rodata_19E8[];
extern char D_kernel_rodata_1A00[];
extern char D_kernel_rodata_1A18[];
extern char D_kernel_rodata_1A30[];
extern char D_kernel_rodata_1A48[];
extern char D_kernel_rodata_1A60[];
extern char D_kernel_rodata_1A78[];
extern char D_kernel_rodata_1A90[];
extern char D_kernel_rodata_1AA8[];
extern char D_kernel_rodata_1AC0[];
extern char D_kernel_rodata_1AD8[];
extern char D_kernel_rodata_1688[];
extern char D_kernel_rodata_1AF8[];
extern char D_kernel_rodata_1B18[];
extern char D_kernel_rodata_1B58[];
extern char D_kernel_rodata_1BA0[];

void iosDumpGIFStatus(void) {
    char *onoff[] = { D_kernel_rodata_1898, D_kernel_rodata_1898 + 8 };
    char *trsmode[] = { D_kernel_rodata_18C0, D_kernel_rodata_18C0 + 8 };
    char *pause[] = { D_kernel_rodata_18E0, D_kernel_rodata_18E0 + 8 };
    char *none[] = { D_kernel_rodata_18E8, D_kernel_rodata_18E8 + 8 };
    char *outpath[] = { D_kernel_rodata_1900, D_kernel_rodata_1900 + 8 };
    char *device[] = { D_kernel_rodata_1920, D_kernel_rodata_1920 + 4,
                       D_kernel_rodata_1920 + 8, D_kernel_rodata_1920 + 12 };
    char *direction[] = { D_kernel_rodata_1940, D_kernel_rodata_1940 + 8 };
    char *flags[] = { D_kernel_rodata_1988, D_kernel_rodata_1988 + 4,
                      D_kernel_rodata_1988 + 8, D_kernel_rodata_1988 + 12 };
    volatile u32 *gif = (volatile u32 *)0x10003020;
    u32 stat, m0, m1, m2, m3, m5, m6, m7, m8, m9, dev, m12, cnt;

    stat = *gif;
    LoaderSysPrintf(D_kernel_rodata_1998);
    m0 = stat & 1;
    m1 = (stat >> 1) & 1;
    m2 = (stat >> 2) & 1;
    m3 = (stat >> 3) & 1;
    m5 = (stat >> 5) & 1;
    m6 = (stat >> 6) & 1;
    m7 = (stat >> 7) & 1;
    m8 = (stat >> 8) & 1;
    m9 = (stat >> 9) & 1;
    dev = (stat >> 10) & 3;
    m12 = (stat >> 12) & 1;
    cnt = (stat >> 24) & 0x1F;
    LoaderSysPrintf(D_kernel_rodata_19D0, onoff[m0]);
    LoaderSysPrintf(D_kernel_rodata_19E8, onoff[m1]);
    LoaderSysPrintf(D_kernel_rodata_1A00, trsmode[m2]);
    LoaderSysPrintf(D_kernel_rodata_1A18, pause[m3]);
    LoaderSysPrintf(D_kernel_rodata_1A30, none[m5]);
    LoaderSysPrintf(D_kernel_rodata_1A48, none[m6]);
    LoaderSysPrintf(D_kernel_rodata_1A60, none[m7]);
    LoaderSysPrintf(D_kernel_rodata_1A78, none[m8]);
    LoaderSysPrintf(D_kernel_rodata_1A90, outpath[m9]);
    LoaderSysPrintf(D_kernel_rodata_1AA8, device[dev]);
    LoaderSysPrintf(D_kernel_rodata_1AC0, direction[m12]);
    LoaderSysPrintf(D_kernel_rodata_1AD8, cnt, cnt);
    LoaderSysPrintf(D_kernel_rodata_1688);
    LoaderSysPrintf(D_kernel_rodata_1AF8, *(volatile u32 *)0x10003070,
                    *(volatile u32 *)0x10003060);
    LoaderSysPrintf(D_kernel_rodata_1B18, *(volatile u32 *)0x10003040 & 0x7FFF,
                    *(volatile u32 *)0x10003040 & 0x7FFF,
                    (*(volatile u32 *)0x10003040 >> 15) & 1,
                    (*(volatile u32 *)0x10003050 >> 14) & 1,
                    (*(volatile u32 *)0x10003050 >> 15) & 0x7FF,
                    flags[(*(volatile u32 *)0x10003050 >> 26) & 3],
                    *(volatile u32 *)0x10003050 >> 28);
    LoaderSysPrintf(D_kernel_rodata_1B58, *(volatile u32 *)0x10003080 & 0x7FFF,
                    (*(volatile u32 *)0x10003080 >> 16) & 0xF,
                    (*(volatile u32 *)0x10003080 >> 20) & 0x3FF);
    LoaderSysPrintf(D_kernel_rodata_1BA0, *gif);
}
