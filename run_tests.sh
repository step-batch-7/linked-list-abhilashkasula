rm *.o test
gcc -c list.c tests.c && gcc -o test *.o && ./test

