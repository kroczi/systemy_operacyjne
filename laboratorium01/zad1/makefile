

object:		source.c
	gcc -fPIC -Wall -c -o obj.o source.c


static:		object
	ar src liblib_stat.a obj.o


dynamic:	object
	gcc -shared -fPIC -o liblib_dyn.so obj.o


clean:
	rm -f *.o *.so* *.a