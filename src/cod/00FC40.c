/* asm/cod/00FC40.s -> func_0010FC40.
 * bounded word search; result null unless below end (Session 19)
 * MATCHED. */
int *func_0010FC40(int *p, int *end, int key) {
    while (*p != key && p < end)
        p++;
    return p < end ? p : 0;
}
