/* asm/cod/001B20.s -> _checkExistString.
 * _checkExistString; plain indexed for loop over the NULL-terminated list (Session 22)
 * MATCHED. */
int func_00128E6C(char *record, const char *module);

int _checkExistString(const char *a0, char **a1) {
    int i;
    for (i = 0; a1[i] != 0; i++) {
        if (func_00128E6C(a1[i], a0) == 0)
            return 1;
    }
    return 0;
}
