/* GAMECORE.XFF @ 0x0C0B00 (64 B) - bosslifebar_resethp
 * Evidence: build/s79/b/dis_all.txt (authority). Two leading nops are part of
 * the image range. r = y / x, p = x * 0.01f; the record keeps r in three
 * float fields, clears the int flag at +0xC, and stores p to D+0x14.
 * NOTE: source order is chosen so GCC emits the stores in the image order
 * (flag, +0x14, f0, f8, f4); the last source store lands in the jr delay slot.
 * UNCONFIRMED: struct/field names.
 
 */
struct LifebarWork {
    float f0;    /* 0x0 */
    float f4;    /* 0x4 */
    float f8;    /* 0x8 */
    int   flag;  /* 0xC */
};

extern struct LifebarWork D_kernel_data_17A0;
extern float D_kernel_data_17B4;

void bosslifebar_resethp(float x, float y) {
    float r = y / x;
    float p = x * 0.01f;

    D_kernel_data_17A0.flag = 0;
    D_kernel_data_17B4 = p;
    D_kernel_data_17A0.f8 = r;
    D_kernel_data_17A0.f4 = r;
    D_kernel_data_17A0.f0 = r;
}
