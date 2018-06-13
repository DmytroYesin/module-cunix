#include <stdio.h>
int my_putchar(char ss)
{
  long write(int, const char *, unsigned long);
  return write(1,&ss,1);
}
int my_puts(const char *ss)
{
  while(*ss)
  {
    if(my_putchar(*ss++) == EOF) return EOF;
  }
  if(my_putchar('\n') == EOF) return EOF;
  return 0;
}

