#include <stddef.h>
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

