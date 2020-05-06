#include <stdio.h>
#include "assert.h"

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
