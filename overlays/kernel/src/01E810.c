/* KERNEL.XFF @ 0x01E810 (276 B) - initSound
 * Evidence: clears sg2NicoReverbMode and .bss+0x7D408, then the Sg2 init chain in image order (Ctrl, Remote, Chip, tick mode 60, ExStAdpcm, Dsp, Mod, Sep, Smfp, Slot, Dma, Vab, ExPcm), digital output mode 0x880, effect end addresses 0x1FFFFF/0x1DFFFF, effect type 0x104 and depth 60 on both cores, effect change, master volume max, sndVabInit, sndSepInit, and a sibling Sg2SlotSetOutputMode(.data+0xA20). UNCONFIRMED: the callee arities (a0 = 0 is set before most init calls).
 */
extern int sg2NicoReverbMode;
extern int D_kernel_bss_7D408;
extern int D_kernel_data_0A20;
int Sg2CtrlInit(int a);
int Sg2RemoteInit(int a);
int Sg2ChipInit(int a);
int Sg2CtrlSetTickMode(int mode);
int Sg2ExStAdpcmInit(void);
int Sg2DspInit(int a);
int Sg2ModInit(int a);
int Sg2SepInit(int a);
int Sg2SmfpInit(int a);
int Sg2SlotInit(int a);
int Sg2DmaInit(int a);
int Sg2VabInit(int a);
int Sg2ExPcmInit(int a);
int Sg2ChipSetDigitalOutputMode(int mode);
int Sg2DspEffectSetEndAdr(int core, int value);
int Sg2DspEffectSetType(int core, int type);
int Sg2DspEffectSetDepth(int core, short depth);
int Sg2DspEffectChange(int core);
int Sg2DspSetMasterVolumeMax(void);
void sndVabInit(void);
void sndSepInit(void);
int Sg2SlotSetOutputMode(int mode);

void initSound(void) {
    sg2NicoReverbMode = 0;
    D_kernel_bss_7D408 = 0;
    Sg2CtrlInit(0);
    Sg2RemoteInit(0);
    Sg2ChipInit(0);
    Sg2CtrlSetTickMode(0x3C);
    Sg2ExStAdpcmInit();
    Sg2DspInit(0);
    Sg2ModInit(0);
    Sg2SepInit(0);
    Sg2SmfpInit(0);
    Sg2SlotInit(0);
    Sg2DmaInit(0);
    Sg2VabInit(0);
    Sg2ExPcmInit(0);
    Sg2ChipSetDigitalOutputMode(0x880);
    Sg2DspEffectSetEndAdr(0, 0x1FFFFF);
    Sg2DspEffectSetEndAdr(1, 0x1DFFFF);
    Sg2DspEffectSetType(0, 0x104);
    Sg2DspEffectSetType(1, 0x104);
    Sg2DspEffectSetDepth(0, 0x3C);
    Sg2DspEffectSetDepth(1, 0x3C);
    Sg2DspEffectChange(0);
    Sg2DspEffectChange(1);
    Sg2DspSetMasterVolumeMax();
    sndVabInit();
    sndSepInit();
    Sg2SlotSetOutputMode(D_kernel_data_0A20);
}
