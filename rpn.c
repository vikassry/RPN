#include "rpn.h"
#include "math.h"

int operate(char operator, String operand1, String operand2){
	int val1 = atoi(operand1), val2 = atoi(operand2), result ;
	switch(operator){
		case '+': result = val1 + val2; break;
		case '-': result = val1 - val2; break;
		case '*': result = val1 * val2; break;
		case '/': result = val1 / val2; break;
		case '^': result = pow(val1,val2); break;
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
	return '0'<=ch && ch <='9' ;
}
int isSeperator_after_number(String numbers, String expr, int i){
	return (expr[i] == ' ' && numbers[0]>='0' && numbers[0] <= '9') || (i==strlen(expr)-1 && expr[i]>='0' && expr[i] <= '9');
}
int pushNumber(Stack stack, String *str, int *count){
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
int storeChar(String *number, int *j, char ch){
	int i = *j;
	if(*number == NULL || ch == '\0' || !isNumber(ch)) return 0;
	*number = (String)realloc(*number, sizeof(char)*(i+2));
	(*number)[i] = ch; i++; *j = i;
	(*number)[i] = '\0';
	return 1; 
}

int popElementsAndPushResult(Stack stack, String *returnValue, char ch){
	String operand2 = pop(stack), operand1 = pop(stack);
	*returnValue = (String)malloc(sizeof(char)*10);
	*returnValue = toString(operate(ch, operand1, operand2), *returnValue, 10);
	push(stack, *returnValue);
	return (stack.list == NULL || !isOperator(ch)) ? 0 : 1;
}

int areOperatorsEnough(String expr){
	int i, oprand_count=0, operator_count=0; 
	for(i=0; i<strlen(expr); i++){
		isNumber(expr[i]) && !isNumber(expr[i+1]) && oprand_count++;
		isOperator(expr[i]) && operator_count++;
	}
	return (oprand_count == operator_count+1);
}


Result evaluate(char *expr){
	int i, j=0, finalResult;
	Result result = {0,0}; 
	Stack stack = createStack();  
	String returnValue, numbers = malloc(sizeof(char));

	if(!areOperatorsEnough(expr)) return (Result){1,0};

	for(i=0; i<strlen(expr); i++){
		isNumber(expr[i]) && storeChar(&numbers, &j, expr[i]);

		isSeperator_after_number(numbers, expr, i) && pushNumber(stack, &numbers, &j);

		isOperator(expr[i]) && popElementsAndPushResult(stack, &returnValue, expr[i]);
	}
	result.status = atoi((String)(*stack.top)->data);
	free(numbers); free(stack.list); free(returnValue);
	return result;
}

//-----------------------------------------------------------------------------------------------------

int pushToQueue(Queue q, String *str, int *count, String expr, int i){
	if(*str==NULL || strcmp(*str, "")==0 || count==NULL) return 0;
	if(i==strlen(expr)-1){
		enque(q, *str); return 1;
	} 
	enque(q, *str); *count = 0;
	*str = (char*)malloc(sizeof(char));
	strcpy(*str, " "); enque(q, *str);
	*str = (char*)calloc(1, sizeof(char));
	return 1;
}

int precedenceOf(char operator){
	int precedence;	
	operator == '^' && (precedence = 3);
	(operator == '/' || operator == '*') && (precedence = 2);
	(operator == '+' || operator == '-') && (precedence = 1);
	return precedence;
}
char topOfStack(Stack s){
	return (*s.top) ? *(char*)(*s.top)->data : '\0';
}

void sendToQ(Queue q, String *str, char token){
	*str = (char*)calloc(1, sizeof(char));
	(*str)[0] = token;
	enque(q, *str);
	*str = (char*)calloc(1, sizeof(char));
}

int sendToStack(Stack s, String *str, char token){
	if(!*str || token == '\0') return 0;
	*str = (char*)calloc(1, sizeof(char));
	(*str)[0] = token;
	push(s, *str);
	*str = (char*)calloc(1, sizeof(char));
	return 1;
}
void takeCareOfPrecedence(Stack s, Queue q, String *str, char operator){
	while(*s.top !=NULL && precedenceOf(operator) <= precedenceOf(topOfStack(s)) && topOfStack(s)!='('){
		sendToQ(q, str, *(char*)pop(s));
		sendToQ(q, str, ' ');
	} 
	sendToStack(s, str, operator);
}

int pushToStack(Stack s, Queue q, String *str, char operator){
	if(*str==NULL) return 0;
	(*str)[0] = operator;
	takeCareOfPrecedence(s, q, str, operator);
	return 1;
}

int popUntilOpeningParenthesisFound(Stack s, Queue q, String *str){
	if(!*s.top || !*str) return 0;
	while(*s.top && topOfStack(s) != '('){
		sendToQ(q, str,*(char*)pop(s));
		sendToQ(q, str, ' ');
	} pop(s);
	return 1;
}

void handleParenthesis(Stack s, Queue q, String *numbers, char token){
	token == '(' && sendToStack(s, numbers, token);
	token == ')' && popUntilOpeningParenthesisFound(s, q, numbers);
}

void copyToPostfixString(Queue q, Stack s, String result){
	node_ptr walker;
	for(walker=q.list->head; walker; walker=walker->next)
		strcat(result,(String)walker->data);
	for(;*s.top;)
		strcat(result," ") && strcat(result,pop(s));
}


char * infixToPostfix(char * expr){
	int i, j=0;
	Stack stack = createStack(); Queue q = createQueue(); 
	String numbers = malloc(sizeof(char)); 
	String result = (String)calloc(sizeof(char),(strlen(expr))+1);
	
	for(i=0; i<strlen(expr); i++){
		isNumber(expr[i]) && storeChar(&numbers, &j, expr[i]);

		isSeperator_after_number(numbers, expr, i) && pushToQueue(q, &numbers, &j, expr, i);

		isOperator(expr[i]) && pushToStack(stack, q, &numbers, expr[i]);

		handleParenthesis(stack, q, &numbers, expr[i]);
	}
	copyToPostfixString(q,stack,result);
	free(numbers); free(stack.list); free(q.list);
	return result;
}