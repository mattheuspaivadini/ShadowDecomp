/* GAMECORE.XFF @ 0x12ACF0 (44 B) - getEventScriptObjWorkSize
 * Evidence: stores $ra, 0x0($sp), $v1, 0x10($v0); loads $v1, 0x0($a0), $ra, 0x0($sp); relocs <.data>; calls GetScriptObjWorkSize; frame
 * UNCONFIRMED: D_kernel_data_2020 is modelled as a work struct whose word at
 * 0x10 receives the caller's value before the size query.
 
 */
int GetScriptObjWorkSize(void *work);

struct EventScriptObjWork {
    char pad00[0x10];
    int size;           /* +0x10 */
};

extern struct EventScriptObjWork D_kernel_data_2020;

int getEventScriptObjWorkSize(int *p) {
    D_kernel_data_2020.size = *p;
    return GetScriptObjWorkSize(&D_kernel_data_2020);
}
