#include <unistd.h>
#include <stdlib.h>
#include <stddef.h>
#define STRUCT_SIZE sizeof(struct halloc_block)

void *base = NULL;

typedef struct halloc_block block_h;

struct halloc_block
{
  size_t size;
  int flag;
  struct halloc_block *n_ptr;
};

block_h *search(block_h **prev , size_t size)
{
  block_h *now = base;

  while(now && !(now -> flag && now -> size >= size))
  {
   *prev = now;
   now = now -> n_ptr;
  }
  return now;
}

block_h *prolong_mem(block_h *prev, size_t size)
{
  block_h *now;
  now = sbrk(0);

  if(sbrk(STRUCT_SIZE + size) == (void*) - 1)
    return (NULL);
  now -> size = size;
  now -> n_ptr = NULL;
  if(prev)
  {
    prev -> n_ptr = now;
  }
  now -> flag = 0;
  return (now);
}

void *halloc(size_t size)
{
  block_h *now;
  block_h *prev;

  if(size <= 0)
    return NULL;
  if(base)
  {
    prev = base;
    now = search(&prev, size);
    if(now)
    {
      now -> flag = 0;
    }
    else
    {
      now = prolong_mem(prev, size);
      if (!now)
        return(NULL);
    }
  }
  else
  {
    now = prolong_mem(NULL, size);
    if (!now)
      return(NULL);
    base = now;
  }
  return(now + 1);
}

block_h *block_get(void *addr)
{
  block_h *res;
  res = (block_h *)addr - 1;
  return res;
}

void free(void *addr)
{
  if(addr)
  {
    block_h *targ = block_get(addr);
    targ -> flag = 1;
    base = NULL;
  }
  else
    return;
}

