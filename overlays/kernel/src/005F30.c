/* KERNEL.XFF @ 0x005F30 (84 B) - iosPadInit
 * Evidence: Init_Shock(); Shock_SetShockVoiceSet(0, ShockVoiceSetCommon); Init_Controler on .data+0x2DC and +0x354, Init_Player on .data+0x2C8 and +0x340: two 0x78-byte slots of {player 0x14, controler 0x64} at .data+0x2C8. UNCONFIRMED: slot layout names.
 */
struct PadSlot {
    char player[0x14];
    char controler[0x64];
};
extern struct PadSlot D_kernel_data_02C8[2];
extern void *ShockVoiceSetCommon;
void Init_Shock(void);
int Shock_SetShockVoiceSet(unsigned int index, void *set);
void Init_Controler(void *c);
void Init_Player(void *p);

void iosPadInit(void) {
    Init_Shock();
    Shock_SetShockVoiceSet(0, ShockVoiceSetCommon);
    Init_Controler(D_kernel_data_02C8[0].controler);
    Init_Controler(D_kernel_data_02C8[1].controler);
    Init_Player(D_kernel_data_02C8[0].player);
    Init_Player(D_kernel_data_02C8[1].player);
}
