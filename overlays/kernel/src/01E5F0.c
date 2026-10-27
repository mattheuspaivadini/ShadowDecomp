/* KERNEL.XFF @ 0x01E5F0 (20 B) - sndVabDelete
 * Evidence: clears bit 0 of word 0. UNCONFIRMED: flag name.
 */
struct SndVab {
    unsigned int flags;
    int id;
    int unk8;
    void *hd;
    void *bd;
    char pad[8];
};

void sndVabDelete(struct SndVab *v) {
    v->flags &= ~1;
}
