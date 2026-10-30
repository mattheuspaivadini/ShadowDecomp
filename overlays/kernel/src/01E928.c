/* KERNEL.XFF @ 0x01E928 (224 B) - tickProcSound   [MATCH: -G0 -fno-strict-aliasing]
 * Evidence: `lw 0xA28(.data)` is compared with the argument (mode): on a change
 * the volume is re-selected - mode == 0 (the `beqz $s0` path) calls
 * Sg2DspSetMasterVolumeMax(), otherwise Sg2DspSetMasterVolume(0,0,0) and
 * (1,0,0) (two `jal` to the same static with a0 = 0/1, a1 = a2 = 0).  The tick
 * body runs only when `mode == 0 || D_A28 == 0` (the image's `beqz $s0` to the
 * body plus `bnel $v0,$zero` past it, with `sw $s0,0xA28` duplicated into the
 * delay slot): Sg2RemoteSyncStatus() == 0 => Sg2CtrlTickProc(), ++D_A24 (.data
 * +0xA24, load/add/store with the store in the Sg2ExPcmTickProc delay),
 * Sg2ExPcmTickProc(), then the two optional callbacks at .bss+0x7D40C and
 * +0x7D408 (`beql` + `jalr`).  D_A28 = mode happens on every path (both the
 * skip branch's delay slot and the fall-through store).  UNCONFIRMED: the
 * callback/global names, the Sg2DspSetMasterVolume argument meaning.
 * Lever: the early-out must be written as the *positive* condition
 * `if (mode == 0 || D_A28 == 0) { body } D_A28 = mode;` - the negated
 * `if (mode != 0 && D_A28 != 0) { D_A28 = mode; return; }` form gives a longer
 * beqz/b/short-sw sequence (the parked 49/58 draft); and the volume block needs
 * `if (mode != 0) {...} else {...}` (mode==0 first in the image's `beqz`).
 */
extern int Sg2DspSetMasterVolume(int a, int b, int c);
extern void Sg2DspSetMasterVolumeMax(void);
extern int Sg2RemoteSyncStatus(void);
extern void Sg2CtrlTickProc(void);
extern void Sg2ExPcmTickProc(void);
extern int D_kernel_data_A24;
extern int D_kernel_data_A28;
extern void (*D_kernel_bss_7D40C)(void);
extern void (*D_kernel_bss_7D408)(void);

void tickProcSound(int mode)
{
    if (D_kernel_data_A28 != mode) {
        if (mode != 0) {
            Sg2DspSetMasterVolume(0, 0, 0);
            Sg2DspSetMasterVolume(1, 0, 0);
        } else {
            Sg2DspSetMasterVolumeMax();
        }
    }
    if (mode == 0 || D_kernel_data_A28 == 0) {
        if (Sg2RemoteSyncStatus() == 0)
            Sg2CtrlTickProc();
        D_kernel_data_A24++;
        Sg2ExPcmTickProc();
        if (D_kernel_bss_7D40C != 0)
            D_kernel_bss_7D40C();
        if (D_kernel_bss_7D408 != 0)
            D_kernel_bss_7D408();
    }
    D_kernel_data_A28 = mode;
}
