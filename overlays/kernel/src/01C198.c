/* KERNEL.XFF @ 0x01C198 (52 B) - init_letter_type_store
 * Evidence: clears the 20 slots at .bss+0x7C218 from index 19 down (R5900 short-loop nops).
 */
extern void *D_kernel_bss_7C218[20];

void init_letter_type_store(void) {
    int i;

    for (i = 19; i >= 0; i--) {
        D_kernel_bss_7C218[i] = 0;
    }
}
