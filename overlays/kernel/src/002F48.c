/* KERNEL.XFF @ 0x002F48 (168 B) - func_002F48 (static, no symbol in the shipped .symtab)
 * Evidence: fprintf-like: vsprintf into a 0x100-byte stack buffer (varargs save area), LoaderSysPrintf(.rodata+0x270, buf) for fd < 0 else LoaderSysFWrite(fd, buf, strlen(buf)); returns strlen(buf). UNCONFIRMED: name; Ghidra FUN_00202f48 (0xA8 bytes with the delay slot).
 */
#include <stdarg.h>

extern char D_kernel_rodata_0270[];
int vsprintf(char *buf, const char *fmt, va_list ap);
int LoaderSysPrintf(const char *fmt, ...);
int LoaderSysFWrite(int fd, void *buf, int size);
unsigned int strlen(const char *s);

int func_002F48(int fd, const char *fmt, ...) {
    char buf[0x100];
    va_list ap;

    va_start(ap, fmt);
    vsprintf(buf, fmt, ap);
    if (fd < 0) {
        LoaderSysPrintf(D_kernel_rodata_0270, buf);
    } else {
        LoaderSysFWrite(fd, buf, strlen(buf));
    }
    return strlen(buf);
}
