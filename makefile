watershed:pointcloud.o util.o bmp.o watershed.o
	gcc  watershed.o util.o bmp.o pointcloud.o -o watershed -lm

watershed.o: watershed.c
	gcc -c watershed.c -lm

stat: pointcloud.o util.o bmp.o parta.o
	gcc parta.o util.o bmp.o pointcloud.o -o stat -lm

pointcloud.o: pointcloud.c pointcloud.h util.h bmp.h
	gcc -c pointcloud.c  -lm

parta.o: parta.c
	gcc -c parta.c

util.o: util.c util.h
	gcc -c util.c -lm
	
clean:
	rm -f *.o stat display watershed out list a.out
	rm -f *.gif imagePointCloud.out

display:  display.o pointcloud.o util.o bmp.o
	gcc pointcloud.o util.o bmp.o display.o -o display -lm 

display.o: display.c pointcloud.h util.h bmp.h
	gcc -c display.c -lm

bmp.o: bmp.c bmp.h
	gcc -c bmp.c -lm

remake:
	git pull
	make clean
	make watershed
	./watershed test2.xyz 1 10.2 1.0 0.0 out 20 1