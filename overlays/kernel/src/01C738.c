/* KERNEL.XFF @ 0x01C738 (24 B) - iosGetDataSizeOfFont
 * Evidence: returns the word at .data+0x808 + id*4. UNCONFIRMED: table name.
 */
extern int D_kernel_data_0808[];

int iosGetDataSizeOfFont(int id) {
    return D_kernel_data_0808[id];
}
