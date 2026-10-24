/* MANAGER.XFF @ 0x0CC8E8 (20 B) - RelocateTwoWayLinkHeader
 * Evidence:
 *   lw v0,0x4(a0)                 ; v0 = *(void **)(p + 4)
 *   bnel v0,zero, jr              ; if (v0 != 0) { execute the delay slot }
 *   sw a0,0x0(v0)                 ;   *(void **)v0 = p
 *   jr $ra
 * A two-way link header whose back-pointer at +0x4 is patched to point at the
 * header itself. UNCONFIRMED field names; the two offsets are the evidence.
 */
void RelocateTwoWayLinkHeader(unsigned char *p) {
    unsigned char *peer = *(unsigned char **)(p + 0x4);
    if (peer != 0)
        *(void **)peer = p;
}
