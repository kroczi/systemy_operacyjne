#ifndef SysOpy
#define SysOpy


typedef struct
{
	char* name;
	char* surname;
	char* phone;
	char* email;
	char* address;
	char* date;
} value;

typedef struct node
{
	value x;
	struct node *next;
	struct node *prev;
} node;

typedef struct list
{
	int length;
	node *head;
	node *tail;
	bool sorted;
} list;


#ifndef DLL

int compare(value v, value w);

value make_contact(char name[], char surname[], char phone[], char email[], char address[], char date[]);

void print_contact(value v);

list init();

void add_after(list *lista, node *p, value v);

void prepend(list *lista, value v);

void append(list *lista, value v);

void add_sorted(list *lista, value v);

node* find(list lista, char* name, char* surname);

value remove_at(list *lista, node *p);

void destroy(list *lista);

void print(list lista);

void print_reverse(list lista);

node* merge(node* p, node* s, node* k);

node* merge_sort(node* p, int size);

void sort(list *lista);

#endif


#endif