# Name of executable and its dependencies
sort: sort.o quicksort.o
# Must be tab:
	gcc sort.o quicksort.o -o sort 
sort.o: sort.c
	gcc -Wall -Werror -pedantic-errors -c sort.c
quicksort.o: quicksort.c quicksort.h
	gcc -Wall -Werror -pedantic-errors -c quicksort.c
clean:
	rm -f *.o sort sort.exe