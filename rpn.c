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
    char *ptr = result, *ptr1 = result, tmp_char; 
    int tmp_value; 
    char *numbers = "9876543210123456789";
    while(value){
        tmp_value = value;  value /= 10;
        *ptr++ = numbers[9 + (tmp_value - value * base)];
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
int pushNumber(Stack stack, string *str, int *count){
	push(stack, *str); *str = (char*)calloc(1, sizeof(char)); 
	*count = 0;  return (stack.list == NULL || str == NULL) ? 0 : 1;
}
int isOperator(char ch){
	return ch == '+' || ch == '-' || ch == '/' || ch == '*' || ch == '^';	
}
int popElementsAndPushesult(Stack stack, string *operand1, string *operand2, string *returnValue, char ch){
	*operand2 = pop(stack); *operand1 = pop(stack);
	*returnValue = (string)malloc(sizeof(char)*10);
	*returnValue = toString(operate(ch, *operand1, *operand2), *returnValue, 10);
	push(stack, *returnValue);
	return (stack.list == NULL || ch == 0) ? 0 : 1;
}
int storeChar(string *number, int *j, char ch){
	int i = *j;
	*number = (string)realloc(*number, sizeof(char)*(i+1));
	(*number)[i] = ch; i++; *j = i;
	return (ch=='\0') ? 0 : 1; 
}
int areOperatorsEnough(string expr){
	int i, oprand_count=0, operator_count=0; 
	for(i=0; i<strlen(expr); i++){
		isNumber(expr[i]) && !isNumber(expr[i+1]) && oprand_count++;
		isOperator(expr[i]) && operator_count++;
	}
	return (oprand_count == operator_count+1);

}


Result evaluate(char *expr){
	Result result = {0,0}; Stack stack = createStack();  
	int i, j=0, finalResult;
	string returnValue, operand1, operand2, numbers = malloc(sizeof(char));

	if(!areOperatorsEnough(expr)) return (Result){1,0};

	for(i=0; i<strlen(expr); i++){
		(isNumber(expr[i])) && storeChar(&numbers, &j, expr[i]);

		(isSeperator(expr[i]) && numbers[0] >='0' && numbers[0] <='9') && pushNumber(stack, &numbers, &j);

		(isOperator(expr[i])) && popElementsAndPushesult(stack, &operand1, &operand2, &returnValue, expr[i]);
	}
	result.status = atoi((string)(*stack.top)->data);
	free(numbers); free(stack.list); free(returnValue);
	return result;
}



// 3 + 4 * 2 / ( 1 - 5 ) ^ 2 ^ 3
char * infixToPostfix(char * expr){
	string result = malloc(sizeof(char));
	int i, j=0; Stack stack = createStack();
	for(i=0; i<strlen(expr); i++){
		if(isNumber(expr[i])){
			result = (string)realloc(result, sizeof(char)*((j+1)));
			result[j] = expr[i]; j++; 
			result[j+1] = ' ';	j++;
		}
		if(isOperator(expr[i])){
			push(stack, &expr[i]);
		}
	}
	for(i=0; i<j; i++)
		printf("<%c>\n",result[i]);
	print_stack(stack);
	return NULL;
}