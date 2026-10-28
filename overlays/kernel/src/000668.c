/* KERNEL.XFF @ 0x000668 (220 B) - iosCdStInit
 * Evidence: .bss+0x18 = strncmp(.rodata+0x30, name, 6) == 0, three 64-bit stream positions at .bss+0x8040/48/50 = -1 (one chained assignment); for CD names sceCdSearchFile (a failure hits an explicit break 0) stores the LSN at .bss+0x14 and strcpy's the name to .bss+0x8058, otherwise LoaderSysFOpen(name, 1, 0x1FF) at .bss+0x1C with iosJumpRecoverPoint(.rodata+0x38, name) on error. UNCONFIRMED: names.
 */
typedef struct {
    unsigned int lsn;
    unsigned int size;
    char name[16];
    unsigned char date[8];
    unsigned int flag;
} sceCdlFILE;
extern char D_kernel_rodata_0030[];
extern char D_kernel_rodata_0038[];
extern int D_kernel_bss_0014;
extern int D_kernel_bss_0018;
extern int D_kernel_bss_001C;
extern long D_kernel_bss_8040;
extern long D_kernel_bss_8048;
extern long D_kernel_bss_8050;
extern char D_kernel_bss_8058[];
int strncmp(const char *a, const char *b, unsigned int n);
char *strcpy(char *d, const char *s);
int sceCdSearchFile(sceCdlFILE *fp, const char *name);
int LoaderSysFOpen(const char *name, int flag, int mode);
void iosJumpRecoverPoint(const char *fmt, ...);

void iosCdStInit(char *name) {
    sceCdlFILE file;

    D_kernel_bss_0018 = strncmp(D_kernel_rodata_0030, name, 6) == 0;
    D_kernel_bss_8050 = D_kernel_bss_8048 = D_kernel_bss_8040 = -1;
    if (D_kernel_bss_0018 == 0) {
        if (!sceCdSearchFile(&file, name)) {
            __asm__ __volatile__("break 0");
        }
        D_kernel_bss_0014 = file.lsn;
        strcpy(D_kernel_bss_8058, name);
    } else {
        D_kernel_bss_001C = LoaderSysFOpen(name, 1, 0x1FF);
        if (D_kernel_bss_001C < 0) {
            iosJumpRecoverPoint(D_kernel_rodata_0038, name);
        }
    }
}
