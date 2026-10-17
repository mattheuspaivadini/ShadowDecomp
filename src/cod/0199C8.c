/* asm/cod/0199C8.s -> sceSifMExitRpc.
 * SCE SDK, cc=29 (callee return types / statement shape from the image)
 * MATCHED. */
extern int D_00135618[];    /* .data 0x00135618: array => lui/%lo, not %gp_rel */

int sceSifRemoveCmdHandler(int index);
void sceSifRemoveRebootNotifyHandler(int index);

void sceSifMExitRpc(void) {
    D_00135618[0] = 0;
    sceSifRemoveCmdHandler((int)0x80000018);
    sceSifRemoveRebootNotifyHandler((int)0x80000014);
}
