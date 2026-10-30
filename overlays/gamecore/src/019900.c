/* GAMECORE.XFF @ 0x019900 (56 B) - gStatGetPlayerAccessoriesDamgeRaitoToBoss
 * Evidence: same shape as the "ToPlayer" variant but the second field is
 * `0xC($v0)` instead of `0x8($v0)`.
 * UNCONFIRMED: the two pointer fields' meaning.
 
 */
struct AccessoryStat {
    char pad[0xC];
    float bossRatio;
};

extern struct AccessoryStat *D_kernel_data_09DC;
extern struct AccessoryStat *D_kernel_data_09E0;

float gStatGetPlayerAccessoriesDamgeRaitoToBoss(void) {
    float ratio = 1.0f;

    if (D_kernel_data_09DC != 0)
        ratio = D_kernel_data_09DC->bossRatio;
    return D_kernel_data_09E0 != 0 ? ratio * D_kernel_data_09E0->bossRatio
                                   : ratio;
}
