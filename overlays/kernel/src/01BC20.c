/* KERNEL.XFF @ 0x01BC20 (352 B) - doit_letter_manager
 * Evidence: opens the letter post (.bss+0x7C210) and for each pending letter: reference type mode 0 delivers to the single receiver object (isysGetLetterObj of get_letter_receiver_obj_group) through the static .text+0x1BDF8, otherwise walks the receiver group and delivers to every object until a mode-1 type is accepted (result 1); a missing letter object hits break 0. Ends with discard_all_letter_in_post and close_letter_post (tail call). UNCONFIRMED: names.
 */
struct LetterPost;
struct Letter;
struct IsysObj;
struct LetterRefType {
    int mode;
};
struct GroupEnt {
    struct IsysObj *obj;
};
extern struct LetterPost *D_kernel_bss_7C210;
void open_letter_post(struct LetterPost *post);
void close_letter_post(struct LetterPost *post);
void discard_all_letter_in_post(struct LetterPost *post);
struct Letter *get_next_letter_in_post(struct LetterPost *post);
struct LetterRefType *get_reference_letter_type(struct Letter *l);
void *get_letter_receiver_obj_group(struct Letter *l);
void *isysGetLetterObj(void *obj);
int func_01BDF8(void *obj, struct Letter *l, struct LetterRefType *type);
struct GroupEnt *isysGroupForFirst(void *group, int arg);
struct GroupEnt *isysGroupForNext(struct GroupEnt *g, int arg);
void isysGroupForExit(struct IsysObj *obj, int arg);

void doit_letter_manager(void) {
    struct Letter *l;
    struct LetterRefType *type;
    struct GroupEnt *g;
    struct IsysObj *last;
    void *o;

    open_letter_post(D_kernel_bss_7C210);
    while ((l = get_next_letter_in_post(D_kernel_bss_7C210)) != 0) {
        type = get_reference_letter_type(l);
        if (type->mode == 0) {
            o = isysGetLetterObj(get_letter_receiver_obj_group(l));
            if (o != 0) {
                func_01BDF8(o, l, type);
            } else {
                __asm__ __volatile__("break 0");
            }
        } else {
            last = 0;
            for (g = isysGroupForFirst(get_letter_receiver_obj_group(l), 0); g != 0; g = isysGroupForNext(g, 0)) {
                last = g->obj;
                o = isysGetLetterObj(last);
                if (o != 0) {
                    if (func_01BDF8(o, l, type) == 1 && type->mode == 1) {
                        break;
                    }
                } else {
                    __asm__ __volatile__("break 0");
                }
            }
            if (last != 0) {
                isysGroupForExit(last, 0);
            }
        }
    }
    discard_all_letter_in_post(D_kernel_bss_7C210);
    close_letter_post(D_kernel_bss_7C210);
}
