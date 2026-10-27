/* KERNEL.XFF @ 0x030B18 (132 B) - div
 * Evidence: Newlib 1.9 stdlib/div.c (quotient/remainder fix-up for mixed signs); div_t returned in $v0 as a 64-bit pair.
 */
typedef struct
{
  int quot;
  int rem;
} div_t;

div_t div(int num, int denom)
{
  div_t r;

  r.quot = num / denom;
  r.rem = num % denom;
  if (num >= 0 && r.rem < 0)
    {
      ++r.quot;
      r.rem -= denom;
    }
  else if (num < 0 && r.rem > 0)
    {
      --r.quot;
      r.rem += denom;
    }
  return (r);
}
