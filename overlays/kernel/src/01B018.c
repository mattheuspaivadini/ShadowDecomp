/* KERNEL.XFF @ 0x01B018 (48 B) - isysGetObjIdentifierByObj
 * Evidence: object type byte +8 indexes the 37-entry identifier table at .data+0x6A0; out-of-range types read entry 0 (result kept in a variable). UNCONFIRMED: names.
 */
struct IsysObj { char pad0[8]; unsigned char type; };
extern int D_kernel_data_06A0[];
int isysGetObjIdentifierByObj(struct IsysObj *o) {
    int t = o->type;
    int r;
    if (t < 37) r = D_kernel_data_06A0[t]; else r = D_kernel_data_06A0[0];
    return r;
}
