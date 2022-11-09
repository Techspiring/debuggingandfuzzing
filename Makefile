# Copyright 2022 Kevin Mader
# Author: Kevin Mader <mail@kevin-mader.de>

# How to improve the testing (randomness)
# do directed test (whitebox test)
# Find the overflow-bug

CC = ../tcc/tcc.exe
CFLAGS = -pedantic -Wall -Wextra -Werror -Wformat-signedness

.PHONY: all clean compile test testBroken

# Erstelle alle Binärdateien und führe alle Tests aus.
all: compile test testBroken

# Lösche alle erstellten Dateien
clean:
	del *.exe
	del build\*.o

# Kompiliere alle Dateien
compile: exercise01Test.exe 
#exercise01TestBroken.exe

build/sortstuff_broken.o: sortstuff_broken.c
	$(CC) $(CFLAGS) -c $^ -o $@
	
build/sortstuff.o: sortstuff.c
	$(CC) $(CFLAGS) -c $^ -o $@

build/exercise01Test.o: exercise01Test.c
	$(CC) $(CFLAGS) -c $^ -o $@

exercise01Test.exe: build/sortstuff.o build/exercise01Test.o
	$(CC) $(CFLAGS) $^ -o $@
	
#exercise01TestBroken.exe: build/sortstuff_broken.o build/exercise01Test.o
#	$(CC) $(CFLAGS) $^ -o $@

test:
	./exercise01Test.exe

#testBroken:
#	./exercise01TestBroken.exe