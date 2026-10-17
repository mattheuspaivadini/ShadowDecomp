/* stdarg.h - minimal stub over the EE-GCC 2.96 varargs builtins.
 * The decomp.me EE-GCC distributions ship no target headers; 2.96 implements
 * <stdarg.h> with these builtins (va_list = __builtin_va_list). */
#ifndef _STDARG_H
#define _STDARG_H

typedef __builtin_va_list va_list;
typedef __builtin_va_list __gnuc_va_list;

#define va_start(v, l) __builtin_stdarg_start((v), l)
#define va_end(v) __builtin_va_end(v)
#define va_arg(v, l) __builtin_va_arg((v), l)
#define va_copy(d, s) __builtin_va_copy((d), (s))

#endif /* _STDARG_H */
