/* KERNEL.XFF @ 0x01BBD8 (40 B) - is_letter_reach_time
 * Evidence: returns 1 when limit (+4) <= time (+8); otherwise time += dt ($f12) and returns 0. UNCONFIRMED: field names.
 */
struct Letter {
    int unk0;
    float limit;
    float time;
};

int is_letter_reach_time(struct Letter *l, float dt) {
    if (l->limit <= l->time) {
        return 1;
    }
    l->time += dt;
    return 0;
}
