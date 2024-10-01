stat: pointcloud.o
	gcc pointcloud.o -o stat -lm

pointcloud.o: pointcloud.c pointcloud.h
	gcc -c pointcloud.c -lm


util.o: util.c util.h
	gcc -c util.c -lm
	
clean:
	rm -f *.o stat list a.out
	rm -f *.gif

display:  display.o pointcloud.o util.o bmp.o
	gcc display.o -o display -lm

display.o:
	gcc display.c -o -lm

bmp.o: bmp.c bmp.h
	gcc -c bmp.c -lm