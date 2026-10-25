/* KERNEL.XFF @ 0x01CD88 (24 B) - _isysCreateSubMsgQueue
 * Evidence: +4 = size, +0 = buf, +8 = count, +0xC/+0x10 = 0. UNCONFIRMED: names.
 */
struct SubMsgQueue {
    void *buf;
    int size;
    int count;
    int rd;
    int wr;
};

void _isysCreateSubMsgQueue(struct SubMsgQueue *q, int size, void *buf, int count) {
    q->size = size;
    q->buf = buf;
    q->count = count;
    q->wr = 0;
    q->rd = 0;
}
