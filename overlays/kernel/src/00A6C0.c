/* KERNEL.XFF @ 0x00A6C0 (76 B) - isysWriteLinkerScriptFile
 * Evidence: 1 KiB stack buffer filled by iosSPrintf(buf, .rodata+0xBC8, obj->+0x38); the header pointer obj->+0x1C is loaded before that call (kept in $s0) and passed with buf and printf to OutputLinkerScriptFile. UNCONFIRMED: field names.
 */
struct XffObj {
    char pad[0x1C];
    void *hdr;
    char pad2[0x18];
    const char *name;
};
extern char D_kernel_rodata_0BC8[];
void iosSPrintf(char *buf, const char *fmt, ...);
void OutputLinkerScriptFile(void *hdr, const char *path, int (*print)(const char *, ...));
int printf(const char *fmt, ...);

void isysWriteLinkerScriptFile(struct XffObj *obj) {
    char path[1024];
    void *hdr = obj->hdr;

    iosSPrintf(path, D_kernel_rodata_0BC8, obj->name);
    OutputLinkerScriptFile(hdr, path, printf);
}
