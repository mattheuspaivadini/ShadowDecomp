/* KERNEL.XFF @ 0x0074A0 (300 B) - Shock_Decode
 * Evidence: sums the static .text+0x6DF0 and ORs the static .text+0x6B60 over every request of the list (next +0x34) for the current port (.data+0x368 -> +8), stores min(sum, 255) and the bits, then unlinks each finished request (byte +0 clear; prev +0x30 / next +0x34) and hands it to the list's done callback (+8, argument +0xC). UNCONFIRMED: names.
 */
struct ShockWork {
    unsigned char active;
    char pad1[0x2F];
    struct ShockWork *prev;
    struct ShockWork *next;
};
struct ShockList {
    struct ShockWork *head;
    int unk4;
    void (*done)(struct ShockWork *w, int arg);
    int arg;
};
struct ShockTbl {
    int num;
    void *set;
    int port;
};
extern struct ShockTbl *D_kernel_data_0368;
int func_006DF0(struct ShockWork *w, int port);
int func_006B60(struct ShockWork *w, int port);

void Shock_Decode(struct ShockList *list, unsigned char *dir, unsigned char *amp) {
    int sum = 0;
    int bits = 0;
    struct ShockWork *w;
    struct ShockWork *p;
    struct ShockWork *next;

    if (list == 0) {
        return;
    }
    for (w = list->head; w != 0; w = w->next) {
        sum += func_006DF0(w, D_kernel_data_0368->port);
        bits |= func_006B60(w, D_kernel_data_0368->port);
    }
    if (sum > 255) {
        sum = 255;
    }
    *amp = sum;
    *dir = bits;
    p = list->head;
    while (p != 0) {
        if (p->active == 0) {
            if (p->prev != 0) {
                p->prev->next = p->next;
            } else {
                list->head = p->next;
            }
            next = p->next;
            if (next != 0) {
                next->prev = p->prev;
                next = p->next;
            }
            if (list->done != 0) {
                list->done(p, list->arg);
            }
            p = next;
        } else {
            p = p->next;
        }
    }
}
