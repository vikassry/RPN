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
int isSeperator_after_number(string, string, int);
int pushNumber(Stack, string*, int*);
int popElementsAndPushResult(Stack stack, string *returnValue, char ch);
int storeChar(string *number, int *j, char ch);
int areOperatorsEnough(string expr);
int operate(char, string, string);

Result evaluate(char * expression);
char * infixToPostfix(char * expression);