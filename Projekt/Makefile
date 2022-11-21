# Copyright 2019 Kevin Mader
# Author: Kevin Mader <mail@kevin-mader.de>

CC = gcc
CFLAGS = --std=c11 -pedantic -Wformat-signedness -Wall -Werror
LIBRARIES = -lGLESv1_CM -lglfw -I. -lm

.PHONY: all clean compile test style all checkstyle

# Erstelle alle Binärdateien und führe alle Tests aus.
all: compile test checkstyle

compile: 4 connectFourTest

connectFour.o: connectFour.c
	$(CC) $(CFLAGS) -c $^ -o $@

connectFourNpc.o: connectFourNpc.c
	$(CC) $(CFLAGS) -c $^ -o $@

connectFourMain.o: connectFourMain.c
	$(CC) $(CFLAGS) -c $^ -o $@

connectFourTest.o: connectFourTest.c
	$(CC) $(CFLAGS) -c $^ -o $@

connectFourGles.o: connectFourGles.c
	$(CC) $(CFLAGS) -c connectFourGles.c $(LIBRARIES)

4: connectFourMain.o connectFour.o connectFourNpc.o connectFourGles.o
	$(CC) $(CFLAGS) $^ -o $@ $(LIBRARIES)

connectFourTest: connectFourTest.o connectFour.o
	$(CC) $(CFLAGS) $^ -o $@

clean:
	rm -f *Main
	rm -f *Test
	rm -f *Fail
	rm -f *.o
	rm -f 4

test:
	./connectFourTest

checkstyle:
	python ../cpplint.py --filter=-readability/casting --repository=. *.c
	python ../cpplint.py --filter=-readability/casting --repository=. *.h