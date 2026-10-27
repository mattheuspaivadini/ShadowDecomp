/* KERNEL.XFF @ 0x01BB40 (16 B) - is_hope_letter_type
 * Evidence: returns l->+0xC == type (xor + sltiu 1).
 */
struct Letter {
    char pad[0xC];
    int type;
};

int is_hope_letter_type(struct Letter *l, int type) {
    return l->type == type;
}
