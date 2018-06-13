#include <stdlib.h>
char* my_itoa(int n)
{
  char *buf = malloc(16 * sizeof(char));
  char *ptr = buf;
  int i = 1;
  int k;
  if (n < 0)
  {
    n = -1 * n;
    *buf = '-';
    buf++;
  }
  k = n;
  while (k > 9)
  {
    k /= 10;
    i *= 10;
  }
  while (i > 0)
  {
    k = n / i;
    *buf = '0' + k;
    buf++;
    n -= i * k;
    i /= 10;
  }
  *buf = '\0';
  return ptr;
}

