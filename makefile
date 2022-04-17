output:main.o malloc.o
	gcc main.c -o output


main.o:main.c 
	gcc -c main.c


malloc.o:malloc.c 
	gcc -c malloc.c


clean:
	rm *.o output
© 2022 GitHub, Inc.
Terms
