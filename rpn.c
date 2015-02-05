#include "rpn.h"


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
int isSeperator(char ch, string numbers){
	return ch == ' '  && numbers[0]>='0' && numbers[0] <= '9';
}
int pushNumber(Stack stack, string *str, int *count){
	char str1[1], str2[1];
	strcpy(str1, ""); strcpy(str2," ");
	if(*str==NULL || strcmp(*str, str1)==0 || strcmp(*str, str2)==0 || count==NULL) return 0;
	push(stack, *str); *count = 0;
	*str = (char*)calloc(1, sizeof(char));
	return 1;
}

int isOperator(char ch){
	char *operators = "+-/*^!=&";
	int i = 0;
	for(i=0; i<strlen(operators); i++)
		if(ch == operators[i])
			return 1;
		return 0;
}
int storeChar(string *number, int *j, char ch){
	int i = *j;
	if(*number == NULL || ch == '\0' || !isNumber(ch)) return 0;
	*number = (string)realloc(*number, sizeof(char)*(i+1));
	(*number)[i] = ch; i++; *j = i;
	return 1; 
}

int popElementsAndPushResult(Stack stack, string *returnValue, char ch){
	string operand2 = pop(stack), operand1 = pop(stack);
	*returnValue = (string)malloc(sizeof(char)*10);
	*returnValue = toString(operate(ch, operand1, operand2), *returnValue, 10);
	push(stack, *returnValue);
	return (stack.list == NULL || !isOperator(ch)) ? 0 : 1;
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
	string returnValue, numbers = malloc(sizeof(char));

	if(!areOperatorsEnough(expr)) return (Result){1,0};

	for(i=0; i<strlen(expr); i++){
		isNumber(expr[i]) && storeChar(&numbers, &j, expr[i]);

		isSeperator(expr[i], numbers) && pushNumber(stack, &numbers, &j);

		isOperator(expr[i]) && popElementsAndPushResult(stack, &returnValue, expr[i]);
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
	// for(i=0; i<j; i++)
	// 	// printf("<%c>\n",result[i]);
	// print_stack(stack);
	return NULL;
}