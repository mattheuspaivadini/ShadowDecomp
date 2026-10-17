/* asm/cod/028688.s -> SIG_DFL.
 * Newlib 1.9.0 signal/signal.c _init_signal_r (authentic source)
 * MATCHED. */
#include "newlib19.h"

typedef void (*_sig_func_ptr) (int);

#define NSIG 32
#define SIG_DFL ((_sig_func_ptr)0)

int
_init_signal_r (struct _reent *ptr)
{
  int i;

  if (ptr->_sig_func == NULL)
    {
      ptr->_sig_func = (_sig_func_ptr *)_malloc_r (ptr, sizeof (_sig_func_ptr) * NSIG);
      if (ptr->_sig_func == NULL)
	return -1;

      for (i = 0; i < NSIG; i++)
	ptr->_sig_func[i] = SIG_DFL;
    }

  return 0;
}
