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

Result evaluate(char * expression);
char * infixToPostfix(char * expression);