rm *.o main
gcc -c list.c test/*.c && gcc -o main *.o && ./main

