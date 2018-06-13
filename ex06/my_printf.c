#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <stdarg.h>

 int my_atoi(const char *nptr)
{
     int out = 0;
     int sign = 1;
     if(*nptr == '-')
     {
         sign = -1;
         nptr++;
     }
     while((*nptr >= '0')&&(*nptr <= '9'))
     {
       out *= 10;
       out += (*nptr - '0');
       nptr++;
     }
     return (sign * out);
 }

int is_digit (const char *c)
{
    return  (*c >= '0') && (*c <= '9');
}
int check_format(const char *c,char s)
{
    return *c == s;
}
int my_strlen(char *str)
{
    int i = 0;
    while(*str++) ++i;
    return i;
}

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


int my_printf(const char* format, ...) {
  extern long write(int, const char*, unsigned int);

  va_list arg_list;
  char *st, *padd_str, *str,*res_str, *padd_str_init;
  int padd;
  unsigned char padd_symb;

  str = malloc(256 * sizeof(char));
  padd_str_init = malloc(20 * sizeof(char));
  res_str = str;
  va_start(arg_list, format);

  while(*format != '\0') {

    if(check_format(format,'%')) {
      padd = 0;
      padd_symb = 0;
      padd_str = padd_str_init;

      format++;
      while(!check_format(format,' ') && !check_format(format,'\0')) {
        if(check_format(format,'%')) {
          *str = '%';
          str++;
          format++;
          break;
        }
        if(check_format(format,'0')) {
          padd_symb = '0';
          format++;
        }
        while(is_digit(format)) {
          *padd_str = *format;
          padd_str++;
          format++;
        }
        *padd_str = '\0';
        padd = my_atoi(padd_str_init);
        if(check_format(format,'s'))
          st = va_arg(arg_list, char *);
        if(check_format(format,'d')) {
          int i = va_arg(arg_list, int);
          st = my_itoa(i);
        }
        padd -= my_strlen(st);
        while(padd-- > 0) *str++ = (padd_symb)? padd_symb:' ';
        while(*st != '\0') {
          *str = *st;
          str++;
          st++;
        }
        format++;
        break;
      }
      continue;
    }
    *str = *format;
    str++;
    format++;
  }
  *str = '\0';

  write(1,res_str, strlen(res_str));
  va_end(arg_list);
  free(padd_str_init);
  free(res_str);
  return 0;
}
