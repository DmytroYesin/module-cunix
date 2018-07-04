#include <stdio.h>
#include <stdlib.h>
#include "filler.h"

int check_free_space(map_t *map, elem_t *new_elem, pos_t p)
{
     for(int i = 0; i < new_elem->h; i++)
     {
       for(int j = 0; j < new_elem->w; j++)
       {
         if(new_elem->array[i][j] == '*')
         {
           if(i + p.y < map->h && j + p.x < map->w && i + p.y >= 0 && j + p.x >= 0)
           {
             if(map->array[i + p.y][j + p.x] != '.')
               return -1;
           }
           else
            return -1;
         }
       }
     }
     return 0;
   }

int check_connection(map_t *map, elem_t *new_elem, pos_t p, char symbol)
{
  for(int i = 0; i < new_elem->h; i++)
  {
    for(int j = 0; j < new_elem->w; j++)
    {
      if(new_elem->array[i][j] != '.')
      {
        if(i + p.y + 1 < map->h && map->array[i + p.y + 1][j + p.x] == symbol)
            return 0;
        if (i + p.y - 1 >= 0 && map->array[i + p.y - 1][j + p.x] == symbol)
            return 0;
        if (j + p.x + 1 < map->w && map->array[i + p.y][j + p.x + 1] == symbol)
            return 0;
        if (j + p.x - 1 >= 0 && map->array[i + p.y][j + p.x - 1] == symbol)
            return 0;
      }
    }
  }
  return -1;
}

pos_t typik_u(req_t *core, pos_t res, int y, int x)
{
  for (int i = y; i > 0; i--)
  {
    for(int j = 0; j < x; j++)
    {
      res.x = i;
      res.y = j;
      if(!check_free_space(&(core->map), &(core->elem), res) && !check_connection(&(core->map), &(core->elem), res, core->symbol))
      {
        return res;
      }
    }
  }
  return res;
}

pos_t typik_d(req_t *core, pos_t res, int x)
{
  for (int i = 0; i < x; i++)
  {
    for(int j = 0; j < x; j++)
    {
      res.x = i;
      res.y = j;
      if(!check_free_space(&(core->map), &(core->elem), res) && !check_connection(&(core->map), &(core->elem), res, core->symbol))
      {
        return res;
      }
    }
  }
  return res;
}

pos_t typik_r(req_t *core, pos_t res, int x)
{
  for (int i = 0; i < x; i++)
  {
    for(int j = 0; j < x; j++)
    {
      res.x = i;
      res.y = j;
      if(!check_free_space(&(core->map), &(core->elem), res) && !check_connection(&(core->map), &(core->elem), res, core->symbol))
      {
        return res;
      }
    }
  }
  return res;
}

pos_t typik_l(req_t *core, pos_t res, int y, int x)
{
  for (int i = 0; i < y; i++)
  {
    for(int j = 0; j < x; j++)
    {
      res.x = j;
      res.y = i;
      if(!check_free_space(&(core->map), &(core->elem), res) && !check_connection(&(core->map), &(core->elem), res, core->symbol))
      {
        return res;
      }
    }
  }
  return res;
}


pos_t play(req_t *core)
{
  pos_t 	res;
  int 	y, x;
  int yy = 0;
  int xx = 0;
  y = core->map.h;
  x = core->map.w;
  for (int i = 0; i < y; i++)
  {
    for (int j = 0; j < x; j++)
    {
      if ((core->map.array[i][j] == core->symbol) && (yy == 0) && (xx == 0))
      {
        yy = i;
        xx = j;
      }
    }
  }
    if (yy < (core->map.h / 2))
      res = typik_u(core, res, y, x);
    else if (xx < (core->map.w / 2))
      res = typik_r(core, res, x);
    else if (xx >= (core->map.w / 2))
      res = typik_l(core, res, y, x);
    else if (yy >= (core->map.h / 2))
      res = typik_d(core, res, x);
    return res;
}

