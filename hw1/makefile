test:test.o storage_mgr.o
	gcc -o test test.o storage_mgr.o dberror.h

test.o:test.c 
	 gcc -c test.c

storage_mgr.o:storage_mgr.c
	 gcc -c storage_mgr.c

clean:
	rm -f *.o test
