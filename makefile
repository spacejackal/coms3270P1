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

remakeStat:
	make clean
	make stat