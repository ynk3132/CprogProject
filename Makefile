all: 
	gcc -o manage point_manager.c
	./manage	

clean:
	rm -f *.o manage