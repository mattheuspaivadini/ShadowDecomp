/* GAMECORE.XFF @ 0x07B880 (60 B) - nico_hydePlayerByNearClip
 * Evidence: `SH_PlayerHydeObjListPlayerHydeList+0xC` null-tested, then
 * `parseHydeObject($a0, list+0x10, list+0xC, $a1, 7)` and `return 0`.
 * Byte-identical to nico_hydeHorseByNearClip (05BF58) apart from the list
 * symbol.
 * UNCONFIRMED: the hyde list layout and parseHydeObject's parameters.
 
 */
struct HydeObjList {
    char pad[0xC];
    void *obj;
    void *param;
};

extern struct HydeObjList SH_PlayerHydeObjListPlayerHydeList;
int parseHydeObject(void *obj, void *param, void *target, int mode, int kind);

int nico_hydePlayerByNearClip(void *obj, int mode) {
    if (SH_PlayerHydeObjListPlayerHydeList.obj != 0)
        parseHydeObject(obj, SH_PlayerHydeObjListPlayerHydeList.param,
                        SH_PlayerHydeObjListPlayerHydeList.obj, mode, 7);
    return 0;
}
