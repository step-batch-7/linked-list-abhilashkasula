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

void insert_in_array_at(int *array, int length, int value, int pos)
{
  for (int i = length; i > pos; i--)
  {
    array[i] = array[i - 1];
  }
  array[pos] = value;
}

void test_add_to_end(void)
{
  printf("add_to_end\n");

  List_ptr list = create_list();
  int expected_list[4] = {};
  printf("\tNo values: %d\n", assert_list(list, expected_list, 0));

  printf("\tshould add a number to list when there are no elements\n");
  printf("\t\tStatus should be Success: %d\n", assert(add_to_end(list, 1), Success));
  expected_list[0] = 1;
  printf("\t\tList values should be [1]: %d\n", assert_list(list, expected_list, 1));

  printf("\tshould add a number at last when there is an element in the list\n");
  printf("\t\tStatus should be Success: %d\n", assert(add_to_end(list, 2), Success));
  expected_list[1] = 2;
  printf("\t\tList values should be [1, 2]: %d\n", assert_list(list, expected_list, 2));

  printf("\tshould add a number at last when there are more than two elements in it\n");
  add_to_end(list, 3);
  expected_list[2] = 3;
  printf("\t\tStatus should be Success: %d\n", assert(add_to_end(list, 4), Success));
  expected_list[3] = 4;
  printf("\t\tList values should be [1, 2, 3, 4]: %d\n", assert_list(list, expected_list, 4));
  destroy_list(list);
}

void test_add_to_start(void)
{
  printf("add_to_start\n");

  List_ptr list = create_list();
  int expected_list[4] = {};
  printf("\tNo values: %d\n", assert_list(list, expected_list, 0));

  printf("\tshould add a number at first when there are no elements\n");
  printf("\t\tStatus should be Success: %d\n", assert(add_to_start(list, 1), Success));
  insert_in_array_at(expected_list, 0, 1, 0);
  printf("\t\tList values should be [1]: %d\n", assert_list(list, expected_list, 1));

  printf("\tshould add a number at first when there is an element\n");
  printf("\t\tStatus should be Success: %d\n", assert(add_to_start(list, 2), Success));
  insert_in_array_at(expected_list, 1, 2, 0);
  printf("\t\tList values should be [2, 1]: %d\n", assert_list(list, expected_list, 2));

  printf("\tshould add a number at first when there are more than 2 elements\n");
  add_to_start(list, 3);
  insert_in_array_at(expected_list, 2, 3, 0);
  printf("\t\tStatus should be Success: %d\n", assert(add_to_start(list, 4), Success));
  insert_in_array_at(expected_list, 3, 4, 0);
  printf("\t\tList values should be [4, 3, 2, 1]: %d\n", assert_list(list, expected_list, 4));
  destroy_list(list);
}

void test_insert_at(void)
{
  printf("insert_at\n");

  List_ptr list = create_list();
  int expected_list[5] = {};
  printf("\tNo values: %d\n", assert_list(list, expected_list, 0));

  printf("\tshould not add a number for the position 1 when the list is empty\n");
  printf("\t\tStatus should be Failure: %d\n", assert(insert_at(list, 1, 1), Failure));
  printf("\t\tList values should be empty: %d\n", assert_list(list, expected_list, 0));

  printf("\tshould add number 1 for the position 0 when the list is empty\n");
  printf("\t\tStatus should be Success: %d\n", assert(insert_at(list, 1, 0), Success));
  expected_list[0] = 1;
  printf("\t\tList values should be [1]: %d\n", assert_list(list, expected_list, 1));

  printf("\tshould add number 2 for the position 1 when the list contains only one number\n");
  printf("\t\tStatus should be Success: %d\n", assert(insert_at(list, 2, 1), Success));
  expected_list[1] = 2;
  printf("\t\tList values should be [1, 2]: %d\n", assert_list(list, expected_list, 2));

  printf("\tshouldn't add number for the position out of range\n");
  printf("\t\tStatus should be Failure: %d\n", assert(insert_at(list, 3, 8), Failure));
  printf("\t\tList values shouldn't be changed: %d\n", assert_list(list, expected_list, 2));

  printf("\tshould add number 3 at position 0 when values are present\n");
  printf("\t\tStatus should be Success: %d\n", assert(insert_at(list, 3, 0), Success));
  insert_in_array_at(expected_list, 2, 3, 0);
  printf("\t\tList values should be [3, 1, 2]: %d\n", assert_list(list, expected_list, 3));

  printf("\tshould add number 4 at position 3 when the count of the list is 3\n");
  printf("\t\tStatus should be Success: %d\n", assert(insert_at(list, 4, 3), Success));
  expected_list[3] = 4;
  printf("\t\tList values should be [3, 1, 2, 4]: %d\n", assert_list(list, expected_list, 4));

  printf("\tshould add number 5 at in the middle of the list at position 2\n");
  printf("\t\tStatus should be Success: %d\n", assert(insert_at(list, 5, 2), Success));
  insert_in_array_at(expected_list, 4, 5, 2);
  printf("\t\tList values should be [3, 1, 5, 2, 4]: %d\n", assert_list(list, expected_list, 5));
}

int main(void)
{
  test_add_to_end();
  test_add_to_start();
  test_insert_at();
  return 0;
}