/* KERNEL.XFF @ 0x033818 (60 B) - copysignf
 * Evidence: Newlib 1.9 libm/sf_copysign.c verbatim (two GET_FLOAT_WORD unions on the stack, SET_FLOAT_WORD in registers).
 */
typedef unsigned int __uint32_t;
typedef union
{
  float value;
  __uint32_t word;
} ieee_float_shape_type;
#define GET_FLOAT_WORD(i,d) do { ieee_float_shape_type gf_u; gf_u.value = (d); (i) = gf_u.word; } while (0)
#define SET_FLOAT_WORD(d,i) do { ieee_float_shape_type sf_u; sf_u.word = (i); (d) = sf_u.value; } while (0)

float copysignf(float x, float y)
{
	__uint32_t ix,iy;
	GET_FLOAT_WORD(ix,x);
	GET_FLOAT_WORD(iy,y);
	SET_FLOAT_WORD(x,(ix&0x7fffffff)|(iy&0x80000000));
        return x;
}
