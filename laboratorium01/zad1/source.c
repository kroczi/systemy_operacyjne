#include <stdio.h>
#include <string.h>
#include <stdbool.h>
#include <stdlib.h>
#include "source.h"


/*______________Contact______________*/

int compare(value v, value w)
{
	if(strcmp(v.surname, w.surname) > 0)
		return 1;
	if(strcmp(v.surname, w.surname) < 0)
		return -1;

	if(strcmp(v.name, w.name) > 0)
		return 1;
	if(strcmp(v.name, w.name) < 0)
		return -1;

	return 0;
}

value make_contact(char name[], char surname[], char phone[], char email[], char address[], char date[])
{
	value v;
	v.name = name;
	v.surname = surname;
	v.phone = phone;
	v.email = email;
	v.address = address;
	v.date = date;
	return v;
}

void print_contact(value v)
{
	printf("%s %s %s %s %s %s\n", v.name, v.surname, v.phone, v.email, v.address, v.date);
}



/*______________Creating______________*/

list init()
{
	list lista;
	lista.head = NULL;
	lista.tail = NULL;
	lista.length = 0;
	lista.sorted = true;
	return lista;
}

/*______________Inserting______________*/

void add_after(list *lista, node *p, value v)               //Dodaje za element wskazywany przez p
{
	if(p == NULL)
	{
		perror("NULL pointer.");
		return;
	}

	node *s = malloc(sizeof(node));
	if(s == NULL)
	{
		perror("Memory allocation failed.");
		return;
	}

	s->x = v;
	s->next = p->next;
	s->prev = p;

	if(p->next != NULL)
		p->next->prev = s;
	else
		lista->tail = s;

	if(lista->sorted == true && (compare(p->x, v) == 1 || (s->next != NULL && compare(v, s->next->x) == 1)))
		lista->sorted = false;

	p->next=s;
	lista->length +=1;
}

void prepend(list *lista, value v)            				//Dodaje na poczatek
{
	node *s = malloc(sizeof(node));
	if(s == NULL)
	{
		perror("Memory allocation failed.");
		return;
	}

	s->x = v;
	s->next = lista->head;
	s->prev = NULL;

	if(lista->head != NULL)
		lista->head->prev = s;
	else
		lista->tail = s;

	if(lista->sorted == true && lista->head != NULL && compare(v, lista->head->x) == 1)
		lista->sorted = false;

	lista->head = s;
	lista->length +=1;
}

void append(list *lista, value v)            				//Dodaje na koniec
{
	add_after(lista, lista->tail, v);
}

void add_sorted(list *lista, value v)
{
	if(lista->sorted == false)
		return;

	node *temp = lista->head;
	while(temp != NULL && compare(v, temp->x) >= 0)
		temp = temp->next;

	if(temp == lista->head)
		prepend(lista, v);
	else
	if(temp == NULL)
		append(lista, v);
	else
		add_after(lista, temp->prev, v);
}

/*______________Searching______________*/

node* find(list lista, char* name, char* surname)
{
	value v = make_contact(name, surname, "", "", "", "");

	node *temp = lista.head;
	if(lista.sorted)
		while(temp != NULL && compare(v, temp->x) == 1)
			temp = temp->next;
	else
		while(temp != NULL && compare(v, temp->x) != 0)
			temp = temp->next;

	if(temp != NULL && compare(v, temp->x) == 0)
		return temp;

	return NULL;
}

/*______________Deleting______________*/

value remove_at(list *lista, node *p)
{
	value v = p->x;
	if(p == lista->head)
	{
		lista->head = lista->head->next;
		lista->head->prev = NULL;
	}
	else 
	if(p->next == NULL)
	{
		p->prev->next = NULL;
		lista->tail = p->prev;
	}
	else
	{
		p->next->prev = p->prev;
		p->prev->next = p->next;
	}

	free(p);
	lista->length -= 1;
	return v;
}

void destroy(list *lista)
{
	while(lista->head != NULL)
	{
		node *temp = lista->head;
		lista->head = lista->head->next;
		free(temp);
	}
	lista->tail = NULL;
	lista->length = 0;
	lista->sorted = true;
}

/*______________Printing______________*/

void print(list lista)
{
	node *temp = lista.head;
	while(temp != NULL)
	{
		print_contact(temp->x);
		temp = temp->next;
	}
}

void print_reverse(list lista)
{
	node *temp = lista.tail;
	while(temp != NULL)
	{
		print_contact(temp->x);
		temp = temp->prev;
	}
}








/*______________Sorting______________*/

node* merge(node* p, node* s, node* k)   			//p-element przed pierwszym
{													//  elementem pierwszej czesci
	while(p!=s && s->next!=k)                       //s-element przed pierwszym
	{												//  elementem drugiej czesci
		if(compare(p->next->x, s->next->x) == 1)    //  (ostatni pierwszej)
		{											//k-element po ostatnim
			node *temp=s->next;                     //  elemencie drugiej czesci
			s->next=s->next->next;
			temp->next=p->next;
			p->next=temp;
			temp->prev = p;
			temp->next->prev = temp;
			if(s->next != NULL)
				s->next->prev = s;
		}
		p=p->next;
	}

	if(k != NULL)
		s = k->prev;
	else
		while(s->next!=k)                       //Zwraca wskaznik na ostatni element
			s=s->next;

	return s;
}

node* merge_sort(node* p, int size)   			//Zwraca wskaznik na ostatni element
{
	if(size==1)
		return p->next;

	node *s=merge_sort(p,(size+1)/2);
	node *k=merge_sort(s, size/2);

	return merge(p,s,k->next);
}


void sort(list *lista)
{
	if(lista->sorted == true || lista->head == NULL || lista->head->next == NULL)
		return;

	prepend(lista, make_contact("", "", "", "", "", ""));       //Tworzenie wartownika na poczatku
	
	merge_sort(lista->head,lista->length-1);        			//Sortowanie

	remove_at(lista, lista->head);                     			//Usuwanie wartownika
	lista->sorted = true;
}

