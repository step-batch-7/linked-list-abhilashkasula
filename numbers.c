#include <stdio.h>
#include <stdlib.h>
#include "list.h"

#define NUMBER_TEXT "Enter a number:"
#define POSITION_TEXT "Enter position:"

typedef void (*Operate_on_list)(List_ptr);

void read_number(char *text, int *value)
{
  printf("%s\n", text);
  scanf("%d", value);
}

void print_exist_status(List_ptr numbers)
{
  int value;
  read_number(NUMBER_TEXT, &value);
  Status includes = is_exists(numbers, value);
  if (includes)
  {
    printf("%d exists\n", value);
  }
  else
  {
    printf("%d not exists\n", value);
  }
}

void perform_add_to_end(List_ptr numbers)
{
  int value;
  read_number(NUMBER_TEXT, &value);
  add_to_end(numbers, value);
}

void perform_add_to_start(List_ptr numbers)
{
  int value;
  read_number(NUMBER_TEXT, &value);
  add_to_start(numbers, value);
}

void perform_insert_at(List_ptr numbers)
{
  int value, position;
  read_number(NUMBER_TEXT, &value);
  read_number(POSITION_TEXT, &position);
  insert_at(numbers, value, position);
}

void perform_add_unique(List_ptr numbers)
{
  int value;
  read_number(NUMBER_TEXT, &value);
  add_unique(numbers, value);
}

void perform_remove_from_start(List_ptr numbers)
{
  remove_from_start(numbers);
}

void perform_remove_from_end(List_ptr numbers)
{
  remove_from_end(numbers);
}

void perform_remove_at(List_ptr numbers)
{
  int position;
  read_number(POSITION_TEXT, &position);
  remove_at(numbers, position);
}

void perform_remove_first_occurrence(List_ptr numbers)
{
  int value;
  read_number(NUMBER_TEXT, &value);
  remove_first_occurrence(numbers, value);
}

void perform_remove_all_occurrences(List_ptr numbers)
{
  int value;
  read_number(NUMBER_TEXT, &value);
  remove_all_occurrences(numbers, value);
}

void perform_clear_list(List_ptr numbers)
{
  clear_list(numbers);
}

void operate(List_ptr numbers, char choice)
{
  Operate_on_list operations[12] = {
      &perform_add_to_end,
      &perform_add_to_start,
      &perform_insert_at,
      &perform_add_unique,
      &perform_remove_from_start,
      &perform_remove_from_end,
      &perform_remove_at,
      &perform_remove_first_occurrence,
      &perform_remove_all_occurrences,
      &perform_clear_list,
      &print_exist_status,
      &display};

  unsigned int operation_index = choice % 97;

  if (operation_index > 11 || operation_index < 0)
  {
    printf("Please enter a valid choice\n");
    return;
  }

  Operate_on_list operation = operations[choice % 97];
  (*operation)(numbers);
}

void print_menu()
{
  printf("Main Menu\n---------\n");
  printf("(a) add a number to the end of the list\n(b) add a number to the start of the list\n");
  printf("(c) insert a number at a given position in the list\n");
  printf("(d) add a unique item on the list at the end(if it already exists, do not insert)\n");
  printf("(e) remove a number from the beginning of the list\n(f) remove a number from the end of the list\n");
  printf("(g) remove a number from a given position in the list\n(h) remove first occurrence of a number\n");
  printf("(i) remove all occurrences of a number\n(j) clear the whole list\n");
  printf("(k) check if a number exists in the list\n(l) display the list of numbers\n");
  printf("(m) exit\n\nPlease enter the alphabet of the operation you would like to perform\n");
}

void read_choice(char *choice)
{
  print_menu();
  scanf("%c", choice);
}

void clear_buffer()
{
  while (getchar() != '\n')
  {
  }
}

int main(void)
{
  List_ptr numbers = create_list();

  if (numbers == NULL)
  {
    return 1;
  }

  char choice;
  read_choice(&choice);

  while (choice != 'm')
  {
    operate(numbers, choice);
    clear_buffer();
    read_choice(&choice);
  }

  destroy_list(numbers);
  return 0;
}
