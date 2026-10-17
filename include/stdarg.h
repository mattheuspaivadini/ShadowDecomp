/* stdarg.h - minimal <stdarg.h> for the EE-GCC distributions, which ship no
 * target headers. 2.96 implements it with the varargs builtins
 * (va_list = __builtin_va_list); the older 2.9 / 2.95.x generations use
 * gcc's ginclude/va-mips.h (vendored as include/va-mips.h). */
#ifndef _STDARG_H
#define _STDARG_H

#if __GNUC__ == 2 && __GNUC_MINOR__ < 96
#define _STDARG_H_
#include "va-mips.h"
typedef __gnuc_va_list va_list;
#else
typedef __builtin_va_list va_list;
typedef __builtin_va_list __gnuc_va_list;

#define va_start(v, l) __builtin_stdarg_start((v), l)
#define va_end(v) __builtin_va_end(v)
#define va_arg(v, l) __builtin_va_arg((v), l)
#define va_copy(d, s) __builtin_va_copy((d), (s))
#endif

#endif /* _STDARG_H */
