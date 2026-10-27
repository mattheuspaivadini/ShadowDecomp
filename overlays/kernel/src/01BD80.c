/* KERNEL.XFF @ 0x01BD80 (56 B) - init_letter_manager
 * Evidence: init_letter_type_store(); .data+0x804 = &rootPtn; .bss+0x7C210 = create_letter_post(). UNCONFIRMED: object names.
 */
extern char rootPtn[];
extern void *D_kernel_data_0804;
extern void *D_kernel_bss_7C210;
void init_letter_type_store(void);
void *create_letter_post(void);

void init_letter_manager(void) {
    init_letter_type_store();
    D_kernel_data_0804 = rootPtn;
    D_kernel_bss_7C210 = create_letter_post();
}
