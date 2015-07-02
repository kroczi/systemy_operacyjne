VPATH = ../zad1



object:		$(VPATH)/source.c
	gcc -fPIC -Wall -c -o obj.o $(VPATH)/source.c



run_stat:	link_stat
	./prog_stat

link_stat:	create_stat 
	gcc -Wall -o prog_stat test.c -I$(VPATH) -L. -llib_stat

create_stat:	object
	ar src liblib_stat.a obj.o



run_dyn:	link_dyn
	./prog_dyn

link_dyn:	create_dyn
	gcc -Wall -Wl,-rpath=`pwd` -o prog_dyn test.c -I$(VPATH) -L. -llib_dyn

create_dyn:		object
	gcc -shared -fPIC -o liblib_dyn.so obj.o



run_DLL:	link_DLL
	./prog_DLL

link_DLL:	create_dyn
	gcc -Wall -Wl,-rpath=`pwd` -D DLL -o prog_DLL test.c -I$(VPATH) -ldl




clean:
	rm -f *.o prog_* *.so* *.a