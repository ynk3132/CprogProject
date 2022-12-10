all: 
	gcc -o point_manage point_manager.c
	./point_manage	

clean:
	rm -f *.o point_manage