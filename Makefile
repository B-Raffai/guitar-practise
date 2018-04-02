all:
	gcc -g `pkg-config --cflags gtk+-3.0` -o main main.c download.c `pkg-config --libs gtk+-3.0`
