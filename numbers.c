#include "list.h"

int main(void)
{
  List_ptr numbers = create_list();
  add_to_end(numbers, 5);
  add_to_end(numbers, 7);
  display(numbers);
  return 0;
}