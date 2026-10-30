/* GAMECORE.XFF @ 0x05D178 (60 B) - nico_setHorseBridleLeftLong
 * Evidence: `lw 0x4248($v0)` handle, null-tested, tail
 * `j nico_setHorseBridleType` with `$a1 = 1`.
 * UNCONFIRMED: the AI work field at +0x4248.
 
 */
struct SCRCharaAIWork {
    char pad[0x4248];
    int handle;
};

struct SCRCharaAIWork *GetSCRCharaAIWorkPtr(void);
void nico_setHorseBridleType(int handle, int type);

void nico_setHorseBridleLeftLong(void) {
    int handle = GetSCRCharaAIWorkPtr()->handle;

    if (handle != 0)
        nico_setHorseBridleType(handle, 1);
}
