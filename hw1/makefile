test:test.o
	gcc -o test test.o

test.o:test.c storage_mgr.h storage_mgr.o
	 gcc -c storage_mgr.o test.c

storage_mgr.o:storage_mgr.c
	 gcc -c storage_mgr.c

clean:
	rm -f *.o test
