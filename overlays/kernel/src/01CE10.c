/* KERNEL.XFF @ 0x01CE10 (124 B) - _isysSendSubMsg
 * Evidence: ring buffer {size +0, buf +4, num +8, wr +0xC, rd +0x10}: 0 unless size matches; next = wr + 1 wrapped to 0 at num; when next reaches rd, rd advances (wrapped) - oldest message dropped; memcpy(buf + wr * size, msg, size); wr = next; returns 1. UNCONFIRMED: field names.
 */
struct SubMsgQueue {
    int size;
    char *buf;
    int num;
    int wr;
    int rd;
};
void *memcpy(void *d, const void *s, unsigned int n);

int _isysSendSubMsg(struct SubMsgQueue *q, void *msg, int size) {
    int wr;
    int next;

    if (q->size != size) {
        return 0;
    }
    wr = q->wr;
    next = 0;
    if (wr + 1 < q->num) {
        next = wr + 1;
    }
    if (next == q->rd) {
        q->rd = next + 1 < q->num ? next + 1 : 0;
    }
    memcpy(q->buf + wr * size, msg, size);
    q->wr = next;
    return 1;
}
