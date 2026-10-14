/* asm/cod/009640.s -> func_00109640 @ 0x00109640 (0x4C bytes)
 *   lw    $a1, 0x28($a1)              ; node = n->field28
 *   beqz  $a1, .L00109684
 *    nop
 *   lw    $v1, 0x8($a1)
 * .L00109650:
 *   beql  $v1, $zero, .L0010967C
 *    lw   $a1, 0x14($a1)              ; node = node->field14
 *   lw    $v0, 0x0($v1)               ; e->field00
 * .L00109660:
 *   bnel  $v0, $a0, .L00109670
 *    lw   $v1, 0x38($v1)              ; e = e->field38
 *   jr    $ra
 *    daddu $v0, $v1, $zero            ; return e
 * .L00109670:
 *   bnel  $v1, $zero, .L00109660
 *    lw   $v0, 0x0($v1)
 *   lw    $a1, 0x14($a1)
 * .L0010967C:
 *   bnel  $a1, $zero, .L00109650
 *    lw   $v1, 0x8($a1)
 * .L00109684:
 *   jr    $ra
 *    daddu $v0, $zero, $zero
 *
 * Search a list of nodes (linked via field14, entries via field08, entry chain
 * via field38) for the entry whose field00 == key. Returns the entry or NULL.
 */
struct E009640 {
    int               field00;   /* 0x00 key */
    char              pad04[0x34];
    struct E009640   *field38;   /* 0x38 */
};

struct N009640 {
    char              pad00[0x08];
    struct E009640   *field08;   /* 0x08 entry list */
    char              pad0C[0x08];
    struct N009640   *field14;   /* 0x14 next node */
    char              pad18[0x10];
    struct N009640   *field28;   /* 0x28 head */
};

struct E009640 *func_00109640(int key, struct N009640 *n) {
    struct N009640 *node;

    for (node = n->field28; node != 0; node = node->field14) {
        struct E009640 *e;

        for (e = node->field08; e != 0; e = e->field38) {
            if (e->field00 == key)
                return e;
        }
    }
    return 0;
}
