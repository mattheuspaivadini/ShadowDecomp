/* GAMECORE.XFF @ 0x014528 (20 B) - setTreeId
 * Evidence: two separate lui: .data+0x778 = a0, .data+0x77C = 0
 * UNCONFIRMED: none
 */
extern int D_kernel_data_0778[];
extern int D_kernel_data_077C[];

void setTreeId(int id) {
    D_kernel_data_0778[0] = id;
    D_kernel_data_077C[0] = 0;
}
