/* KERNEL.XFF @ 0x01C1D0 (48 B) - get_letter_type
 * Evidence: returns slot[id] for id < 20 (unsigned), else NULL.
 */
extern void *D_kernel_bss_7C218[20];

void *get_letter_type(unsigned int id) {
    if (id < 20) {
        return D_kernel_bss_7C218[id];
    }
    return 0;
}
