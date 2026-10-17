/* fp-bit-common.h - the shared inline helpers of gcc-3.0 gcc/config/fp-bit.c
 * (nan/isnan/isinf/iszero/flip_sign), included by each fine-grained object. */
#ifndef FP_BIT_COMMON_H
#define FP_BIT_COMMON_H

#ifdef NO_NANS

#define nan() 0
#define isnan(x) 0
#define isinf(x) 0
#else

#if defined FLOAT
extern const fp_number_type __thenan_sf;
#else
extern const fp_number_type __thenan_df;
#endif

INLINE
static fp_number_type *
nan (void)
{
  /* Discard the const qualifier... */
#ifdef FLOAT  
  return (fp_number_type *) (& __thenan_sf);
#else
  return (fp_number_type *) (& __thenan_df);
#endif
}

INLINE
static int
isnan ( fp_number_type *  x)
{
  return x->class == CLASS_SNAN || x->class == CLASS_QNAN;
}

INLINE
static int
isinf ( fp_number_type *  x)
{
  return x->class == CLASS_INFINITY;
}

#endif /* NO_NANS */

INLINE
static int
iszero ( fp_number_type *  x)
{
  return x->class == CLASS_ZERO;
}

INLINE 
static void
flip_sign ( fp_number_type *  x)
{
  x->sign = !x->sign;
}

extern FLO_type pack_d ( fp_number_type * );

#endif /* FP_BIT_COMMON_H */
