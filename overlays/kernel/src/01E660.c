/* KERNEL.XFF @ 0x01E660 (24 B) - sndVabHDClose
 * Evidence: sibling Sg2VabClose(word +4).
 */
struct SndVab {
    unsigned int flags;
    int id;
    int unk8;
    void *hd;
    void *bd;
    char pad[8];
};
int Sg2VabClose(int id);

void sndVabHDClose(struct SndVab *v) {
    Sg2VabClose(v->id);
}
