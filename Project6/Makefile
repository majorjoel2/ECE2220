p6:
	gcc -Wall -g p6.c -o p6.out

black:
	./p6.out read "BlackSquare(97x97).bmp" BS97.txt
	./p6.out read "BlackSquare(98x98).bmp" BS98.txt
	./p6.out read "BlackSquare(99x99).bmp" BS99.txt
	./p6.out read "BlackSquare(100x100).bmp" BS100.txt

white:
	./p6.out read "WhiteSquare(97x97).bmp" WS97.txt
	./p6.out read "WhiteSquare(98x98).bmp" WS98.txt
	./p6.out read "WhiteSquare(99x99).bmp" WS99.txt
	./p6.out read "WhiteSquare(100x100).bmp" WS100.txt

orange:
	./p6.out read "OrangeSquare(97x97).bmp" OS97.txt
	./p6.out read "OrangeSquare(98x98).bmp" OS98.txt
	./p6.out read "OrangeSquare(99x99).bmp" OS99.txt
	./p6.out read "OrangeSquare(100x100).bmp" OS100.txt

other:
	./p6.out read "CU.bmp" CUO.txt
	./p6.out read "Tiger.bmp" TIGO.txt
	./p6.out read "USC.bmp" LOSERO.txt

edgeb:
	./p6.out edge "BlackSquare(97x97).bmp"
	./p6.out edge "BlackSquare(98x98).bmp"
	./p6.out edge "BlackSquare(99x99).bmp"
	./p6.out edge "BlackSquare(100x100).bmp"

edgew:
	./p6.out edge "WhiteSquare(97x97).bmp"
	./p6.out edge "WhiteSquare(98x98).bmp"
	./p6.out edge "WhiteSquare(99x99).bmp"
	./p6.out edge "WhiteSquare(100x100).bmp"

edgeor:
	./p6.out edge "OrangeSquare(97x97).bmp"
	./p6.out edge "OrangeSquare(98x98).bmp"
	./p6.out edge "OrangeSquare(99x99).bmp"
	./p6.out edge "OrangeSquare(100x100).bmp"

edgeot:
	./p6.out edge "CU.bmp"
	./p6.out edge "Tiger.bmp"
	./p6.out edge "USC.bmp"

read:
	touch black
	touch white
	touch orange
	touch other

edge:
	touch edgeb
	touch edgew
	touch edgeor
	touch edgeot

all:
	touch read
	touch edge

clean:
	-find *-edge.bmp -type f -delete
	-find *.txt -type f -delete
