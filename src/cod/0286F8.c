/* asm/cod/0286F8.s -> _signal_r.
 * Newlib 1.9.0 signal/signal.c _signal_r (authentic source)
 * MATCHED. */
#include "newlib19.h"

typedef void (*_sig_func_ptr) (int);

#define NSIG 32
#define SIG_ERR ((_sig_func_ptr)-1)
#define EINVAL 22

extern int _init_signal_r (struct _reent *);

_sig_func_ptr
_signal_r (struct _reent *ptr, int sig, _sig_func_ptr func)
{
  _sig_func_ptr old_func;

  if (sig < 0 || sig >= NSIG)
    {
      ptr->_errno = EINVAL;
      return SIG_ERR;
    }

  if (ptr->_sig_func == NULL && _init_signal_r (ptr) != 0)
    return SIG_ERR;

  old_func = ptr->_sig_func[sig];
  ptr->_sig_func[sig] = func;

  return old_func;
}
