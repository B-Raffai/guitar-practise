FLAGS = `pkg-config --cflags gtk+-3.0 vte-2.91`
LIBS = `pkg-config --libs gtk+-3.0 vte-2.91`
all:
	gcc -g $(FLAGS) -o main main.c download.c $(LIBS)
