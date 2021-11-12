p6:
	gcc -Wall -g p6.c -o p6.out

b100:
	./p6.out read "BlackSquare(100x100).bmp" BS100.txt

black:
	./p6.out read "BlackSquare(97x97).bmp" BS97.txt
	./p6.out read "BlackSquare(98x98).bmp" BS98.txt
	./p6.out read "BlackSquare(99x99).bmp" BS99.txt
	./p6.out read "BlackSquare(100x100).bmp" BS100.txt

clean:
	if [ -a BS97.txt ]; then rm BS97.txt; fi;
	if [ -a BS98.txt ]; then rm BS98.txt; fi;
	if [ -a BS99.txt ]; then rm BS99.txt; fi;
	if [ -a BS100.txt ]; then rm BS100.txt; fi;
