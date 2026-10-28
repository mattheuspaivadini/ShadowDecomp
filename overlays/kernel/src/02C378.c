/* KERNEL.XFF @ 0x02C378 (204 B) - Sg2SmfpGetParam
 * Evidence: 0 for id < 0; else by type: 2 -> +0x10, 4 -> +0x18, 8 -> +0x1C, 0x200 -> (int) of the double at +0x30 (dptoli) of the SMF record [id] (.bss+0x9A880); any other type returns the uninitialised ret (switch without default). UNCONFIRMED: field names.
 */
struct Sg2Smfp {
    int status;
    int unk4;
    int mod;
    int vab;
    int unk10;
    int unk14;
    int unk18;
    int unk1C;
    char pad20[0x10];
    double tempo;
    char pad38[0x80 - 0x38];
};
extern struct Sg2Smfp D_kernel_bss_9A880[8];
int Sg2SmfpGetParam(int id, int type) {
 int ret;
 if (id >= 0) {
 switch (type) {
 case 2: ret = D_kernel_bss_9A880[id].unk10; break;
 case 4: ret = D_kernel_bss_9A880[id].unk18; break;
 case 8: ret = D_kernel_bss_9A880[id].unk1C; break;
 case 0x200: ret = D_kernel_bss_9A880[id].tempo; break;
 }
 } else {
 ret = 0;
 }
 return ret;
}
