test:test.o storage.o
	gcc -o test test.o storage.o

test.o:test.c storage_mgr.o storage_mgr.h
	 gcc -c storage_mgr.o test.c

storage_mgr.o:storage_mgr.c
	 gcc -c storage_mgr.c

clean:
	rm -f *.o test
