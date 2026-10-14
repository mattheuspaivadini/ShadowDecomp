/* asm/cod/010998.s -> func_00110998 @ 0x00110998 (0x38 bytes)
 *   lw    $v0, 0x4($a0)                  ; v0 = p->prev
 *   beqz  $v0, .L001109AC
 *    lw   $v1, 0x0($a0)                  ; v1 = p->next
 *   b     .L001109B4
 *    sw   $v1, 0x0($v0)                  ; p->prev->next = p->next
 * .L001109AC:
 *   lui   $v0, %hi(D_00133930)
 *   sw    $v1, %lo(D_00133930)($v0)      ; D_00133930 = p->next
 * .L001109B4:
 *   beql  $v1, $zero, .L001109C8
 *    sw   $zero, 0x4($a0)                ; p->prev = 0
 *   lw    $v0, 0x4($a0)
 *   sw    $v0, 0x4($v1)                  ; p->next->prev = p->prev
 *   sw    $zero, 0x4($a0)                ; p->prev = 0
 * .L001109C8:
 *   jr    $ra
 *    daddu $v0, $v1, $zero               ; return p->next
 *
 * Unlink `p` from a doubly-linked list whose head is the global D_00133930
 * (next at 0x0, prev at 0x4). D_00133930 is in .data; declared `[]` so it is
 * addressed absolutely (not small data).
 */
struct L010998 {
    struct L010998 *next;   /* 0x00 */
    struct L010998 *prev;   /* 0x04 */
};

extern struct L010998 *D_00133930[];

struct L010998 *func_00110998(struct L010998 *p) {
    struct L010998 *next = p->next;

    if (p->prev)
        p->prev->next = next;
    else
        D_00133930[0] = next;
    if (next)
        next->prev = p->prev;
    p->prev = 0;
    return next;
}
