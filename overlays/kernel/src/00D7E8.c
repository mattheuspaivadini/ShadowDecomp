/* KERNEL.XFF @ 0x00D7E8 (188 B) - iosUcharColClampAdd
 * Evidence: packs two ARGB quads byte-by-byte ((x & 0xFFFFFF00) | byte,
 * (x & 0xFFFF00FF) | byte<<8, (x & 0xFF00FFFF) | byte<<16, then | 0xFF000000),
 * adds them with `paddub` through two stack quads, copies the packed result with
 * lw/sw into a fourth slot and stores its bytes 0/1/2 to *a/*b/*c.
 * Matching levers (all proved by the diff):
 *  - the two packed operands are live in $11/$12 (not argument registers), so
 *    they are `register ... asm("$11"/"$12")` locals;
 *  - the three drawn byte fields are pre-extracted into locals (v3/v0/v1); that
 *    is what puts each `andi`/`sll` one slot *before* the matching mask `and`
 *    in the shipped schedule (statement order alone leaves 8 words wrong);
 *  - the 4-byte read-back temp is pinned to $3 (the shipped `lw v1,32(sp)` /
 *    `sw v1,48(sp)`); unpinned the allocator always picks a3.
 *  - the 0x40 frame is a real local array, so `addiu sp,sp,-0x40` is the
 *    prologue scheduled down to its first use and the epilogue restores it in
 *    the `jr ra` delay slot.
 * UNCONFIRMED: parameter names; that $11/$12 come set from the caller; that the
 * read-back temp is really $3 in the source (register-pin workaround).
 */
void iosUcharColClampAdd(unsigned char *a, unsigned char *b, unsigned char *c,
                         unsigned int x3, unsigned int x0, unsigned int x1) {
    unsigned int buf[16];
    unsigned int v0, v1, v3;
    register unsigned int r asm("$3");
    register unsigned int p0 asm("$11");
    register unsigned int p1 asm("$12");

    p0 &= 0xFFFFFF00;
    p0 |= a[0];
    v3 = x3 & 0xFF;
    p1 &= 0xFFFFFF00;
    p1 |= v3;
    p0 &= 0xFFFF00FF;
    p0 |= b[0] << 8;
    v0 = (x0 & 0xFF) << 8;
    p1 &= 0xFFFF00FF;
    p1 |= v0;
    p0 &= 0xFF00FFFF;
    p0 |= c[0] << 16;
    v1 = (x1 & 0xFF) << 16;
    p1 &= 0xFF00FFFF;
    p1 |= v1;
    p0 |= 0xFF000000;
    p1 |= 0xFF000000;

    buf[0] = p0;
    buf[4] = p1;
    __asm__ __volatile__(
        "lq $3, 0x10($sp)\n"
        "lq $2, 0x0($sp)\n"
        "paddub $2, $2, $3\n"
        "sq $2, 0x20($sp)\n" : : "m"(buf[0]) : "$2", "$3", "memory");
    r = buf[8];
    buf[12] = r;
    a[0] = ((unsigned char *)&buf[12])[0];
    b[0] = ((unsigned char *)&buf[12])[1];
    c[0] = ((unsigned char *)&buf[12])[2];
}
