#include <stdio.h>
#include <stdlib.h>
#include <malloc.h>
#include <string.h>

#define DEBUG(x) printf("%d\r\n", x)

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
		scanf("%d%f%s",&tmp->data.id, &tmp->data.price, &tmp->data.name);
		printf("%d %.2f %s\r\n",tmp->data.id, tmp->data.price, tmp->data.name);
		
		if (strcmp(tmp->data.name, null) != 0)
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

void print_LinkList(Node *head)
{
	Node *tmp = head;
	int i = 0;
	do {
		printf("Node %3d:  addr = %#X   last = %#X  next = %#X  data.id = %3d  data.name = %20s  data.price = %.2f\r\n", i, tmp, tmp->last, tmp->next, tmp->data.id, tmp->data.name, tmp->data.price);
		i++;
		tmp = tmp->next;
	}
	while (tmp != head);
}

void data_store(FILE *pf, Node *head)
{
	Node *tmp = head;
	pf = fopen("data.txt", "a");
	
	if (pf == NULL)
	{
		printf("can not find such file in disk\r\n");
	}
	else
	{
		int i = 0;
		do {
			fprintf(pf, "Node %3d:  addr = %#X   last = %#X  next = %#X  data.id = %3d  data.name = %20s  data.price = %.2f\r\n", i, tmp, tmp->last, tmp->next, tmp->data.id, tmp->data.name, tmp->data.price);
			i++;
			tmp = tmp->next;
		}
		while (tmp != head);
		
		fclose(pf);
	}
}


int main()
{
//	printf("hello world!!\r\n");
	
	Head = malloc(sizeof(Node));
	Init_LinkList(Head);
	
	printf("init complete, please input shares infomation: ID, price, name.\r\n");
	printf("The stock ID should be belong 000~999 ,the name should be less than 20 characters\r\n");
	input_data(Head);
	
	print_LinkList(Head);
	data_store(data_file, Head);
	return 0;
}
