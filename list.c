#include <stdlib.h>
#include <stdio.h>
#include "list.h"

List_ptr create_list(void)
{
  List_ptr new_list = malloc(sizeof(List));
  new_list->head = NULL;
  new_list->last = NULL;
  new_list->count = 0;
  return new_list;
}

Node_ptr create_node(int value)
{
  Node_ptr new_node = malloc(sizeof(Node));
  new_node->value = value;
  new_node->next = NULL;
  return new_node;
}

Status add_to_end(List_ptr list, int value)
{
  Node_ptr new_node = create_node(value);
  if (list->head == NULL)
  {
    list->head = new_node;
  }
  else
  {
    list->last->next = new_node;
  }
  list->last = new_node;
  list->count += 1;
  return Success;
}

Status add_to_start(List_ptr list, int value)
{
  Node_ptr new_node = create_node(value);
  if (list->head == NULL)
  {
    list->head = new_node;
  }
  else
  {
    new_node->next = list->head;
    list->head = new_node;
  }
  list->count += 1;
  return Success;
}

Status insert_at(List_ptr list, int value, int position)
{
  if (position < 0 || position > list->count)
    return Failure;
  if (position == 0)
    return add_to_start(list, value);
  if (position == list->count)
    return add_to_end(list, value);
  Node_ptr new_node = create_node(value);
  Node_ptr previous_node = NULL;
  Node_ptr p_walk = list->head;
  for (int i = 0; i < position; i++)
  {
    previous_node = p_walk;
    p_walk = p_walk->next;
  }
  new_node->next = p_walk;
  previous_node->next = new_node;
  list->count += 1;
  return Success;
}

Status add_unique(List_ptr list, int value)
{
  Status is_value_absent = Success;
  Node_ptr p_walk = list->head;
  while (p_walk != NULL)
  {
    if (p_walk->value == value)
    {
      is_value_absent = Failure;
    }
    p_walk = p_walk->next;
  }
  return is_value_absent && add_to_end(list, value);
}

void display(List_ptr list)
{
  Node_ptr p_walk = list->head;
  while (p_walk != NULL)
  {
    printf("%d ", p_walk->value);
    p_walk = p_walk->next;
  }
  printf("\n");
}

Status remove_from_start(List_ptr list)
{
  if (list->count <= 0)
    return Failure;
  if (list->count == 1)
  {
    list->last = NULL;
  }
  list->head = list->head->next;
  list->count -= 1;
  return Success;
}

Status clear_list(List_ptr list)
{
  Node_ptr p_walk = list->head;
  Node_ptr element_to_free = NULL;
  while (p_walk != NULL)
  {
    element_to_free = p_walk;
    p_walk = p_walk->next;
    free(element_to_free);
  }
  list->head = NULL;
  list->last = NULL;
  list->count = 0;
  return Success;
}

void destroy_list(List_ptr list)
{
  clear_list(list);
  free(list);
}
