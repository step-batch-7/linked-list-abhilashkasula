#include <stdio.h>
#include "../list.h"

unsigned int assert_list(List_ptr, int *, int);

unsigned int assert_list(List_ptr list, int *values, int length)
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

Status assert(Status actual_status, Status expected)
{
  return actual_status == expected;
}

void test_add_to_end(void)
{
  printf("add_to_end\n");

  List_ptr list = create_list();
  int values[4] = {};
  printf("\tNo values: %d\n", assert_list(list, values, 0));

  printf("\tshould add a number to list when there are no elements\n");
  printf("\t\tStatus should be Success: %d\n", assert(add_to_end(list, 1), Success));
  values[0] = 1;
  printf("\t\tList values should be [1]: %d\n", assert_list(list, values, 1));

  printf("\tshould add a number at last when there is an element in the list\n");
  printf("\t\tStatus should be Success: %d\n", assert(add_to_end(list, 2), Success));
  values[1] = 2;
  printf("\t\tList values should be [1, 2]: %d\n", assert_list(list, values, 2));

  printf("\tshould add a number at last when there are more than two elements in it\n");
  add_to_end(list, 3);
  values[2] = 3;
  printf("\t\tStatus should be Success: %d\n", assert(add_to_end(list, 4), Success));
  values[3] = 4;
  printf("\t\tList values should be [1, 2, 3, 4]: %d\n", assert_list(list, values, 4));
  destroy_list(list);
}

void test_add_to_start(void)
{
  printf("add_to_start\n");

  List_ptr list = create_list();
  int values[4] = {};
  printf("\tNo values: %d\n", assert_list(list, values, 0));

  printf("\tshould add a number at first when there are no elements\n");
  printf("\t\tStatus should be Success: %d\n", assert(add_to_start(list, 1), Success));
  values[0] = 1;
  printf("\t\tList values should be [1]: %d\n", assert_list(list, values, 1));

  printf("\tshould add a number at first when there is an element\n");
  printf("\t\tStatus should be Success: %d\n", assert(add_to_start(list, 2), Success));
  values[0] = 2;
  values[1] = 1;
  printf("\t\tList values should be [2, 1]: %d\n", assert_list(list, values, 2));

  printf("\tshould add a number at first when there are more than 2 elements\n");
  add_to_start(list, 3);
  printf("\t\tStatus should be Success: %d\n", assert(add_to_start(list, 4), Success));
  values[0] = 4;
  values[1] = 3;
  values[2] = 2;
  values[3] = 1;
  printf("\t\tList values should be [4, 3, 2, 1]: %d\n", assert_list(list, values, 4));
  destroy_list(list);
}

int main(void)
{
  test_add_to_end();
  test_add_to_start();
  return 0;
}