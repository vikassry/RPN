#include "rpn.h"
#include <stdio.h>
#include <string.h>
#include <stdlib.h>


int operate(char operator, string operand1, string operand2){
	int val1 = atoi(operand1), val2 = atoi(operand2), result ;
	switch(operator){
		case '+': result = val1 + val2; break;
		case '-': result = val1 - val2; break;
		case '*': result = val1 * val2; break;
		case '/': result = val1 / val2; break;
		default : printf(" Wrong operator");
	}
	return result ;
}

char *toString (int value, char *result, int base){
    char *ptr = result, *ptr1 = result, tmp_char; int tmp_value;
    while(value){
        tmp_value = value;  value /= 10;
        *ptr++ = "9876543210123456789"[9 + (tmp_value - value * base)];
    };
    tmp_value < 0 && (*ptr++ = '-');
    *ptr-- = '\0';
    while(ptr1 < ptr){
        tmp_char = *ptr; *ptr--= *ptr1;
        *ptr1++ = tmp_char;
    } 
    return result;
}


int isNumber(char ch){
	return 48<=ch && ch <=57 ;
}
int isSeperator(char ch){
	return ch == ' ' ;
}
int pushToStack(Stack *stack, string *str, int *count){
	push(stack, *str); *str = (char*)calloc(1, sizeof(char)); 
	*count = 0;  return (stack == NULL || str == NULL) ? 0 : 1;
}
int isOperator(char ch){
	return ch == '+' || ch == '-' || ch == '/' || ch == '*';	
}
int pop_and_push_result(Stack *stack, string *operand1, string *operand2, string *returnValue, char ch){
	*operand2 = pop(stack); *operand1 = pop(stack);
	*returnValue = (string)malloc(sizeof(char)*10);
	*returnValue = toString(operate(ch, *operand1, *operand2), *returnValue, 10);
	push(stack, *returnValue);
	return (stack == NULL || ch == 0) ? 0 : 1;
}


Result evaluate(char *expr){
	Result result = {0,0}; int i, j=0, oprand_count=0, operator_count=0, finalResult;
	Stack stack = createStack();  string returnValue;  
	string number = malloc(sizeof(char)), operand1, operand2;
	
	for(i=0; i<strlen(expr); i++){
		isNumber(expr[i]) && !isNumber(expr[i+1]) && oprand_count++;
		isOperator(expr[i]) && operator_count++;
	}
	if(oprand_count != operator_count+1) return (Result){1,0};

	for(i=0; i<strlen(expr); i++){
		if(isNumber(expr[i])){
			number = realloc(number, sizeof(char)*(j+1));
			number[j] = expr[i]; j++; 
		} 
		(isSeperator(expr[i]) && (number[0] >='0' && number[0] <='9')) && pushToStack(&stack, &number, &j);

		(isOperator(expr[i])) && pop_and_push_result(&stack, &operand1, &operand2, &returnValue, expr[i]);
	}
	result.status = atoi((string)stack.top->data);
	free(number); free(stack.list); free(returnValue);
	return result;
}