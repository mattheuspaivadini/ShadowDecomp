/* MANAGER.XFF @ 0x0058C8 (8 B) - GAMEUTIL_get_move_radi_from_pitch1_to_pitch2
 * Evidence: `jr $ra` with `460c6801` in the delay slot = `sub.s $f0,$f13,$f12`,
 * i.e. the difference of the two float arguments (first in $f12, second in
 * $f13) returned in $f0. The Ghidra EE dossier agrees:
 *   float f(float pitch1, float pitch2) { return pitch2 - pitch1; }
 * Note the operand order: the image computes pitch2 - pitch1, not the reverse.
 */
float GAMEUTIL_get_move_radi_from_pitch1_to_pitch2(float pitch1, float pitch2) {
    return pitch2 - pitch1;
}
