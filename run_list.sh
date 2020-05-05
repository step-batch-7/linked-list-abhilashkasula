rm *.o main
gcc -c numbers.c list.c && gcc -o main *.o && ./main

