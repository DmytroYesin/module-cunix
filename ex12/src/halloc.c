#include <unistd.h>
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
  block_h *new;
  new = sbrk(0);

  if(sbrk(STRUCT_SIZE + size) == (void*) - 1)
    return (NULL);
  new -> size = size;
  new -> n_ptr = NULL;
  if(prev)
  {
    prev -> n_ptr = new;
  }
  new -> flag = 0;
  return (new);
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

void free(block_h *addr)
{
  if(addr)
  {
    (addr - 1) -> flag = 1;
    base = NULL;
  }
  else
    return;
}

