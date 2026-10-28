/* KERNEL.XFF @ 0x014DD8 (212 B) - iosGsResizeRootDC
 * Evidence: for both root DCs (+0x88 of the screen block at .bss+0x1F010, 400 B each) re-applies iosSetDCParam(dc, (w*sw >> 11) + (h*sh >> 11), w*sw >> 11, h, sh), iosSetDCClearParam(dc, 1, r, g, b, a) from the clear colour at .data+0x5B0 and iosSetDCViewPort(dc, 0, 0, h, sh) (sibling of iosSetRootContext). The colour loads never fill the call delay slot: the object is volatile. UNCONFIRMED: names.
 */
struct IosDC {
    char pad0[400];
};
struct RootEnv {
    int w;
    int scale_w;
    int h;
    int scale_h;
    char pad10[0x78];
    struct IosDC *root;
};
struct ClearColor {
    int r;
    int g;
    int b;
    int a;
};
extern struct RootEnv D_kernel_bss_1F010;
extern volatile struct ClearColor D_kernel_data_05B0;
void iosSetDCParam(struct IosDC *dc, int a, int b, int c, int d);
void iosSetDCClearParam(struct IosDC *dc, int enable, int r, int g, int b, int a);
void iosSetDCViewPort(struct IosDC *dc, int x, int y, int w, int h);

void iosGsResizeRootDC(void) {
    int i;

    for (i = 0; i < 2; i++) {
        iosSetDCParam(&D_kernel_bss_1F010.root[i], (D_kernel_bss_1F010.w * D_kernel_bss_1F010.scale_w >> 11) + (D_kernel_bss_1F010.h * D_kernel_bss_1F010.scale_h >> 11),
                      D_kernel_bss_1F010.w * D_kernel_bss_1F010.scale_w >> 11, D_kernel_bss_1F010.h, D_kernel_bss_1F010.scale_h);
        iosSetDCClearParam(&D_kernel_bss_1F010.root[i], 1, D_kernel_data_05B0.r, D_kernel_data_05B0.g, D_kernel_data_05B0.b, D_kernel_data_05B0.a);
        iosSetDCViewPort(&D_kernel_bss_1F010.root[i], 0, 0, D_kernel_bss_1F010.h, D_kernel_bss_1F010.scale_h);
    }
}
