objects = main.o bitmaplib.o filtres.o jpg_io.o

program : $(objects)
	gcc -Wall -g -o projet $(objects)
	# ./projet
	rm $(objects)

main.o : main.c bitmaplib.h filtres.h jpg_io.h
	gcc -Wall -g -c main.c

bitmaplib.o : bitmaplib.c bitmaplib.h
	gcc -Wall -g -c bitmaplib.c

filtres.o : filtres.c filtres.h bitmaplib.h
	gcc -Wall -g -c filtres.c

jpg_io.o : jpg_io.c jpg_io.h 
	gcc -Wall -g -c jpg_io.c -ljpeg

clean :
	rm $(objects)