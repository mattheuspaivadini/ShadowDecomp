/* KERNEL.XFF @ 0x02A358 (92 B) - Sg2SlotSetPoltamentParam
 * Evidence: on the 0xE0-byte slot [i] (.bss+0x97E30): if flag 0x200 is clear, sets it, clears +0xDC and copies +0x24 into +0xCC and +0xD0; then +0xD4 = target and +0xD8 = speed, negated when target < +0xD0. UNCONFIRMED: field names (portamento start/current/target/speed/count).
 */
struct Sg2Slot {
    unsigned int flags;
    char pad4[0x20];
    int pitch;
    char pad28[0xCC - 0x28];
    int porta_start;
    int porta_cur;
    int porta_target;
    float porta_speed;
    int porta_count;
};
extern struct Sg2Slot D_kernel_bss_97E30[48];

void Sg2SlotSetPoltamentParam(int i, int target, float speed) {
    struct Sg2Slot *s = &D_kernel_bss_97E30[i];

    if (!(s->flags & 0x200)) {
        s->flags |= 0x200;
        s->porta_count = 0;
        s->porta_start = s->pitch;
        s->porta_cur = s->pitch;
    }
    s->porta_target = target;
    if (target < s->porta_cur) {
        speed = -speed;
    }
    s->porta_speed = speed;
}
