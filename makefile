stat: pointcloud.o bmp.o
	sudo gcc pointcloud.o -o stat `libpng-config --ldflags` -lz

pointcloud.o: pointcloud.c pointcloud.h
	gcc -c pointcloud.c

bmp.o: bmp.c bmp.h
	sudo gcc -c bmp.c -DUSEPNG `libpng-config --cflags`

list: util.o
	gcc util.o -o list

util.o: util.c util.h
	gcc -c util.c
	
clean:
	rm -f *.o stat list a.out

remakeStat:
	make clean
	make stat