/* KERNEL.XFF @ 0x02B730 (200 B) - Sg2SlotEnvTbl
 * Evidence: clears the output (first byte of the empty string at .rodata+0x2DC0), then for the 48 slots sprintf's Sg2RemoteGetSlotReleaseLv(i) with .rodata+0x2DC8, appends .rodata+0x2DD0 after every 12th slot and strcat's the piece to the output. UNCONFIRMED: names.
 */
extern char D_kernel_rodata_2DC0[];
extern char D_kernel_rodata_2DC8[];
extern char D_kernel_rodata_2DD0[];
int Sg2RemoteGetSlotReleaseLv(int i);
int sprintf(char *buf, const char *fmt, ...);
char *strcat(char *d, const char *s);

void Sg2SlotEnvTbl(char *out) {
    char buf[16];
    int i;

    out[0] = D_kernel_rodata_2DC0[0];
    for (i = 0; i < 48; i++) {
        sprintf(buf, D_kernel_rodata_2DC8, Sg2RemoteGetSlotReleaseLv(i));
        if ((i + 1) % 12 == 0) {
            strcat(buf, D_kernel_rodata_2DD0);
        }
        strcat(out, buf);
    }
}
