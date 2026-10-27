/* KERNEL.XFF @ 0x0073B0 (64 B) - Init_Player
 * Evidence: four word stores into the player slot (see iosPadInit): 0, a .text handler (.text+0x7738, or .text+0x7730 when the first is null), .text+0x7780 and .bss+0xD9E8.
 * The three addresses are hoisted into locals before the test (that is what schedules them ahead of the branch). UNCONFIRMED: field names.
 */
/* UNCONFIRMED: field and handler names; the handlers are stripped statics. */
struct Player {
    int state;
    void (*f04)(void);
    void (*f08)(void);
    void *f0c;
};
static void func_7730(void);
static void func_7738(void);
static void func_7780(void);
extern char D_kernel_bss_D9E8[];

void Init_Player(struct Player *p) {
    void (*a)(void) = func_7738;
    void (*b)(void) = func_7780;
    void *c = D_kernel_bss_D9E8;

    p->state = 0;
    if (a)
        p->f04 = a;
    else
        p->f04 = func_7730;
    p->f08 = b;
    p->f0c = c;
}
