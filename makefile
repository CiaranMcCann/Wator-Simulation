#For more information check out http://www.cs.colby.edu/maxwell/courses/tutorials/maketutor/
# How to use make?
# go into the directory and type make
# this will build an exe which you run by tytping ./Wator
# you can run make clean to delete it and clean object files
# This is a very simple make file, more will be added to this to add in deps

CC=gcc
CFLAGS=-I.

Wator: main.o main.o	
	$(CC) -o Wator main.o $(CFLAGS).	

clean:
	rm Wator
	rm *.o
