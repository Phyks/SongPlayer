all : generateur.out


generateur.out : generateur.c wave_stuff.o
	gcc -lm -o generateur.out generateur.c wave_stuff.o


wave_stuff.o : wave_stuff.c wave_stuff.h
	gcc -c wave_stuff.c
