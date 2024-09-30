stat: pointcloud.o
	gcc pointcloud.o -o stat 

pointcloud.o: pointcloud.c pointcloud.h
	gcc -c pointcloud.c

list: util.o
	gcc util.o -o list

util.o: util.c util.h
	gcc -c util.c
	
clean:
	rm -f *.o stat list a.out
	rm -f *.gif

imageGen: pointcloud.o bmp.o display.o util.o
	gcc display.o -o -lm

display.o:
	gcc display.c -o -lm

bmp.o: bmp.c bmp.h
	gcc -c bmp.c -lm