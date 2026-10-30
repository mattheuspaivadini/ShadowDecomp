/* GAMECORE.XFF @ 0x07C1D8 (52 B) - SCRPlayerRotateStop
 * Evidence: `jal GetLayoutClass`, `lw $v1,0x19C($v0)`, then `lwc1 $f0,0x50`
 * multiplied by 0x3F000000 (0.5f) and stored back.
 * UNCONFIRMED: the layout field meanings.
 
 */
struct LayoutClass {
    char pad[0x19C];
    struct RootObj *root;
};

struct RootObj {
    char pad[0x50];
    float rotateSpeed;
};

struct LayoutClass *GetLayoutClass(void);

void SCRPlayerRotateStop(void) {
    struct RootObj *root = GetLayoutClass()->root;

    root->rotateSpeed *= 0.5f;
}
