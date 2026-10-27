/* KERNEL.XFF @ 0x009910 (104 B) - isysRemoveModuleObjGroup
 * Evidence: removes the object from the group at .data+0x390 when hdr->+0x24 is set and from .data+0x388 when hdr->+0x1C is set (_isysDeleteGroup(obj, group, 0)). UNCONFIRMED: field meanings.
 */
struct XffHdr {
    char pad[0x1C];
    int nsym;
    char pad2[4];
    int nexec;
};
struct XffObj {
    char pad[0x1C];
    struct XffHdr *hdr;
};
extern char D_kernel_data_0388[];
extern char D_kernel_data_0390[];
void _isysDeleteGroup(void *obj, void *group, int flag);

void isysRemoveModuleObjGroup(struct XffObj *obj) {
    if (obj->hdr->nexec) {
        _isysDeleteGroup(obj, D_kernel_data_0390, 0);
    }
    if (obj->hdr->nsym) {
        _isysDeleteGroup(obj, D_kernel_data_0388, 0);
    }
}
