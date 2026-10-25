/* KERNEL.XFF @ 0x003BC0 (16 B) - iosGetMallocRootPtnRemainSize
 * Evidence: `lw` of .data+0xB0 scaled by 4 (`sll 2`) in the delay slot.
 * UNCONFIRMED: the object name (the root partition remaining size in 4-byte units).
 */
extern int D_kernel_data_00B0;
int iosGetMallocRootPtnRemainSize(void) { return D_kernel_data_00B0 << 2; }
