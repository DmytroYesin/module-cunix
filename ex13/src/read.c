#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include <fcntl.h>
#include <errno.h>
#include <sys/stat.h>
#include "filler.h"
#include "my_string.h"

void read_input(filler_t *filler)
{
  char buff[BUF_SIZE];
  int  input;

  while(1)
  {
    memset(buff, '\0', BUF_SIZE);
    input = read(0, buff, BUF_SIZE - 1);
    if(!strlen(buff))
    {
      break;
    }
    if(filler->current_stream == NULL)
      filler->current_stream = string_create(buff);
    else
      string_append(filler->current_stream, buff);
    if (input <= 0)
      break;
  }
}

int read_finished(stream_t* buff)
{
  unsigned int 	pos = 0;
  int   elem_pos = 0;
  bool 	first_size = true;
  char 	arr_elem_size[32];
  pos_t elem_size;

  while(pos <= buff->size)
  {
    if(buff->str[pos] > '9' || buff->str[pos] < '0')
      pos++;
    else if (first_size)
    {
      while(pos <= buff->size && buff->str[pos] != '\n')
        pos++;
      pos++;
      first_size = false;
    }
    else
    {
      elem_pos = pos;

      while(pos <= buff->size && buff->str[pos] != '\n')
        pos++;
      if(buff->str[pos] != '\n')
        return -1;
      else
      {
        find_size(arr_elem_size, buff->str, elem_pos);
        elem_size = parse_size(arr_elem_size);
        if(buff->size <= pos + elem_size.x*(elem_size.y + 1))
          return -1;
        else
          return 0;
      }
    }
  }
  return -1;
}

req_t *read_request(filler_t *filler)
{
  req_t *req = NULL;
  read_input(filler);
  if(read_finished(filler->current_stream) == 0)
    req = parse_all(filler->current_stream->str);
  return req;
}

