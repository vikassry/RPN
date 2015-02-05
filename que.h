#include "stack.h"

typedef struct que{
	LinkedList *list;
	Node **front;
} Queue;

Queue createQueue(void);
int enque(Queue, void *);
void *deque(Queue);
void print_Queue(Queue);