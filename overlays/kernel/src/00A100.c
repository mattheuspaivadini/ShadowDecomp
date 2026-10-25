/* KERNEL.XFF @ 0x00A100 (112 B) - isysGetSymdefModuleObjNum
 * Evidence: same walk over the group at .data+0x390; returns the count.
 */
struct GroupEnt {
    void *obj;
};
extern char D_kernel_data_0390[];
struct GroupEnt *isysGroupForFirst(void *group, int flag);
struct GroupEnt *isysGroupForNext(struct GroupEnt *g, int flag);
void isysGroupForExit(void *obj, int flag);

int isysGetSymdefModuleObjNum(void) {
    struct GroupEnt *g;
    void *obj = 0;
    int n = 0;

    for (g = isysGroupForFirst(D_kernel_data_0390, 0); g != 0; g = isysGroupForNext(g, 0)) {
        obj = g->obj;
        n++;
    }
    if (obj != 0) {
        isysGroupForExit(obj, 0);
    }
    return n;
}
