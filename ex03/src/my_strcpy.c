char *my_strcpy(char *dst, char *src)
{
  for (char *p = dst; (*p++ = *src++););
  return dst;
}
