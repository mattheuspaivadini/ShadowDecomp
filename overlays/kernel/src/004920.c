/* KERNEL.XFF @ 0x004920 (108 B) - iosCreateMsgQueue
 * Evidence: memset(q, 0, 0x1C); a non-NULL buffer with size > 0 is cleared too (size * 8 bytes); then q->buf (+0) and q->size (+4). UNCONFIRMED: queue layout.
 */
struct IosMsgQueue {
    void *buf;
    int size;
    char pad[0x14];
};
void *memset(void *p, int c, unsigned int n);

void iosCreateMsgQueue(struct IosMsgQueue *q, void *buf, int size) {
    memset(q, 0, sizeof(*q));
    if (buf != 0 && size > 0) {
        memset(buf, 0, size * 8);
    }
    q->buf = buf;
    q->size = size;
}
