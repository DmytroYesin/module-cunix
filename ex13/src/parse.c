#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "filler.h"
#include "my_string.h"

void write_matrix(char **array, int h, int w, char *all, int gpos)
{
  for(int i = 0; i < h; i++)
  {
    for(int j = 0; j < w + 1; j++)
    {
	    array[i][j] = all[gpos];
		  gpos++;
		}
  }
}

req_t *parse_all(char *all)
{
	req_t 	*req;
	pos_t 	pos;
	int 	  n, gpos;
	char 	  *map_size, *elem_size;

	n = 0;
	gpos = 2;
	map_size = (char *) malloc(BUF_SIZE * sizeof(char));
	elem_size = (char *) malloc(BUF_SIZE * sizeof(char));
  req = create_req();
	req->symbol = *all;
	do {
		*(map_size + n) = *(all + gpos);
		gpos++;
		n++;
	} while(*(all + gpos - 1) != '\n');

  pos = parse_size(map_size);
	req->map.h = pos.x;
	req->map.w = pos.y;
	req->map.array = (char **) malloc(req->map.h * sizeof(char*));
  for(int i = 0; i < req->map.h; i++)
		req->map.array[i] = (char *) malloc((req->map.w + 1) * sizeof(char));

  write_matrix(req->map.array, req->map.h, req->map.w, all, gpos);
	gpos += req->map.h*(req->map.w + 1);
  n = 0;
	do {
		*(elem_size + n) = *(all + gpos);
		gpos++;
		n++;
  } while(*(all + gpos - 1) != '\n');

	pos = parse_size(elem_size);
	req->elem.h = pos.x;
	req->elem.w = pos.y;
	req->elem.array = (char **) malloc(req->elem.h * sizeof(char*));
	for(int i = 0; i < req->elem.h; i++)
		req->elem.array[i] = (char *)malloc((req->elem.w+1) * sizeof(char));

  write_matrix(req->elem.array, req->elem.h, req->elem.w, all, gpos);
  free(map_size);
	free(elem_size);
  return req;
}

pos_t parse_size(char *answer)
{
  char *y, *x;
  int size, i;
  pos_t pos;

  size = strlen(answer);
  y = malloc(size);
  x = malloc(size);

  for (i = 0; i < size && answer[i] != ' '; i++)
  x = strncpy(x, answer, i + 1);
  y = strcpy(y, answer + i + 1);
  pos.x = atoi(x);
  pos.y = atoi(y);

  free(x);
  free(y);
  return pos;
}

int find_size(char array_elem_size[32], char *buf, int pos)
{
  int i;

  for (i = 0; buf[pos] != '\n'; i++)
  {
    array_elem_size[i] = buf[pos];
    pos++;
  }
  array_elem_size[i] = '\0';
  return 0;
}

