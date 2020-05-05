#include <stdio.h>
#include "../list.h"

#define SUCCESS_TEXT "Status should be Success"
#define FAILURE_TEXT "Status should be Failure"

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

void display_assertion(Status status, char *text)
{
  if (status)
  {
    printf("\t\t✅  %s\n", text);
  }
  else
  {
    printf("\t\t❌  %s\n", text);
  }
}

void test_add_to_end(void)
{
  printf("add_to_end\n");

  List_ptr list = create_list();
  int expected_list[4] = {};
  display_assertion(assert_list(list, expected_list, 0), "No values");

  printf("\tshould add a number to list when there are no elements\n");
  display_assertion(assert(add_to_end(list, 1), Success), SUCCESS_TEXT);
  expected_list[0] = 1;
  display_assertion(assert_list(list, expected_list, 1), "List values should be [1]");

  printf("\tshould add a number at last when there is an element in the list\n");
  display_assertion(assert(add_to_end(list, 2), Success), SUCCESS_TEXT);
  expected_list[1] = 2;
  display_assertion(assert_list(list, expected_list, 2), "List values should be [1, 2]");

  printf("\tshould add a number at last when there are more than two elements in it\n");
  add_to_end(list, 3);
  expected_list[2] = 3;
  display_assertion(assert(add_to_end(list, 4), Success), SUCCESS_TEXT);
  expected_list[3] = 4;
  display_assertion(assert_list(list, expected_list, 4), "List values should be [1, 2, 3, 4]");

  destroy_list(list);
}

void test_add_to_start(void)
{
  printf("add_to_start\n");

  List_ptr list = create_list();
  int expected_list[4] = {};

  printf("\tshould add a number at first when there are no elements\n");
  display_assertion(assert(add_to_start(list, 1), Success), SUCCESS_TEXT);
  insert_in_array_at(expected_list, 0, 1, 0);
  display_assertion(assert_list(list, expected_list, 1), "List values should be [1]");

  printf("\tshould add a number at first when there is an element\n");
  display_assertion(assert(add_to_start(list, 2), Success), SUCCESS_TEXT);
  insert_in_array_at(expected_list, 1, 2, 0);
  display_assertion(assert_list(list, expected_list, 2), "List values should be [2, 1]");

  printf("\tshould add a number at first when there are more than 2 elements\n");
  add_to_start(list, 3);
  insert_in_array_at(expected_list, 2, 3, 0);
  display_assertion(assert(add_to_start(list, 4), Success), SUCCESS_TEXT);
  insert_in_array_at(expected_list, 3, 4, 0);
  display_assertion(assert_list(list, expected_list, 4), "List values should be [4, 3, 2, 1]");

  destroy_list(list);
}

void test_insert_at(void)
{
  printf("insert_at\n");

  List_ptr list = create_list();
  int expected_list[5] = {};

  printf("\tshould not add a number for the position 1 when the list is empty\n");
  display_assertion(assert(insert_at(list, 1, 1), Failure), FAILURE_TEXT);
  display_assertion(assert_list(list, expected_list, 0), "List values should be empty");

  printf("\tshould add number 1 for the position 0 when the list is empty\n");
  display_assertion(assert(insert_at(list, 1, 0), Success), SUCCESS_TEXT);
  expected_list[0] = 1;
  display_assertion(assert_list(list, expected_list, 1), "List values should be [1]");

  printf("\tshould add number 2 for the position 1 when the list contains only one number\n");
  display_assertion(assert(insert_at(list, 2, 1), Success), SUCCESS_TEXT);
  expected_list[1] = 2;
  display_assertion(assert_list(list, expected_list, 2), "List values should be [1, 2]");

  printf("\tshouldn't add number for the position out of range\n");
  display_assertion(assert(insert_at(list, 3, 8), Failure), FAILURE_TEXT);
  display_assertion(assert_list(list, expected_list, 2), "List values shouldn't be changed");

  printf("\tshould add number 3 at position 0 when values are present\n");
  display_assertion(assert(insert_at(list, 3, 0), Success), SUCCESS_TEXT);
  insert_in_array_at(expected_list, 2, 3, 0);
  display_assertion(assert_list(list, expected_list, 3), "List values should be [3, 1, 2]");

  printf("\tshould add number 4 at position 3 when the count of the list is 3\n");
  display_assertion(assert(insert_at(list, 4, 3), Success), SUCCESS_TEXT);
  expected_list[3] = 4;
  display_assertion(assert_list(list, expected_list, 4), "List values should be [3, 1, 2, 4]");

  printf("\tshould add number 5 at in the middle of the list at position 2\n");
  display_assertion(assert(insert_at(list, 5, 2), Success), SUCCESS_TEXT);
  insert_in_array_at(expected_list, 4, 5, 2);
  display_assertion(assert_list(list, expected_list, 5), "List values should be [3, 1, 5, 2, 4]");

  destroy_list(list);
}

