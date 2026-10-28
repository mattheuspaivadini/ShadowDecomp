/* KERNEL.XFF @ 0x014CF8 (224 B) - iosSetRootContext
 * Evidence: creates two DCs on rootPtn, then for each: iosSetDCParam(dc, (w*sw >> 11) + (h*sh >> 11), w*sw >> 11, h, sh) from the screen block at .bss+0x1F010, iosSetDCClearParam(dc, 1, 0, 0, 0, 0x80) and iosSetDCViewPort(dc, 0, 0, h, sh); the DC array is kept at +0x88. UNCONFIRMED: field names.
 */
struct IosDC {
    char pad0[400];
};
struct DCObj {
    void *ptn;
    char pad4[0x18];
    struct IosDC *dc;
    int num;
};
struct RootEnv {
    int w;
    int scale_w;
    int h;
    int scale_h;
    char pad10[0x78];
    struct IosDC *root;
};
extern char rootPtn[];
extern struct RootEnv D_kernel_bss_1F010;
struct DCObj *iosCreateDC(void *parent, int num);
void iosSetDCParam(struct IosDC *dc, int a, int b, int c, int d);
void iosSetDCClearParam(struct IosDC *dc, int enable, int r, int g, int b, int a);
void iosSetDCViewPort(struct IosDC *dc, int x, int y, int w, int h);

void iosSetRootContext(void) {
    struct IosDC *root;
    struct IosDC *dc;
    int i;

    root = iosCreateDC(rootPtn, 2)->dc;
    dc = root;
    for (i = 0; i < 2; i++) {
        iosSetDCParam(dc, (D_kernel_bss_1F010.w * D_kernel_bss_1F010.scale_w >> 11) + (D_kernel_bss_1F010.h * D_kernel_bss_1F010.scale_h >> 11),
                      D_kernel_bss_1F010.w * D_kernel_bss_1F010.scale_w >> 11, D_kernel_bss_1F010.h, D_kernel_bss_1F010.scale_h);
        iosSetDCClearParam(dc, 1, 0, 0, 0, 0x80);
        iosSetDCViewPort(dc, 0, 0, D_kernel_bss_1F010.h, D_kernel_bss_1F010.scale_h);
        dc++;
    }
    D_kernel_bss_1F010.root = root;
}
