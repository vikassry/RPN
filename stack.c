#include <stdio.h>
#include <stdlib.h>
#include "stack.h"


void print_stack(Stack s){
	print_list(*s.list);
}

Stack createStack(void){
	LinkedList *list = (LinkedList*)calloc(1,sizeof(LinkedList));
	return (Stack){list, &list->tail};
}

int push(Stack stack, void *data){
	node_ptr node = create_node(data);
	add_to_list(stack.list, node);
	return stack.list->count;
}

void *pop(Stack stack){
	return deleteElementAt(stack.list, stack.list->count-1);
}

void print_list(LinkedList list){
	int i=0; node_ptr walker;  
	for(walker = list.head; walker !=NULL; walker = walker->next)
		printf("Node%d %c \n", i+1, *(char*)walker->data ) && i++;
	printf("Total Elements: %d\n",list.count);
}


LinkedList createList(){
	return (LinkedList){NULL, NULL, 0};
}

Node *create_node(void *data){
	node_ptr node = calloc(1, sizeof(Node));
	(*node).data = data;
	(*node).next = NULL;
	return node;
}

int add_to_list(LinkedList *list, Node *item){
	if(item == NULL) return 0;
	if((*list).head == NULL)
		(*list).head = item;
	else
		(*(*list).tail).next = item;
	(*list).tail = item;
	list->count+=1;
	return 1;
}

void *get_first_element(LinkedList list){
	return (list.head == NULL) ? NULL : (*list.head).data;
}

void *get_last_element(LinkedList list){
	return (list.head == NULL) ? NULL : (*list.tail).data;
}

void traverse(LinkedList list, void (*fun)(void *data)){
	node_ptr walker;
	for (walker = list.head; walker !=NULL; walker = (*walker).next)
		fun((*walker).data);
}


Node *getNodeAt(LinkedList list, int index){
	int idx = 0;  node_ptr walker, item;
	for(walker = list.head; walker !=NULL; walker = (*walker).next, idx++)
		(idx == index) && (item = walker);
	return item;
}

void *getElementAt(LinkedList list, int index){
	if (index >= list.count || index < 0) 
		return NULL;
	return getNodeAt(list, index)->data;
}

int indexOf(LinkedList list, void *item){
	int idx = 0;  node_ptr walker;
	for(walker = list.head; walker !=NULL; walker = (*walker).next, idx++)
		if((*walker).data == item) 	return idx;
	return -1;	
}

void *deleteElementAt(LinkedList *list, int index){
	int idx = 0;  node_ptr walker; Node *item = getNodeAt(*list, index);
	if(list->count == 0 || index < 0 || index >= list->count || list->head == NULL) return NULL;
	index == 0 && list->count == 1 && (list->tail = NULL);
	if(index == 0){
		list->head = list->head->next;
		(*list).count -= 1; return item->data;
	}
	if(index == (*list).count-1){
		item = list->tail;
		for(walker = list->head; walker !=NULL; walker = walker->next){
			if(idx == (*list).count-2){
				(*walker).next = NULL;
				(*list).tail = walker;
				(*list).count -= 1;
				return item->data;
			} idx++;
		}
	}
	getNodeAt(*list, index-1)->next = getNodeAt(*list,index+1);
	list->count -= 1;
 	return item->data;
}


int asArray(LinkedList list , void **array){
	int index = 0;  node_ptr walker;
	for(walker = list.head; walker !=NULL; walker = (*walker).next)
		(array[index] = (*walker).data) && (index += 1);
	return index;
}


LinkedList *filter(LinkedList list, int_void predicate){
	int index = 0;  node_ptr walker;
	list_ptr new_list = calloc(1,sizeof(LinkedList));
	if(list.head == NULL) return NULL;

	for(walker = list.head; walker !=NULL; walker = walker->next)
		(predicate(walker->data)) && add_to_list(new_list, walker);
	return new_list;
}