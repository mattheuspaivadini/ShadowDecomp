/* KERNEL.XFF @ 0x030A90 (132 B) - strstr
 * Evidence: Newlib 1.9 string/strstr.c (empty-haystack special case, inner index loop); byte-exact with the module's default compiler.
 */
typedef unsigned int size_t;

char *strstr(const char *searchee, const char *lookfor)
{
  if (*searchee == 0)
    {
      if (*lookfor)
	return (char *) 0;
      return (char *) searchee;
    }

  while (*searchee)
    {
      size_t i;
      i = 0;

      while (1)
	{
	  if (lookfor[i] == 0)
	    {
	      return (char *) searchee;
	    }

	  if (lookfor[i] != searchee[i])
	    {
	      break;
	    }
	  i++;
	}
      searchee++;
    }

  return (char *) 0;
}
