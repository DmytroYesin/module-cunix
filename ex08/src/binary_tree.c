#include <binary_tree.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

node_t  *allocnode()
{
  node_t *node = malloc(sizeof(node_t));
  node -> data = NULL;
  node -> key = NULL;
  node -> right = NULL;
  node -> left = NULL;
  return node;
}

void print_node(node_t *node)
{
  if(node == NULL)
    return ;
  printf("%p: %s ", node -> data, (char*)node ->key);
}

void destroy_tree(node_t *node, void(*fdestroy)(node_t *root))
{
  if(node == NULL)
    return ;
  destroy_tree(node->left,fdestroy);
  destroy_tree(node->right,fdestroy);
  fdestroy(node);
  free(node);
}

void visit_tree(node_t *node, void(*fp)(node_t *root))
{
  if(node == NULL)
    return ;
  fp(node);
  visit_tree(node->left,fp);
  visit_tree(node->right,fp);
}

node_t *insert(node_t *root, char *key, void *data)
{
  if(root == NULL)
  {
    root = malloc(sizeof(node_t));
    root -> data = data;
    root -> key = key;
    root -> right = NULL;
    root -> left = NULL;
    return root;
  }
  if(strcmp(key, root -> key) > 0)
  {
    root -> right = insert(root -> right, key, data);
  }
  else
  {
    root -> left = insert(root -> left, key, data);
  }
  return root;
}

