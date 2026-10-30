/* GAMECORE.XFF @ 0x051FA0 (36 B) - set_root_node_data_expression
 * Evidence: `$a0 += 0x34` then `swc1` of the six float arguments into two
 * 0x34-byte blocks: block 0 gets `$f12..$f14` at +4/+8/+0xC, block 1 gets
 * `$f15..$f17` at +0x38/+0x3C/+0x40, and block 1's leading int (+0x34) is
 * zeroed (`sw $zero`). Block 0's leading int is untouched.
 * UNCONFIRMED: the block layout beyond the three floats and the int flag.
 
 */
typedef struct {
    int mode;
    float x;
    float y;
    float z;
    int unk[9];
} ExprNode; /* 0x34 B */

void set_root_node_data_expression(char *root, float ax, float ay, float az,
                                  float bx, float by, float bz) {
    ExprNode *n = (ExprNode *)(root + 0x34);

    n[0].x = ax;
    n[0].y = ay;
    n[0].z = az;
    n[1].mode = 0;
    n[1].x = bx;
    n[1].y = by;
    n[1].z = bz;
}
