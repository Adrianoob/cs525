test:test.o storage_mgr.o dberror.o
	gcc -o test test.o storage_mgr.o dberror.o

test.o:test.c 
	 gcc -c test.c

storage_mgr.o:storage_mgr.c dberror.c
	 gcc -c storage_mgr.c dberror.c

clean:
	rm -f *.o test
