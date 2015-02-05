#include <stdio.h>
typedef void TestFn(void);
typedef struct{
	char* name; 
	TestFn* fn;
} Test;

//code to be updated starts
TestFn setup,teardown,fixtureSetup,fixtureTearDown,test_createQueue_creates_an_empty_queue,test_enque_adds_an_int_element_to_Queue_and_returns_number_of_elements_in_the_queue,test_enque_adds_3_char_element_to_Queue_and_returns_number_of_elements_in_the_queue,test_enque_adds_3_string_element_to_Queue_and_returns_number_of_elements_in_the_queue,test_deque_delets_the_last_element_from_the_queue,test_deque_delets_the_last_element_from_the_double_queue;
Test test[] = {"test_createQueue_creates_an_empty_queue",test_createQueue_creates_an_empty_queue,"test_enque_adds_an_int_element_to_Queue_and_returns_number_of_elements_in_the_queue",test_enque_adds_an_int_element_to_Queue_and_returns_number_of_elements_in_the_queue,"test_enque_adds_3_char_element_to_Queue_and_returns_number_of_elements_in_the_queue",test_enque_adds_3_char_element_to_Queue_and_returns_number_of_elements_in_the_queue,"test_enque_adds_3_string_element_to_Queue_and_returns_number_of_elements_in_the_queue",test_enque_adds_3_string_element_to_Queue_and_returns_number_of_elements_in_the_queue,"test_deque_delets_the_last_element_from_the_queue",test_deque_delets_the_last_element_from_the_queue,"test_deque_delets_the_last_element_from_the_double_queue",test_deque_delets_the_last_element_from_the_double_queue};
char testFileName[] = {"queTest.c"};
void _setup(){/*CALL_SETUP*/}
void _teardown(){/*CALL_TEARDOWN*/}
void fixtureSetup(){}
void fixtureTearDown(){}
//code to be updated ends

int testCount;
int passCount;
int currentTestFailed;

int assert_expr(int expr, const char* fileName, int lineNumber, const char* expression){
	if(expr) return 0;
	currentTestFailed = 1;
	printf("\t %s : failed at %s:%d\n",expression, fileName,lineNumber);
	return 1;
}
int assert_equal(int val1, int val2, const char* fileName, int lineNumber,const char* expr1,const char* expr2){
	if(val1 == val2) return 0;
	currentTestFailed = 1;
	printf("\t %d == %d: failed in assertEqual(%s,%s) at %s:%d\n",val1,val2,expr1,expr2, fileName,lineNumber);
	return 1;
}

void runTest(char* name, TestFn test){
	testCount++,currentTestFailed=0;
	printf("**  %s\n",name);
	_setup();
		test();
	_teardown();
	if(!currentTestFailed) passCount++;	
}
int main(int argc, char const *argv[]){		
	int i,total = sizeof(test)/sizeof(Test);	
	fixtureSetup();
	testCount=0,passCount=0;
	printf("**------ %s ------\n",testFileName);
	for (i = 0; i < total; ++i)
		runTest(test[i].name,test[i].fn);	
	printf("** Ran %d tests passed %d failed %d\n",testCount,passCount,testCount-passCount);
	fixtureTearDown();	
	return 0;
}