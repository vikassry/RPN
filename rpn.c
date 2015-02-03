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


int evaluate(char *expr){
	Stack stack = createStack(); char seperator = ' ', operator;
	string number = calloc(1, sizeof(char)), operand1, operand2;
	int i, j=0, value, result, *returnValue;
	
	for(i=0,j=0; i<strlen(expr); i++){
		if(expr[i] <=57 && expr[i] >=48 ){
			number = realloc(number, sizeof(char)*(j+1));
			number[j] = expr[i]; j++;
		} 
		if(expr[i] == seperator && (number[0] >=48 && number[0] <=57)){
				push(&stack, number);
				number = (char*)calloc(1, sizeof(char));  j=0;
		}
		if(expr[i] == 42 || expr[i] == 43 || expr[i] == 45 || expr[i] == 47){
			operand2 = pop(&stack); 
			operand1 = pop(&stack);
			returnValue = (int*)malloc(sizeof(int));
			*returnValue =  operate(expr[i], operand1, operand2);
			push(&stack, returnValue);
		}
	}
	return *(int*)stack.top->data;
}
