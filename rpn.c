#include "rpn.h"
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
// #define atoa(x) #x


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
    if (base < 2 || base > 36) { *result = '\0'; return result; }
    while (value){
        tmp_value = value; value /= base;
        *ptr++ = "9876543210123456789" [9 + (tmp_value - value * base)];
    };
    tmp_value < 0 && (*ptr++ = '-');
    *ptr-- = '\0';
    while (ptr1 < ptr) {
        tmp_char = *ptr;
        *ptr--= *ptr1;
        *ptr1++ = tmp_char;
    }
    return result;
}


int evaluate(char *expr){
	Stack stack = createStack(); char seperator = ' ', operator, *returnValue, *result;
	string number = calloc(1, sizeof(char)), operand1, operand2;
	int i, j=0, k, value;
	
	for(i=0,j=0; i<strlen(expr); i++){
		if(expr[i] <=57 && expr[i] >=48 ){
			number = realloc(number, sizeof(char)*(j+1));
			number[j] = expr[i]; j++;
		} 
		if(expr[i] == seperator && (number[0] >=48 && number[0] <=57)){
				push(&stack, number);  j=0;
				number = (char*)calloc(1, sizeof(char)); 
		}
		if(expr[i] == 42 || expr[i] == 43 || expr[i] == 45 || expr[i] == 47){
			operand2 = pop(&stack); operand1 = pop(&stack);
			returnValue = (string)malloc(sizeof(char)*10);
			returnValue = toString(operate(expr[i], operand1, operand2), returnValue, 10);
			push(&stack, returnValue);
		}
	}
	free(number); free(stack.list);
	return atoi((string)stack.top->data);
}
