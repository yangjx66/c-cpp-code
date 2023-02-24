/**
 * @file main.c
 * @author your name (you@domain.com)
 * @brief 
 * @version 0.1
 * @date 2023-02-20
 * 
 * @copyright Copyright (c) 2023
 * 
 */

#include <stdio.h>
#include <stdlib.h>
#include <malloc.h>
#include <string.h>

#define DEBUG(x) printf("%d\r\n", x)

typedef enum {
	POSITIVE = 0, REVERSE = !POSITIVE
} TraversDirection;

struct Data {
	int id;
	float price;
	char name[20];
};

typedef struct Node {
	struct Data data;
	struct Node *last;
	struct Node *next;
} Node;

static Node *Head = NULL;
static Node *next = NULL;
static Node *last = NULL;
static Node *tmp = NULL;

FILE *data_file = NULL;

// Init the head node of target linklist
void Init_LinkList(Node *p)
{	
	p->data.id = 0x00000000;
	p->data.price = 0.0f;
	strcpy(p->data.name, "null");
	
	p->last = p;
	p->next = p;
	
//	printf("p = %d %f %s %#X %#X\r\n",p->data.id, p->data.price, p->data.name, p->last, p->next);
}

// start input data, and store them to the linklist(header is Head)
void input_data(Node *head)
{
	tmp = head;
	
	last = tmp->last;
	next = tmp->next;
	char *null = "null";
	while (1)
	{
		printf("\r\n");
		scanf("%s%d%f", &tmp->data.name, &tmp->data.id, &tmp->data.price);
		printf("[OK!] Title: %s    ID: %d    Price: %.2f \r\n", tmp->data.name,tmp->data.id, tmp->data.price);
		
		if (strcmp(tmp->data.name, null) != 0) // string compare, is "null"?
		{
			last->next = tmp;
			tmp->last = last;
			last = tmp;
			
			tmp = malloc(sizeof(Node));
		}
		else
		{
//			last->last = tmp;
			last->next = head;
			head->last = last;
			
			free(tmp);
			tmp = NULL;
			
			break;
		}
	}
}

// travers LinkedList from the specified node and manually select positive or reverse.
void travers_linkedlist(Node *base, TraversDirection dir)
{
	Node *tmp = base;
	int i = 0;

	if (dir == POSITIVE) // forward
	{
		printf("\r\n");
	
		do {
			printf("Node %3d:  addr = %#X   last = %#X  next = %#X  data.id = %3d  data.name = %20s  data.price = %.2f\r\n", i, tmp, tmp->last, tmp->next, tmp->data.id, tmp->data.name, tmp->data.price);
			i++;
			tmp = tmp->next;
		}
		while (tmp != base);
	}
	else // backward
	{
		printf("\r\n");
	
		do {
			printf("Node %3d:  addr = %#X   last = %#X  next = %#X  data.id = %3d  data.name = %20s  data.price = %.2f\r\n", i, tmp, tmp->last, tmp->next, tmp->data.id, tmp->data.name, tmp->data.price);
			i++;
			tmp = tmp->last;
		}
		while (tmp != base);
	}
}

void find_elements(Node *head)
{
	Node *tmp = head;
	int i = 0;
	
	printf("\r\n");
	
	do {
		printf("Node %3d:  addr = %#X   last = %#X  next = %#X  data.id = %3d  data.name = %20s  data.price = %.2f\r\n", i, tmp, tmp->last, tmp->next, tmp->data.id, tmp->data.name, tmp->data.price);
		i++;
		tmp = tmp->next;
	}
	while (tmp != head);
}

void reverse_find_elements(Node *head)
{
	Node *tmp = head;
	int i = 0;
	
	printf("\r\n");
	
	do {
		printf("Node %3d:  addr = %#X   last = %#X  next = %#X  data.id = %3d  data.name = %20s  data.price = %.2f\r\n", i, tmp, tmp->last, tmp->next, tmp->data.id, tmp->data.name, tmp->data.price);
		i++;
		tmp = tmp->last;
	}
	while (tmp != head);
}

void data_store(FILE *pf, Node *head)
{
	Node *tmp = head;
	pf = fopen("../data.txt", "a");
	
	printf("\r\n");
	
	if (pf == NULL)
	{
		printf("ERROR: Can not find such file in disk\r\n");
	}
	else
	{
		printf("[OK!] Find such file in directory, starting write data to data.txt\r\n");
		int i = 0;
		
		fprintf(pf, "\r\n");
			
		do {
			fprintf(pf, "Node %3d:  addr = %#X   last = %#X  next = %#X  data.id = %3d  data.name = %20s  data.price = %.2f\r\n", i, tmp, tmp->last, tmp->next, tmp->data.id, tmp->data.name, tmp->data.price);
			i++;
			tmp = tmp->next;
		}
		while (tmp != head);
		
		fprintf(pf, "\r\n");
		
		fclose(pf);
		printf("[OK!] Finished\r\n");
	}
}


int main()
{
//	printf("hello world!!\r\n");
	
	Head = malloc(sizeof(Node));
	Init_LinkList(Head);
	
	printf("[OK!] Initializating complete, please input stock infomation:title, ID, price.\r\n");
	printf("[Warning!] The stock ID should be belong 000~999 ,the name should be less than 20 characters\r\n");
	input_data(Head);
	
	printf("print linkedlist\r\n");
	travers_linkedlist(Head, POSITIVE);
	printf("print linkedlist reversed\r\n");
	travers_linkedlist(Head, POSITIVE);
	data_store(data_file, Head);

	return 0;
}
