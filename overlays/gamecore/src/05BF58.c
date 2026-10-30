/* GAMECORE.XFF @ 0x05BF58 (60 B) - nico_hydeHorseByNearClip
 * Evidence: `SH_PlayerHydeObjListHorseHydeList+0xC` null-tested, then
 * `parseHydeObject($a0, list+0x10, list+0xC, $a1, 7)` and `return 0`.
 * UNCONFIRMED: the hyde list layout and parseHydeObject's parameters.
 
 */
struct HydeObjList {
    char pad[0xC];
    void *obj;
    void *param;
};

extern struct HydeObjList SH_PlayerHydeObjListHorseHydeList;
int parseHydeObject(void *obj, void *param, void *target, int mode, int kind);

int nico_hydeHorseByNearClip(void *obj, int mode) {
    if (SH_PlayerHydeObjListHorseHydeList.obj != 0)
        parseHydeObject(obj, SH_PlayerHydeObjListHorseHydeList.param,
                        SH_PlayerHydeObjListHorseHydeList.obj, mode, 7);
    return 0;
}
