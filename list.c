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
  if (new_node != NULL)
  {
    new_node->value = value;
    new_node->next = NULL;
  }
  return new_node;
}

Status add_to_end(List_ptr list, int value)
{
  Node_ptr new_node = create_node(value);
  if (new_node == NULL)
  {
    return Failure;
  }

  Node_ptr *ptr_to_set = &list->head;
  if (list->head != NULL)
  {
    ptr_to_set = &list->last->next;
  }
  *ptr_to_set = new_node;
  list->last = new_node;
  list->count++;
  return Success;
}

Status add_to_start(List_ptr list, int value)
{
  Node_ptr new_node = create_node(value);
  if (new_node == NULL)
  {
    return Failure;
  }
  if (list->head == NULL)
  {
    list->last = new_node;
  }

  new_node->next = list->head;
  list->head = new_node;
  list->count++;
  return Success;
}

Status insert_at(List_ptr list, int value, int position)
{
  Node_ptr new_node = create_node(value);

  if (position < 0 || position > list->count || new_node == NULL)
  {
    return Failure;
  }
  if (position == 0)
  {
    return add_to_start(list, value);
  }
  if (position == list->count)
  {
    return add_to_end(list, value);
  }

  Node_ptr p_walk = list->head;
  for (int i = 1; i < position; i++)
  {
    p_walk = p_walk->next;
  }
  new_node->next = p_walk->next;
  p_walk->next = new_node;
  list->count++;
  return Success;
}

Status add_unique(List_ptr list, int value)
{
  return !is_exists(list, value) && add_to_end(list, value);
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
  if (list->head == NULL)
  {
    return Failure;
  }
  if (list->head->next == NULL)
  {
    list->last = NULL;
  }

  Node_ptr element_to_free = list->head;
  list->head = list->head->next;
  free(element_to_free);
  list->count--;
  return Success;
}

Status remove_from_end(List_ptr list)
{
  if (list->head == NULL)
  {
    return Failure;
  }

  Node_ptr previous = NULL;
  Node_ptr current = list->head;

  while (current->next != NULL)
  {
    previous = current;
    current = current->next;
  }
  if (previous == NULL)
  {
    list->head = NULL;
  }
  else
  {
    previous->next = NULL;
  }

  list->last = previous;
  free(current);
  list->count--;
  return Success;
}

Status remove_at(List_ptr list, int position)
{
  if (position < 0 || position >= list->count)
    return Failure;
  if (position == 0)
    return remove_from_start(list);
  if (position == (list->count) - 1)
    return remove_from_end(list);
  Node_ptr p_walk = list->head;
  for (int i = 1; i < position; i++)
  {
    p_walk = p_walk->next;
  }
  Node_ptr element_to_free = p_walk->next;
  p_walk->next = p_walk->next->next;
  free(element_to_free);
  list->count -= 1;
  return Success;
}

Status remove_first_occurrence(List_ptr list, int value)
{
  Status is_removed = Failure;
  Status is_first_occurrence = Success;
  Node_ptr p_walk = list->head;
  for (int i = 0; i < list->count; i++)
  {
    if (p_walk->value == value && is_first_occurrence)
    {
      is_removed = remove_at(list, i);
      is_first_occurrence = Failure;
    }
    p_walk = p_walk->next;
  }
  return is_removed;
}

Status remove_all_occurrences(List_ptr list, int value)
{
  Status is_removed = Failure;
  Node_ptr p_walk = list->head;
  for (int i = 0; p_walk != NULL; i++)
  {
    if (p_walk->value == value)
    {
      is_removed = remove_at(list, i);
      i--;
    }
    p_walk = p_walk->next;
  }
  return is_removed;
}

Status is_exists(List_ptr list, int value)
{
  Status exist_status = Failure;
  Node_ptr p_walk = list->head;
  while (p_walk != NULL)
  {
    if (p_walk->value == value)
    {
      exist_status = Success;
    }
    p_walk = p_walk->next;
  }
  return exist_status;
}

Status clear_list(List_ptr list)
{
  Status is_removed = Failure;
  while (list->head != NULL)
  {
    is_removed = remove_from_start(list);
  }
  return is_removed;
}

void destroy_list(List_ptr list)
{
  clear_list(list);
  free(list);
}
