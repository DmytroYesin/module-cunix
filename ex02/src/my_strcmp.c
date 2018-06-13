#include <string.h>
int my_strlen(char *str)
{
  int i = 0;
  while(*str++) ++i;
  return i;
}

int my_strcmp(char *str1, char *str2)
{
  if (my_strlen(str1) > my_strlen(str2))
  {
    return 1;
  }
  else if (my_strlen(str1) < my_strlen(str2))
  {
    return -1;
  }
  else
  {
  while(*str1 && *str2)
  {
    if (*str1 < *str2)
     return -1;
    if (*str1 > *str2)
     return 1;
   ++str1; ++str2;
  }
  }
 return *str1? -1 : *str2? 1 : 0;
} 