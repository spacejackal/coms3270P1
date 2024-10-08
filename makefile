stat: pointcloud.o util.o
	gcc pointcloud.o util.o -o stat -lm

pointcloud.o: pointcloud.c pointcloud.h util.h bmp.h
	gcc -c pointcloud.c  -lm


util.o: util.c util.h
	gcc -c util.c -lm
	
clean:
	rm -f *.o stat list a.out
	rm -f *.gif

display:  display.o pointcloud.o util.o bmp.o
	gcc pointcloud.o util.o bmp.o display.o -o display -lm 

display.o: display.c pointcloud.h util.h bmp.h
	gcc -c display.c -lm

bmp.o: bmp.c bmp.h
	gcc -c bmp.c -lm