void test_add_unique(void)
{
  printf("add_unique\n");

  List_ptr list = create_list();
  int expected_list[2];

  printf("\tshould add number 1 when the list is empty\n");
  display_assertion(assert(add_unique(list, 1), Success), SUCCESS_TEXT);
  expected_list[0] = 1;
  display_assertion(assert_list(list, expected_list, 1), "List values should be [1]");

  printf("\tshouldn't add number 1 again\n");
  display_assertion(assert(add_unique(list, 1), Failure), FAILURE_TEXT);
  display_assertion(assert_list(list, expected_list, 1), "List values should be [1]");

  printf("\tshould add number 2\n");
  display_assertion(assert(add_unique(list, 2), Success), SUCCESS_TEXT);
  expected_list[1] = 2;
  display_assertion(assert_list(list, expected_list, 2), "List values should be [1, 2]");

  destroy_list(list);
}

void test_remove_from_start(void)
{
  printf("remove_from_start\n");

  List_ptr list = create_list();
  add_to_end(list, 1);
  add_to_end(list, 2);
  add_to_end(list, 3);
  int expected_list[2] = {2, 3};

  printf("\tshould remove number from the start when there are more than 2 values\n");
  display_assertion(assert(remove_from_start(list), Success), SUCCESS_TEXT);
  display_assertion(assert_list(list, expected_list, 2), "Value should be deleted");

  printf("\tshould remove number form start when there are two values\n");
  display_assertion(assert(remove_from_start(list), Success), SUCCESS_TEXT);
  expected_list[0] = 3;
  display_assertion(assert_list(list, expected_list, 1), "Value should be deleted");

  printf("\tshould remove number when there is only one element\n");
  display_assertion(assert(remove_from_start(list), Success), SUCCESS_TEXT);
  display_assertion(assert_list(list, expected_list, 0), "List should be empty");

  printf("\tshould give Failure status for list is empty\n");
  display_assertion(assert(remove_from_start(list), Failure), FAILURE_TEXT);

  destroy_list(list);
}

void test_remove_from_end(void)
{
  printf("remove_from_end\n");

  List_ptr list = create_list();
  add_to_end(list, 1);
  add_to_end(list, 2);
  add_to_end(list, 3);
  int expected_list[2] = {1, 2};

  printf("\tshould remove number from the end when there are more than 2 values\n");
  display_assertion(assert(remove_from_end(list), Success), SUCCESS_TEXT);
  display_assertion(assert_list(list, expected_list, 2), "Last value should get deleted");

  printf("\tshould remove last number when ther are only two elements\n");
  display_assertion(assert(remove_from_end(list), Success), SUCCESS_TEXT);
  display_assertion(assert_list(list, expected_list, 1), "Last value should get deleted");

  printf("\tshould remove the number when there is only one element\n");
  display_assertion(assert(remove_from_end(list), Success), SUCCESS_TEXT);
  display_assertion(assert_list(list, expected_list, 0), "Value should get deleted");

  printf("\tshould give Failure status for list is empty\n");
  display_assertion(assert(remove_from_end(list), Failure), FAILURE_TEXT);

  destroy_list(list);
}

