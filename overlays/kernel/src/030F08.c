/* KERNEL.XFF @ 0x030F08 (40 B) - fabsf
 * Evidence: Newlib 1.9 libm/sf_fabs.c verbatim (GET_FLOAT_WORD through a stack union, SET_FLOAT_WORD in registers); the source text is byte-exact with the module's default compiler.
 */
typedef unsigned int __uint32_t;
typedef union
{
  float value;
  __uint32_t word;
} ieee_float_shape_type;
#define GET_FLOAT_WORD(i,d) do { ieee_float_shape_type gf_u; gf_u.value = (d); (i) = gf_u.word; } while (0)
#define SET_FLOAT_WORD(d,i) do { ieee_float_shape_type sf_u; sf_u.word = (i); (d) = sf_u.value; } while (0)

float fabsf(float x)
{
	__uint32_t ix;
	GET_FLOAT_WORD(ix,x);
	SET_FLOAT_WORD(x,ix&0x7fffffff);
        return x;
}
