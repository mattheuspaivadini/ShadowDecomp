/* KERNEL.XFF @ 0x009738 (104 B) - isysDumpExecutableModules
 * Evidence: walks the group at .data+0x380 with isysGroupForFirst/isysGroupForNext keeping entry->+0 of the last one, and calls isysGroupForExit(that, 0) when any (the dump body itself is compiled out).
 */
struct GroupEnt {
    void *obj;
};
extern char D_kernel_data_0380[];
struct GroupEnt *isysGroupForFirst(void *group, int flag);
struct GroupEnt *isysGroupForNext(struct GroupEnt *g, int flag);
void isysGroupForExit(void *obj, int flag);

void isysDumpExecutableModules(void) {
    struct GroupEnt *g;
    void *obj = 0;

    for (g = isysGroupForFirst(D_kernel_data_0380, 0); g != 0; g = isysGroupForNext(g, 0)) {
        obj = g->obj;
    }
    if (obj != 0) {
        isysGroupForExit(obj, 0);
    }
}
