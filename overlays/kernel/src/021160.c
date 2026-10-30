/* KERNEL.XFF @ 0x021160 (296 B) - func_021160 (static, no symbol in the shipped .symtab)
 * STATUS: MATCHING [-G0 -fno-strict-aliasing] (74/74 words)
 * Evidence: runs only in state 0x10 (+0); cur = func_020CC8(p, 0) compared with the ring
 * position +0x2D4; queues up to two ring segments through func_020DB0(p, 1, base +0x230 + pos, n),
 * wrap-around against +0x234/+0x244/+0x248; next state 0x20 (+0x34 set, plus func_020DB0(p, 2,
 * +0x240, 0) unless +8 bit 0) or 0x40; finally +0x2D4 = (+0x2D4 < cur) ? cur : 0.
 * Lever: the early "n2 < 0" exit is a `goto out` to the single shared tail. Writing the tail twice
 * gives cur one more set of references, so global-alloc gives it $s2 instead of $s3 (10/74 words).
 * Levers tried (session 76 worker b): declaration order, renames, register-asm pins of s1-s3
 * (size 292/308), -fno-schedule-insns2 (20/74), -fno-gcse (no change).
 * UNCONFIRMED: function name, field names/meanings, prototypes of func_020CC8 / func_020DB0.
 */
struct St { int state; int p4; unsigned int f8; char p0C[0x28]; int f34; char p38[0x1F8];
  int f230; int f234; char p238[8]; int f240; int f244; int f248; char p24C[0x88]; int f2D4; };
int func_020CC8(struct St *p, int a);
void func_020DB0(struct St *p, int a1, int a2, int a3);

void func_021160(struct St *p) {
    int n1, n2, cur, pos, wr, lim;
    if (p->state != 0x10) return;
    cur = func_020CC8(p, 0);
    pos = p->f2D4;
    if (cur == pos) return;
    n1 = (pos < cur) ? cur - pos : p->f234 - pos;
    wr = p->f248;
    lim = p->f244;
    n2 = wr + n1 - lim;
    if (n2 >= 0) n1 = lim - wr;
    if (n1 > 0) func_020DB0(p, 1, p->f230 + pos, n1);
    if (n2 < 0) goto out;
    if (p->f34) {
        p->state = 0x20;
        if (!(p->f8 & 1)) func_020DB0(p, 2, p->f240, 0);
        func_020DB0(p, 1, p->f230 + p->f2D4 + n1, n2);
    } else {
        p->state = 0x40;
    }
out:
    p->f2D4 = (p->f2D4 < cur) ? cur : 0;
}
