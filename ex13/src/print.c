#include <stdio.h>
#include <stdlib.h>
#include <stdarg.h>
#include "filler.h"
#define _POSIX_C_SOURCE 200809L

void print_log(const char *filename, const char *mode, const char *format, ...)
{
  va_list   arg;
  FILE      *log;
  log = fopen(filename, mode);
  va_start(arg, format);
  vfprintf(log, format, arg);
  va_end(arg);
  fclose(log);
}

void print_pos(pos_t p)
{
    dprintf(1, "%d %d", p.x, p.y);
    print_log("filler.log","a","Position: (%d;%d)\n",p.x,p.y);
}

