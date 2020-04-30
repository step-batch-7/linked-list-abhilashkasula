#include <stdio.h>
#include <stdlib.h>
#include "list.h"

void operate(List_ptr numbers, char choice)
{
  int value;
  int position;
  printf("---%c---\n", choice);
  switch (choice)
  {
  case 'a':
    printf("Enter a number:\n");
    scanf("%d", &value);
    add_to_end(numbers, value);
    break;
  case 'b':
    printf("Enter a number:\n");
    scanf("%d", &value);
    add_to_start(numbers, value);
    break;
  case 'c':
    printf("Enter a number:\n");
    scanf("%d", &value);
    printf("Enter position:\n");
    scanf("%d", &position);
    insert_at(numbers, value, position);
    break;
  case 'd':
    printf("Enter a number:\n");
    scanf("%d", &value);
    add_unique(numbers, value);
    break;
  case 'e':
    remove_from_start(numbers);
    break;
  }
}

void print_menu()
{
  printf("Main Menu\n---------\n");
  printf("(a) add a number to the end of the list\n(b) add a number to the start of the list\n");
  printf("(c) insert a number at a given position in the list\n");
  printf("(d) add a unique item on the list at the end(if it alreay exists, do not insert)\n");
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

int main(void)
{
  List_ptr numbers = create_list();
  char choice;
  read_choice(&choice);
  while (choice != 'm')
  {
    operate(numbers, choice);
    display(numbers);
    read_choice(&choice);
  }
  return 0;
}