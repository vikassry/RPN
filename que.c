#include <stdio.h>
#include <stdlib.h>
#include "que.h"

void print_Queue(Queue q){
	print_list(*q.list);
}

Queue createQueue(void){
	LinkedList *list = (LinkedList*)calloc(1, sizeof(LinkedList));
	return (Queue){list, &list->head};
}

int enque(Queue q, void * item){
	node_ptr node = create_node(item);
	add_to_list(q.list, node);
	return q.list->count;
}

void *deque(Queue q){
	return deleteElementAt(q.list, 0);
}