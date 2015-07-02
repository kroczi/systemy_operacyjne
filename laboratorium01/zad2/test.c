#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <sys/times.h>
#include <stdbool.h>
#include <unistd.h> 

#include "source.h"



#ifdef DLL 
#include <dlfcn.h>

int (*compare)(value v, value w);
value (*make_contact)(char name[], char surname[], char phone[], char email[], char address[], char date[]);
void (*print_contact)(value v);
list (*init)();
void (*add_after)(list *lista, node *p, value v);
void (*prepend)(list *lista, value v);
void (*append)(list *lista, value v);
void (*add_sorted)(list *lista, value v);
node* (*find)(list lista, char* name, char* surname);
value (*remove_at)(list *lista, node *p);
void (*destroy)(list *lista);
void (*print)(list lista);
void (*print_reverse)(list lista);
node* (*merge)(node* p, node* s, node* k);
node* (*merge_sort)(node* p, int size);
void (*sort)(list *lista);

 const char *error;
#endif




 char* word()
 {
 	int i;
 	
 	char *napis = (char*)malloc(11);
 	if(napis == NULL)
 	{
 		perror("Allocation failed.");
 		return "";
 	}

 	int len = 5 + rand()%6;
	for(i = 0; i < len; i++)
		napis[i] = 'a' + rand()%('z'-'a');
	napis[0] += 'A'-'a';
	napis[len] = '\0';
	
	return napis;
 }


 char* number()
 {
 	int i;
 	
 	char *napis = (char*)malloc(10);
 	if(napis == NULL)
 	{
 		perror("Allocation failed.");
 		return "";
 	}
	
	for(i = 0; i < 9; i++)
		napis[i] = '0' + rand()%('9'-'0');
	napis[9] = '\0';
	
	return napis;
 }
 

 void print_checkpoint(struct tms start, clock_t start_real, struct tms last, clock_t last_real, struct tms now, clock_t now_real)
 {
	int tps = sysconf(_SC_CLK_TCK);
 	printf("\tusr_time\tsys_time\treal_time\n");
	printf("last\t\t%lg\t\t%lg\t\t%lg\n", (double)(now.tms_utime - last.tms_utime)/(double)tps, (double)(now.tms_stime - last.tms_stime)/(double)tps, (double)(now_real - last_real)/(double)tps);
	printf("whole\t\t%lg\t\t%lg\t\t%lg\n", (double)(now.tms_utime - start.tms_utime)/(double)tps, (double)(now.tms_stime - start.tms_stime)/(double)tps, (double)(now_real - start_real)/(double)tps);
 }
 

 void checkpoint()
 {
 	static struct tms start, last, now;
	static clock_t start_real, last_real, now_real;
	static int index = 1;
	
	now_real = times(&now);

	if(index == 1)
	{
		start = now;
		start_real = now_real;
		printf("**Checkpoint 1. - Starting point**\n");
	}
	else
	{
		printf("__Checkpoint %d.__\n", index);	
		print_checkpoint(start, start_real, last, last_real, now, now_real);
	}

	last = now;
	last_real = now_real;
	index++;
 }
 


int main() 
{
	#ifdef DLL 

   void *Biblioteka = dlopen("liblib_dyn.so", RTLD_LAZY);
   error = dlerror();
   printf("\n    Otwarcie biblioteki \"liblib_dyn\", rezultat -%s- \n", error);
   if( error ) return(1);

   compare = dlsym(Biblioteka, "compare");
   error = dlerror();
   printf("    Szukanie funkcji \"compare\", rezultat -%s- \n", error);
   if( error ) return(1);
   
   make_contact = dlsym(Biblioteka, "make_contact");
   error = dlerror();
   printf("    Szukanie funkcji \"make_contact\", rezultat -%s- \n", error);
   if( error ) return(1);

   print_contact = dlsym(Biblioteka, "print_contact");
   error = dlerror();
   printf("    Szukanie funkcji \"print_contact\", rezultat -%s- \n", error);
   if( error ) return(1);
   
   init = dlsym(Biblioteka, "init");
   error = dlerror();
   printf("    Szukanie funkcji \"init\", rezultat -%s- \n", error);
   if( error ) return(1);
   
   add_after = dlsym(Biblioteka, "add_after");
   error = dlerror();
   printf("    Szukanie funkcji \"add_after\", rezultat -%s- \n", error);
   if( error ) return(1);
   
   prepend = dlsym(Biblioteka, "prepend");
   error = dlerror();
   printf("    Szukanie funkcji \"prepend\", rezultat -%s- \n", error);
   if( error ) return(1);
   
   append = dlsym(Biblioteka, "append");
   error = dlerror();
   printf("    Szukanie funkcji \"append\", rezultat -%s- \n", error);
   if( error ) return(1);

   add_sorted = dlsym(Biblioteka, "add_sorted");
   error = dlerror();
   printf("    Szukanie funkcji \"add_sorted\", rezultat -%s- \n", error);
   if( error ) return(1);
   
   find = dlsym(Biblioteka, "find");
   error = dlerror();
   printf("    Szukanie funkcji \"find\", rezultat -%s- \n", error);
   if( error ) return(1);
   
   remove_at = dlsym(Biblioteka, "remove_at");
   error = dlerror();
   printf("    Szukanie funkcji \"remove_at\", rezultat -%s- \n", error);
   if( error ) return(1);
   
   destroy = dlsym(Biblioteka, "destroy");
   error = dlerror();
   printf("    Szukanie funkcji \"destroy\", rezultat -%s- \n", error);
   if( error ) return(1);
   
   print = dlsym(Biblioteka, "print");
   error = dlerror();
   printf("    Szukanie funkcji \"print\", rezultat -%s- \n", error);
   if( error ) return(1);
   
   print_reverse = dlsym(Biblioteka, "print_reverse");
   error = dlerror();
   printf("    Szukanie funkcji \"print_reverse\", rezultat -%s- \n", error);
   if( error ) return(1);

   sort = dlsym(Biblioteka, "sort");
   error = dlerror();
   printf("    Szukanie funkcji \"sort\", rezultat -%s- \n", error);
   if( error ) return(1);

   printf("\n\n");
   
   #endif


	checkpoint();
	
    int i, zarodek;
    zarodek= time(NULL);
    srand(zarodek);   

	printf("\n\nCreating...\n\n");

	list lista = init();


    for(i= 1; i<= 8149692; ++i)
		prepend(&lista, make_contact(word(), word(), number(), "", "", ""));

	checkpoint();

	printf("\n\nSorting...\n\n");
	value contact = lista.head->x;
	sort(&lista);
        
	checkpoint();

	printf("\n\nSearching...\n\n");
	find(lista, contact.name, contact.surname);
	//if(found != NULL)
	//	print_contact(found->x);

	checkpoint();

	printf("\n\nDeleting...\n\n");
	destroy(&lista);

	checkpoint();
	



	#ifdef DLL 
    
   printf("\n\n");

   int stan = dlclose(Biblioteka);
   error = dlerror();
   printf("    Zamykanie biblioteki \"liblib_dyn\", rezultat -%s-\n", error); 
   if( stan ) return(1);

    #endif

    return 0;
}
