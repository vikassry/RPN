#include "stack.h"
typedef struct result Result;

struct result {
  int error;
  int status;
};

Result evaluate(char * expression);
char * infixToPostfix(char * expression);