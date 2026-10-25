/* KERNEL.XFF @ 0x01ACC0 (12 B) - isysInitGroup
 * Evidence: clears halfwords +2 then +0. UNCONFIRMED: field names.
 */
struct Group {
    unsigned short head;
    unsigned short count;
};
void isysInitGroup(struct Group *g) {
    g->count = 0;
    g->head = 0;
}
