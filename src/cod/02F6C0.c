/* asm/cod/02F6C0.s -> ratio.
 * Newlib 1.9.0 stdlib/mprec.c ratio (authentic source, include/newlib19_mprec.h)
 * MATCHED. */
#include "newlib19_mprec.h"

double
ratio (_Bigint * a, _Bigint * b)

{
  union double_union da, db;
  int k, ka, kb;

  da.d = b2d (a, &ka);
  db.d = b2d (b, &kb);
#ifdef Pack_32
  k = ka - kb + 32 * (a->_wds - b->_wds);
#else
  k = ka - kb + 16 * (a->_wds - b->_wds);
#endif
  if (k > 0)
    word0 (da) += k * Exp_msk1;
  else
    {
      k = -k;
      word0 (db) += k * Exp_msk1;
    }
  return da.d / db.d;
}
