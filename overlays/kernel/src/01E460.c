/* KERNEL.XFF @ 0x01E460 (80 B) - sndSepStopTypeAll
 * Evidence: for every used 0x70-byte SEP slot (.bss+0x7C3D0, 32 slots) whose 3-bit type (bits 34..36 of the 64-bit word at +8) equals type, sets bit 32 (stop). UNCONFIRMED: bitfield names.
 */
struct SepSlot { int used; int unk4; unsigned long unk8 : 32; unsigned long stop : 1; unsigned long unk8b : 1; unsigned int type : 3; char pad[0x60]; };
extern struct SepSlot D_kernel_bss_7C3D0[32];
void sndSepStopTypeAll(int type) {
 int i;
 for (i = 0; i < 32; i++) {
 if (D_kernel_bss_7C3D0[i].used && D_kernel_bss_7C3D0[i].type == type) D_kernel_bss_7C3D0[i].stop = 1;
 }
}
