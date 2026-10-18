/* asm/cod/012710.s -> sceTtyRead.
 * sceTtyRead; typed tty/queue records with a volatile queue count, char store forces the queue-pointer reloads (Session 23)
 * MATCHED. */
struct Queue { int f00; volatile int count; unsigned char *cur; };
struct Tty { char pad00[0x18]; struct Queue *q; };
extern struct Tty D_0014AFD0;
int func_001123C0(struct Queue *q);

int sceTtyRead(char *dst, int n) {
    int i;

    for (i = 0; i < n; ) {
        while (D_0014AFD0.q->count == 0)
            ;
        dst[i] = *D_0014AFD0.q->cur;
        func_001123C0(D_0014AFD0.q);
        if (dst[i] == '\n' || dst[i] == '\r')
            return i + 1;
        i++;
    }
    return i;
}
