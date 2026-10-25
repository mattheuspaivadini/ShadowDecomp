/* KERNEL.XFF @ 0x01BB28 (20 B) - init_letter
 * Evidence: *a = 0; *b = 0; l->+0x20 = 1. UNCONFIRMED: names.
 */
struct Letter {
    char pad[0x20];
    int state;
};

void init_letter(struct Letter *l, int *a, int *b) {
    *a = 0;
    *b = 0;
    l->state = 1;
}
