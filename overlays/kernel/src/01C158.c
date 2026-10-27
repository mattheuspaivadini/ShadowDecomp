/* KERNEL.XFF @ 0x01C158 (60 B) - entry_new_letter_type
 * Evidence: first NULL slot of the 20-pointer store at .bss+0x7C218 takes the type, returns its index or -1.
 */
extern void *D_kernel_bss_7C218[20];

int entry_new_letter_type(void *type) {
    int i;

    for (i = 0; i < 20; i++) {
        if (D_kernel_bss_7C218[i] == 0) {
            D_kernel_bss_7C218[i] = type;
            return i;
        }
    }
    return -1;
}
