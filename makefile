#For more information check out http://www.cs.colby.edu/maxwell/courses/tutorials/maketutor/
# How to use make?
# go into the directory and type make
# this will build an exe which you run by tytping ./Wator
# you can run make clean to delete it and clean object files
# This is a very simple make file, more will be added to this to add in deps

CC=gcc
CFLAGS=-lX11 -lGL -lGLU -I. -fopenmp
APP=Wator

build: main.o
	$(CC) -o $(APP) main.o $(CFLAGS)

clean:
	rm *.o
	rm $(APP)