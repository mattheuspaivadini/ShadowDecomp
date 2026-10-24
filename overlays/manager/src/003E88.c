/* MANAGER.XFF @ 0x003E88 (20 B) - GAMEUTIL_get_parent_collision_attribute
 * Evidence: 0x10-byte frame saving $ra, then `ld $ra` + sibling `j`
 * GetParentCharColAttr with the frame released in the delay slot: the argument
 * is forwarded unchanged and the callee's result is returned.
 */
int GetParentCharColAttr(int obj);

int GAMEUTIL_get_parent_collision_attribute(int obj) {
    return GetParentCharColAttr(obj);
}
