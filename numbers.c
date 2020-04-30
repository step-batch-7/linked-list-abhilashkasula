#include "list.h"

int main(void)
{
  List_ptr numbers = create_list();
  add_to_end(numbers, 5);
  add_to_end(numbers, 7);
  add_to_start(numbers, 8);
  add_to_start(numbers, 10);
  display(numbers);
  clear_list(numbers);
  destroy_list(numbers);
  return 0;
}