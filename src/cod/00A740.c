/* asm/cod/00A740.s -> func_0010A740.
 * void one-shot CreateSema; ee_sema_t (Session 23)
 * MATCHED. */
typedef struct { int count; int max_count; int init_count; int wait_threads; unsigned int attr; void *option; } ee_sema_t;
extern int D_0013231C __attribute__((section(".data")));
extern char D_00137F68[];
int CreateSema(ee_sema_t *s);

void func_0010A740(void) {
    ee_sema_t s;
    if (D_0013231C != -1) return;
    s.init_count = 1; s.max_count = 1; s.option = D_00137F68;
    D_0013231C = CreateSema(&s);
}
