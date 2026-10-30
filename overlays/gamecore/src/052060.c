/* GAMECORE.XFF @ 0x052060 (60 B) - constructor_expression_change
 * Evidence: one leading `sw $zero,0x0($a0)` for the head word, `addiu $a0,4`
 * to reach the record array, then a countdown loop (`$v0 = 4`,
 * `addiu $v0,-1` at the loop top, `bgez` at the bottom) clearing six ints per
 * 0x18-byte record with the pointer bumped in the `bgez` delay slot.
 * The do-while with a pre-decrement runs 5 times (i = 3..-1), which is the
 * image's iteration count.
 * UNCONFIRMED: the record layout; the store order (0,4,0x10,8,0x14,0xC) follows
 * the image, gcc emits these stores in source order.
 
 */
struct CtorRecord {
    int f00;
    int f04;
    int f08;
    int f0c;
    int f10;
    int f14;
};

struct CtorBlock {
    int head;
    struct CtorRecord rec[5];
};

void constructor_expression_change(struct CtorBlock *block) {
    struct CtorRecord *rec = block->rec;
    int i;

    block->head = 0;
    i = 4;
    do {
        --i;
        rec->f00 = 0;
        rec->f04 = 0;
        rec->f10 = 0;
        rec->f08 = 0;
        rec->f14 = 0;
        rec->f0c = 0;
        rec++;
    } while (i >= 0);
}
