/* GAMECORE.XFF @ 0x044A00 (44 B) - NICO_is_quake_attack_hit
 * Evidence: frame 0x20, a 16-byte stack buffer at `$sp` whose first 8 bytes are
 * zeroed, `$a1 = $a0` (the object), `$a0 = $sp`; then the callee's return value
 * is compared with 1 (`xori 1` + `sltiu 1`).
 * UNCONFIRMED: the buffer type and the callee prototype.
 
 */
typedef struct {
    long a;
    long b;
} Attr16;

int GAMEUTIL_get_parent_collision_attribute(Attr16 *out, int obj);

int NICO_is_quake_attack_hit(int obj) {
    Attr16 attr;

    attr.a = 0;
    return GAMEUTIL_get_parent_collision_attribute(&attr, obj) == 1;
}
