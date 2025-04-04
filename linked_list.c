#include "linked_list.h"

#include <stdlib.h>

struct list_node *new_node(size_t value)
{ 
  struct list_node* node = malloc(sizeof(struct list_node));
  node->value = value;
  node->next = NULL;
  return node; 
}

void insert_at_head(struct linked_list *list, size_t value) 
{
  struct list_node *node = new_node(value);
  node->next = (list->head);
  list->head = node;
}

void insert_at_tail(struct linked_list *list, size_t value) 
{
  struct list_node *node = new_node(value);
  
  node->next = NULL;
  if (list->head == NULL) 
  {
    list->head = node;
    return;
  }

  struct list_node *temp = list->head;
  while (temp->next != NULL) 
  {
    temp = temp->next;
  }
  temp->next = node;
}

size_t remove_from_head(struct linked_list *list) 
{ 
  if (list->head == NULL)
  {
    return 34;  //something greater than 15 (max tile number)
  }

  struct list_node *temp = list->head;  
  size_t value = temp->value;    
  list->head = temp->next;  
  
  free(temp);  
  return value;
}

size_t remove_from_tail(struct linked_list *list) 
{
  struct list_node *temp = list->head;
  size_t value = 0;
  if(list->head == NULL)
  {
    return 34; //something greater than 15 (max tile number)
  }
  
  if (temp->next == NULL) 
  {
    value = temp->value;
    free(temp);
    list->head = NULL; 
    return value;
  }

  while (temp->next->next != NULL) 
  {
    temp = temp->next;
  }

  value = temp->next->value;
  free(temp->next);
  temp->next = NULL;

  return value;
}

void free_list(struct linked_list list) 

{
  struct list_node* temp = list.head;
  while (temp != NULL) 
    {
      struct list_node *next = temp->next;
      free(temp);
      temp = next;
    }
}

// Utility function to help you debugging, do not modify
void dump_list(FILE *fp, struct linked_list list) 
{
  fprintf(fp, "[ ");
  for (struct list_node *cur = list.head; cur != NULL; cur = cur->next) 
  {
    fprintf(fp, "%zu ", cur->value);
  }
  fprintf(fp, "]\n");
}
