/* asm/cod/017A00.s -> func_00117A00 @ 0x00117A00 (0xB0 bytes)
 * A chain of `if (id == CONST)` comparisons, each storing a table address (or a
 * loaded pointer) into *out and returning 1; the default stores 0 and still
 * returns 1. The order of the comparisons (0x8001, 0x8003, 0x8002, 0x8004,
 * 0x8011, 0x8013, 0x8012, 0x8014) matches the emitted `beq` sequence, so this is
 * an if-chain, not a switch.
 *
 * D_00133A68 / D_00133A6C are loaded as 32-bit values (their *contents* are
 * stored); the others are addresses (declared as arrays so they are absolute,
 * not small data).
 */
extern int D_00133A68[];
extern int D_00133A6C[];
extern char D_00133AC0[];
extern char D_00133B40[];
extern char D_00134C10[];
extern char D_00134C40[];
extern char D_00135080[];
extern char D_001355C0[];

int func_00117A00(int id, int *out) {
    if (id == 0x8001) {
        *out = D_00133A68[0];
        return 1;
    }
    if (id == 0x8003) {
        *out = (int)D_00133AC0;
        return 1;
    }
    if (id == 0x8002) {
        *out = (int)D_00133B40;
        return 1;
    }
    if (id == 0x8004) {
        *out = (int)D_00134C10;
        return 1;
    }
    if (id == 0x8011) {
        *out = D_00133A6C[0];
        return 1;
    }
    if (id == 0x8013) {
        *out = (int)D_00134C40;
        return 1;
    }
    if (id == 0x8012) {
        *out = (int)D_00135080;
        return 1;
    }
    if (id == 0x8014) {
        *out = (int)D_001355C0;
        return 1;
    }
    *out = 0;
    return 1;
}
