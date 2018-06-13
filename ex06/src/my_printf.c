#include <stdio.h>
#include <stdarg.h>
int my_printf(const char* format, ...)
{
  va_list arg;
  int out;
  va_start (arg, format);
  out = vfprintf (stdout, format, arg);
  va_end (arg);
  return out;
}

