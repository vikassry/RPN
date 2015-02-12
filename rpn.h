#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#include "que.h"
typedef struct result Result;

struct result {
  int error;
  int status;
};

int isNumber(char);
int isOperator(char);
int isSeperator_after_number(String, String, int);
int pushNumber(Stack, String*, int*);
int popElementsAndPushResult(Stack stack, String *returnValue, char ch);
int storeChar(String *number, int *j, char ch);	
int areOperatorsEnough(String expr);
int operate(char, String, String);
int precedenceOf(char);
int pushToQueue(Queue, String*, int*, String, int);
char topOfStack(Stack);
void sendToQ(Queue, String*, char);
int sendToStack(Stack, String*, char);
void popOutToQ(Queue, Stack, String*);
int popUntilOpeningParenthesisFound(Stack, Queue, String *);
void copyToPostfixString(Queue, Stack, String);

Result evaluate(char * expression);
char * infixToPostfix(char * expression);