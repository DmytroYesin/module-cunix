#include "../include/linked_list.h"
#include <stdio.h>
#include <stdlib.h>
#include <stddef.h>

node_t  *list_create(void *data)
{
   node_t *head = NULL;
   head = malloc(sizeof(node_t));
   head -> data = data;
   head -> next = NULL;
   return head;
}

void list_destroy(node_t **head, void (*fp)(void *data))
{
    if (head == NULL)
    {
      return ;
    }
    node_t *next;
    node_t *current = *head;
    while (current != NULL)
    {
         fp(current -> data);
         next = current -> next;
         free(current);
         current = next;
    }
    *head = NULL;
}

void list_push(node_t *head, void *data)
{
  if (head == NULL)
  {
    return ;
  }
  while(head -> next)
  {
	  head = head -> next;
  }
  head -> next = malloc(sizeof(node_t));
  head = head -> next;
  head -> next = NULL;
  head -> data = data;
}

void list_unshift(node_t **head, void *data)
{
     node_t   *new = malloc(sizeof(node_t));
     new -> data = data;
     new -> next = *head;
     *head = new;
}

void *list_pop(node_t **head)
{
    node_t *ptr, *ptr_ptr = *head;
    void *out;
    if(ptr_ptr -> next)
    {
      ptr = ptr_ptr -> next;
    }
    else
    {
      out = (*head) -> data;
      free((*head) -> data);
      free(*head);
      *head = NULL;
      return out;
    }
    while (ptr -> next)
    {
      ptr = ptr -> next;
      ptr_ptr = ptr_ptr -> next;
    }
    out = ptr -> data;
    free(ptr -> data);
    free(ptr);
    ptr_ptr -> next = NULL;
    return out;
}

void *list_shift(node_t **head)
{
   void *out;
   node_t *temp = *head;
   *head = (*head) -> next;
   out = temp -> data;
   free(temp -> data);
   free(temp);
   return out;
}

void *list_remove(node_t **head, int pos)
{
  void *out;
  node_t *ptr = *head, *ptr_ptr;
  if (pos == 0)
  {
      out = ptr -> data;
      (*head) = (*head) -> next;
      free(ptr -> data);
      free(ptr);
      return out;
  }
  ptr_ptr = ptr;
  ptr = ptr -> next;
  while(pos > 1)
  {
      ptr = ptr -> next;
      ptr_ptr = ptr_ptr -> next;
      pos--;
   }
  ptr_ptr -> next = ptr -> next;
  out = ptr -> data;
  free(ptr -> data);
  free(ptr);
  return out;
}

void list_print(node_t *head)
{
    node_t * current = head;
    while (current != NULL)
    {
        printf("%s\n", current -> data);
        current = current -> next;
    }
}

void list_visitor(node_t *head, void (*fp)(void *data))
{
    while (head != NULL)
    {
        (*fp)(head -> data);
        head = head -> next;
    }
}