void test_remove_at(void)
{
  printf("remove_at\n");

  List_ptr list = create_list();
  for (int i = 1; i <= 5; i++)
  {
    add_to_end(list, i);
  }
  int expected_list[5] = {1, 2, 3, 4, 5};

  printf("\tshouldn't remove number for the position out of range\n");
  printf("\t   for position 10\n");
  display_assertion(assert(remove_at(list, 10), Failure), FAILURE_TEXT);
  display_assertion(assert_list(list, expected_list, 5), "List shouldn't modify");
  printf("\t   for position -1\n");
  display_assertion(assert(remove_at(list, -1), Failure), FAILURE_TEXT);
  display_assertion(assert_list(list, expected_list, 5), "List shouldn't modify");

  printf("\tshould remove the last value for position 4\n");
  display_assertion(assert(remove_at(list, 4), Success), SUCCESS_TEXT);
  display_assertion(assert_list(list, expected_list, 4), "Last value should get deleted");

  printf("\tshould remove the number from the middle at position 2\n");
  display_assertion(assert(remove_at(list, 2), Success), SUCCESS_TEXT);
  expected_list[2] = expected_list[3];
  expected_list[3] = expected_list[4];
  display_assertion(assert_list(list, expected_list, 3), "Value at 2 should be deleted");

  printf("\tshould remove the number from the star at position 0\n");
  display_assertion(assert(remove_at(list, 0), Success), SUCCESS_TEXT);
  expected_list[0] = expected_list[1];
  expected_list[1] = expected_list[2];
  display_assertion(assert_list(list, expected_list, 2), "Value at 0 should be deleted");

  printf("\tshould remove the number at pos 1 for two elements in list\n");
  display_assertion(assert(remove_at(list, 1), Success), SUCCESS_TEXT);
  display_assertion(assert_list(list, expected_list, 1), "Value at 1 should get deleted");

  destroy_list(list);
}

void test_remove_first_occurrence(void)
{
  printf("remove_first_occurrence\n");

  List_ptr list = create_list();
  add_to_end(list, 2);
  add_to_end(list, 2);
  int expected_list[1] = {2};

  printf("\tshould remove first occurrence\n");
  display_assertion(assert(remove_first_occurrence(list, 2), Success), SUCCESS_TEXT);
  display_assertion(assert_list(list, expected_list, 1), "First value should get deleted");

  printf("\tshould get Failure status when the number is not present to delete\n");
  display_assertion(assert(remove_first_occurrence(list, 5), Failure), SUCCESS_TEXT);
  display_assertion(assert_list(list, expected_list, 1), "List is not modified");

  printf("\tshould remove the value when there is only one element\n");
  display_assertion(assert(remove_first_occurrence(list, 2), Success), SUCCESS_TEXT);
  display_assertion(assert_list(list, expected_list, 0), "List should be empty");

  destroy_list(list);
}

void test_remove_all_occurrences(void)
{
  printf("remove_all_occurrences\n");

  List_ptr list = create_list();
  add_to_end(list, 2);
  add_to_end(list, 3);
  add_to_end(list, 2);
  add_to_end(list, 4);
  int expected_list[2] = {3, 4};

  printf("\tshould remove all occurrences of a value\n");
  display_assertion(assert(remove_all_occurrences(list, 2), Success), SUCCESS_TEXT);
  display_assertion(assert_list(list, expected_list, 2), "Values should get deleted");

  printf("\tshould get Failure status for no occurrence found\n");
  display_assertion(assert(remove_all_occurrences(list, 10), Failure), FAILURE_TEXT);
  display_assertion(assert_list(list, expected_list, 2), "Values should no modified");

  printf("\tshould remove one value when it is a unique value\n");
  display_assertion(assert(remove_all_occurrences(list, 4), Success), SUCCESS_TEXT);
  display_assertion(assert_list(list, expected_list, 1), "One value get deleted");

  printf("\tshould remove one value when there is only one element in list\n");
  display_assertion(assert(remove_all_occurrences(list, 3), Success), SUCCESS_TEXT);
  display_assertion(assert_list(list, expected_list, 0), "One value get deleted");

  printf("\tshould get Failure for list is empty\n");
  display_assertion(assert(remove_all_occurrences(list, 1), Failure), FAILURE_TEXT);
  display_assertion(assert_list(list, expected_list, 0), "List is empty");

  destroy_list(list);
}

int main(void)
{
  test_add_to_end();
  test_add_to_start();
  test_insert_at();
  test_add_unique();
  test_remove_from_start();
  test_remove_from_end();
  test_remove_at();
  test_remove_first_occurrence();
  test_remove_all_occurrences();
  return 0;
}