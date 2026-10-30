/* GAMECORE.XFF @ 0x091A00 (52 B) - player_resetHangPointWork
 * Evidence: the word at +0x0 is tested and the routine returns when it is
 * clear; `$a0 = $v1 + 0x50` is computed in the `beqz` delay slot, then the
 * word is zeroed and a sibling `j` goes to `DeleteTwoWayLink`.
 * UNCONFIRMED: the work struct layout and the callee prototype.
 
 */
struct HangPointWork {
    int linked;
    char pad[0x4C];
    char link[0x50];
};

void DeleteTwoWayLink(void *link);

void player_resetHangPointWork(struct HangPointWork *work) {
    if (work->linked != 0) {
        work->linked = 0;
        DeleteTwoWayLink(work->link);
    }
}
