/* KERNEL.XFF @ 0x00A090 (112 B) - isysGetUndefModuleObjNum
 * Evidence: counts the entries of the group at .data+0x388 with isysGroupForFirst/Next, remembering entry->+0 of the last one and passing it to isysGroupForExit(obj, 0) when any; returns the count.
 */
struct GroupEnt {
    void *obj;
};
extern char D_kernel_data_0388[];
struct GroupEnt *isysGroupForFirst(void *group, int flag);
struct GroupEnt *isysGroupForNext(struct GroupEnt *g, int flag);
void isysGroupForExit(void *obj, int flag);

int isysGetUndefModuleObjNum(void) {
    struct GroupEnt *g;
    void *obj = 0;
    int n = 0;

    for (g = isysGroupForFirst(D_kernel_data_0388, 0); g != 0; g = isysGroupForNext(g, 0)) {
        obj = g->obj;
        n++;
    }
    if (obj != 0) {
        isysGroupForExit(obj, 0);
    }
    return n;
}
