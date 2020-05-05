rm *.o main
gcc -c list.c test/tests.c && gcc -o main *.o && ./main

