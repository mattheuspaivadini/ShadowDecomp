/* GAMECORE.XFF @ 0x030B90 (60 B) - bgmChkStandbyComplete
 * Evidence: `$a1 = $a0`, `lw 0x8($a1)` compared with 1 returning 0 in the
 * delay slot, else `lw 0x0($a1)` tail-called into adpcmOpenChkComplete.
 * UNCONFIRMED: the work layout.
 
 */
struct BgmWork {
    void *handle;
    char pad[4];
    int state;
};

int adpcmOpenChkComplete(void *handle);

int bgmChkStandbyComplete(struct BgmWork *work) {
    if (work->state == 1)
        return 0;
    return adpcmOpenChkComplete(work->handle);
}
