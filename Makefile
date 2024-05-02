objects = main.o bitmaplib.o filtres.o

program : $(objects)
	gcc -Wall -g -o projet $(objects)
	./projet

main.o : main.c bitmaplib.h filtres.h
	gcc -Wall -g -c main.c

bitmaplib.o : bitmaplib.c bitmaplib.h
	gcc -Wall -g -c bitmaplib.c

filtres.o : filtres.c filtres.h bitmaplib.h
	gcc -Wall -g -c filtres.c

clean :
	rm $(objects)