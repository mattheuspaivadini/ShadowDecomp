/* KERNEL.XFF @ 0x007378 (52 B) - Shock_SetShockVoiceSet
 * Evidence: table pointer from .data+0x368; `index < table->count` (sltu) guards
 * `table->entries[index] = set`; returns index or -1 (set in the beqz slot).
 * UNCONFIRMED: object names.
 */
struct VoiceTable {
    unsigned int count;
    void **entries;
};
extern struct VoiceTable *D_kernel_data_0368;

int Shock_SetShockVoiceSet(unsigned int index, void *set) {
    struct VoiceTable *t = D_kernel_data_0368;
    int ret = -1;

    if (index < t->count) {
        t->entries[index] = set;
        ret = index;
    }
    return ret;
}
