#include <string.h>
#include <stdlib.h>
#include "que.h"
#include "expr_assert.h"

void test_createQueue_creates_an_empty_queue(){
	Queue q = createQueue();
	assert((*q.front) == NULL);
	assert(q.list->head == NULL);
	assert(q.list->head == NULL);
	assert(q.list->count == 0);
	free(q.list);
}

void test_enque_adds_an_int_element_to_Queue_and_returns_number_of_elements_in_the_queue(){
	float a = 12.5;
	Queue q = createQueue();
	enque(q, &a);
	assert((*q.front)->data == &a);
	assert(*(float*)(*q.front)->data == 12.5);
	assert(q.list->head->data == &a);
	assert(q.list->tail->data == &a);
	assert(q.list->count == 1);
	free(q.list);
}

void test_enque_adds_3_char_element_to_Queue_and_returns_number_of_elements_in_the_queue(){
	char a = 'a', b = 'b', c='c';
	Queue q = createQueue();
	enque(q, &a);
	assert((*q.front)->data == &a); 
	assert(q.list->tail->data == &a);
	enque(q, &b);  enque(q, &c);
	
	assert((*q.front)->data == &a);
	assertEqual(*(char*)(*q.front)->data, 97);
	assert(q.list->head->data == &a);
	assert(q.list->tail->data == &c);
	assert(q.list->count == 3);
	free(q.list);
}

void test_enque_adds_3_string_element_to_Queue_and_returns_number_of_elements_in_the_queue(){
	String a = malloc(sizeof(char)*10), b = malloc(sizeof(char)*10), c=malloc(sizeof(char)*10); 
	Queue q = createQueue();
	strcpy(a,"asdzdczdcd"); strcpy(b,"wdcdcswwq"); strcpy(c,"jsdiksjdeq");
	enque(q, a); enque(q, b); enque(q, c);
	
	assert((*q.front)->data == a);
	assertEqual(strcmp((*q.front)->data, a), 0);
	
	assert(q.list->head->data == a);
	assert(q.list->tail->data == c);
	assertEqual(strcmp(q.list->tail->data, c), 0);
	assert(q.list->head->next->data == b);
	assert(q.list->count == 3);
	free(q.list);
}

void test_deque_delets_the_element_from_the_front_of_the_queue_and_returns_deleted_items_reference(){
	char a = 'a', b = 'b', c='c';
	Queue q = createQueue();
	enque(q, &a); enque(q, &b); enque(q, &c);
	assert(q.list->tail->data == &c);
	assert(*(char*)deque(q) == a);
	assert((*q.front)->data == &b);	
	deque(q);

	assert((*q.front)->data == &c);
	assert(q.list->tail->data == &c);	
	assert(*(char*)deque(q) == 'c');
	assert(q.list->head == NULL);
	assert(q.list->tail == NULL);
	assert((*q.front) == NULL);
	free(q.list);
}

void test_deque_delets_the_last_element_from_queue_and_makes_list_head_tail_and_front_NULL(){
	double a = 23.5;
	Queue q = createQueue();
	enque(q, &a);
	assert((*q.front)->data == &a);	
	assert(q.list->head->data == &a);
	assert(q.list->tail->data == &a);
	assert(*(double*)((*q.front)->data) == 23.5);
	assert(*(double*)deque(q) == a);

	assert(q.list->head == NULL);
	assert(q.list->tail == NULL);
	assert((*q.front) == NULL);
	free(q.list);
}