/* KERNEL.XFF @ 0x01CDA0 (108 B) - _isysRecvSubMsg
 * Evidence: returns 0 on an element-size mismatch (+0) or an empty ring (rd +0x10 == wr +0xC); otherwise memcpy(dst, buf (+4) + rd * size, size), rd advances modulo count (+8), returns 1. UNCONFIRMED: names (these offsets also fix the layout behind _isysCreateSubMsgQueue).
 */
struct SubMsgQueue {
    int elemSize;
    char *buf;
    int count;
    int wr;
    int rd;
};
void *memcpy(void *d, const void *s, unsigned int n);

int _isysRecvSubMsg(struct SubMsgQueue *q, void *dst, int size) {
    int next;

    if (q->elemSize != size) {
        return 0;
    }
    if (q->rd == q->wr) {
        return 0;
    }
    memcpy(dst, q->buf + q->rd * q->elemSize, size);
    next = q->rd + 1;
    if (next >= q->count) {
        next = 0;
    }
    q->rd = next;
    return 1;
}
