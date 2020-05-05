#include <stdio.h>
#include "list.h"

unsigned int assert(List_ptr, int *, int);

unsigned int assert(List_ptr list, int *values, int length)
{
  if (list->count != length)
    return 0;
  unsigned int is_equal = Success;
  Node_ptr p_walk = list->head;
  for (int i = 0; i < list->count; i++)
  {
    is_equal &= p_walk->value == values[i];
    p_walk = p_walk->next;
  }
  return is_equal;
}

void test_add_to_end()
{
  printf("add_to_end\n");
  List_ptr list = create_list();
  int values[10] = {};
  printf("\tNo values: %d\n", assert(list, values, 0));

  add_to_end(list, 1);
  values[0] = 1;
  printf("\tAdding to list when there are no elements in it: %d\n", assert(list, values, 1));

  add_to_end(list, 2);
  values[1] = 2;
  printf("\tAdding to list when there is an element in it: %d\n", assert(list, values, 2));

  add_to_end(list, 3);
  add_to_end(list, 4);
  values[2] = 3;
  values[3] = 4;
  printf("\tAdding to list when there are more than two elements in it: %d\n", assert(list, values, 4));
}

int main(void)
{
  test_add_to_end();
  return 0;
}