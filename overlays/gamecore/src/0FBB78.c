/* GAMECORE.XFF @ 0x0FBB78 (8 B) - getUserPathExMode
 * Evidence: `jr $ra` with `8c823c60` in the delay slot.
 * Name is authoritative (GAMECORE.XFF .symtab, STT_FUNC).
 */
int getUserPathExMode(unsigned char *p) {
    return *(int *)(p + 0x3c60);
}
