/* KERNEL.XFF @ 0x009B08 (76 B) - isysLaunchExecModule
 * Evidence: the static at .text+0x8E60 prepares the module, its entry (obj->+0x1C->+0x10) is read before FlushCache(0) and FlushCache(2) (data writeback + icache invalidate), then called with the object (jalr $s1). UNCONFIRMED: struct layout names.
 */
struct XffHdr {
    char pad[0x10];
    void (*entry)(void *obj);
};
struct XffObj {
    char pad[0x1C];
    struct XffHdr *hdr;
};
void func_008E60(struct XffObj *obj);
void FlushCache(int op);

void isysLaunchExecModule(struct XffObj *obj) {
    void (*entry)(void *);

    func_008E60(obj);
    entry = obj->hdr->entry;
    FlushCache(0);
    FlushCache(2);
    entry(obj);
}
