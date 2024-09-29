stat: pointcloud.o bmp.o
	gcc pointcloud.o -o stat -lm

pointcloud.o: pointcloud.c pointcloud.h
	gcc -c pointcloud.c

bmp.o: bmp.c bmp.h
	gcc -c bmp.c -lm

list: util.o
	gcc util.o -o list

util.o: util.c util.h
	gcc -c util.c
	
clean:
	rm -f *.o stat list a.out

remakeStat:
	make clean
	make stat