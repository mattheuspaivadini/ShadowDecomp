/* sceCdChgSys @ 0x00118358 (0x24 bytes): prints and returns 2.
 * Named from the "sceCdChgSys: Illegal_function_call" string (Phase 5). */
int scePrintf(const char *msg);

extern char D_00138A98[];

int sceCdChgSys(int a0, int a1) {
    scePrintf(D_00138A98);
    return 2;
}
