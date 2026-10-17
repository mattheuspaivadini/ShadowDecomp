/* newlib19_mprec.h - Newlib 1.9.0 stdlib/mprec.h, the configuration this image uses.
 *
 * Transcribed from newlib-1_9_0 newlib/libc/stdlib/mprec.h and the _Bigint of
 * newlib/libc/include/sys/reent.h: little-endian (IEEE_8087), 64-bit doubles
 * (_DOUBLE_IS_32BITS off), Pack_32, Sudden_Underflow off. __Long is `int' because
 * long is 64-bit in this EE-GCC (docs/compiler.md section 8). Confirmed by the
 * already-matched mprec routines (_b2d, _d2b, _lshift, _multiply, __mdiff, ...). */
#ifndef NEWLIB19_MPREC_H
#define NEWLIB19_MPREC_H

#include "newlib19.h"

typedef unsigned int __uint32_t;
typedef int __int32_t;
#define __Long int
typedef unsigned __Long __ULong;

struct _Bigint
{
  struct _Bigint *_next;
  int _k, _maxwds, _sign, _wds;
  __ULong _x[1];
};

typedef struct _Bigint _Bigint;

union double_union
{
  double d;
  __uint32_t i[2];
};

#define IEEE_8087
#define word0(x) (x.i[1])
#define word1(x) (x.i[0])

#define Storeinc(a,b,c) (((unsigned short *)a)[1] = (unsigned short)b, \
((unsigned short *)a)[0] = (unsigned short)c, a++)

#define Exp_shift  20
#define Exp_shift1 20
#define Exp_msk1    ((__uint32_t)0x100000L)
#define Exp_msk11   ((__uint32_t)0x100000L)
#define Exp_mask  ((__uint32_t)0x7ff00000L)
#define P 53
#define Bias 1023
#define IEEE_Arith
#define Emin (-1022)
#define Exp_1  ((__uint32_t)0x3ff00000L)
#define Exp_11 ((__uint32_t)0x3ff00000L)
#define Ebits 11
#define Frac_mask  ((__uint32_t)0xfffffL)
#define Frac_mask1 ((__uint32_t)0xfffffL)
#define Ten_pmax 22
#define Bletch 0x10
#define Bndry_mask  ((__uint32_t)0xfffffL)
#define Bndry_mask1 ((__uint32_t)0xfffffL)
#define LSB 1
#define Sign_bit ((__uint32_t)0x80000000L)
#define Log2P 1
#define Tiny0 0
#define Tiny1 1
#define Quick_max 14
#define Int_max 14
#define Infinite(x) (word0(x) == ((__uint32_t)0x7ff00000L)) /* sufficient test for here */

#define rounded_product(a,b) a *= b
#define rounded_quotient(a,b) a /= b

#define Big0 (Frac_mask1 | Exp_msk1*(DBL_MAX_EXP+Bias-1))
#define Big1 ((__uint32_t)0xffffffffL)

#define Pack_32

#define Balloc	_Balloc
#define Bfree	_Bfree
#define multadd _multadd
#define s2b	_s2b
#define lo0bits _lo0bits
#define hi0bits _hi0bits
#define i2b	_i2b
#define mult	_multiply
#define pow5mult	_pow5mult
#define lshift	_lshift
#define cmp	__mcmp
#define diff	__mdiff
#define ulp 	_ulp
#define b2d	_b2d
#define d2b	_d2b
#define ratio	_ratio

#define tens __mprec_tens
#define bigtens __mprec_bigtens
#define tinytens __mprec_tinytens

double 		ulp(double x);
double		b2d(_Bigint *a , int *e);
_Bigint *	Balloc(struct _reent *p, int k);
void 		Bfree(struct _reent *p, _Bigint *v);
_Bigint *	multadd(struct _reent *p, _Bigint *, int, int);
_Bigint *	s2b(struct _reent *, const char*, int, int, __ULong);
_Bigint	*	i2b(struct _reent *,int);
_Bigint *	mult(struct _reent *, _Bigint *, _Bigint *);
_Bigint *	pow5mult(struct _reent *, _Bigint *, int k);
int 		hi0bits(__ULong);
int 		lo0bits(__ULong *);
_Bigint *	d2b(struct _reent *p, double d, int *e, int *bits);
_Bigint *	lshift(struct _reent *p, _Bigint *b, int k);
_Bigint *	diff(struct _reent *p, _Bigint *a, _Bigint *b);
int		cmp(_Bigint *a, _Bigint *b);

double		ratio(_Bigint *a, _Bigint *b);

/* memcpy is the image's func_0012821C (see newlib19.h) */
#define Bcopy(x,y) func_0012821C((char *)&x->_sign, (char *)&y->_sign, y->_wds*sizeof(__Long) + 2*sizeof(int))

#define n_bigtens 5

extern const double tinytens[];
extern const double bigtens[];
extern const double tens[];

double _mprec_log10(int);

#endif /* NEWLIB19_MPREC_H */
