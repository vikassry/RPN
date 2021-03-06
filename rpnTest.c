#include "expr_assert.h"
#include "rpn.h"

void test_isNumber_returns_1_if_given_character_is_a_number(){
	assert(isNumber('5') == 1);
	assert(isNumber('0') == 1);
}

void test_isNumber_returns_0_if_given_character_is_a_not_a_number(){
	assert(isNumber('#') == 0);
	assert(isNumber('d') == 0);
}

void test_isOperator_gives_1_if_given_char_is_an_operator(){
	assert(isOperator('+') ==1);
	assert(isOperator('^') ==1);
}

void test_isOperator_returns_0_if_given_character_is_not_an_Operator(){
	assert(isOperator('#') == 0);
	assert(isOperator('S') == 0);
	assert(isOperator('9') == 0);
}

void test_isSeperator_after_number_gives_1_when_whiteSpace_occurs_after_any_number(){
	String expr = "23 ";
	assert(isSeperator_after_number("43",expr,2) == 1);
}

void test_isSeperator_after_number_gives_0_when_whiteSpace_doesnt_occur(){
	String expr = "4r[";
	assert(isSeperator_after_number("r5",expr,2) == 0);
}

void test_isSeperator_after_number_gives_0_when_other_than_whiteSpace_occurs(){
	String expr = "14 [";
	assert(isSeperator_after_number("@4",expr,3) == 0);
}

void test_isSeperator_returns_1_when_number_is_at_the_end_of_the_string(){
	String expr = "2 34";
	assert(isSeperator_after_number("34",expr,3) == 1);
}

void test_pushNumber_pushes_given_string_into_stack_and_returns_1(){
	Stack stack = createStack();
	int num = 10; String str = "vikas";
	assert(pushNumber(stack, &str, &num) == 1);
	assert(memcmp((*stack.top)->data, str, strlen(str)) == 0);
	assert(num==0);
	free(str);
}

void test_pushNumber_gives_0_when_string_is_NULL_or_number_adrss_is_NULL(){
	Stack stack = createStack();
	int num = 10; String str = NULL, str1 = "hii";
	assert(pushNumber(stack, &str, &num) == 0);
	assert(pushNumber(stack, &str1, NULL) == 0);
}

void test_pushNumber_gives_0_when_string_is_empty_or_space(){
	Stack stack = createStack();
	int num = 10; String str = " ", str1 = "";
	assert(pushNumber(stack, &str, &num) == 0);
	assert(pushNumber(stack, &str1, &num) == 0);
}

void test_areOperatorsEnough_return_1_when_operators_are_enough_for_operands(){
	assert(areOperatorsEnough("2 2 - 2 2 2 * 2 - - -") == 1);
	assert(areOperatorsEnough("2 2 - 2 2 + 2 * 2 - - ") == 1);
}

void test_areOperatorsEnough_return_0_when_operators_are_not_enough_for_operands(){
	assert(areOperatorsEnough("2 2 - 2 2 2 2-") == 0);
	assert(areOperatorsEnough("2 2 - 2 2 + 2 * 2 ") == 0);
}

void test_operate_gives_result_of_two_numbers_according_to_the_operator(){
	assertEqual(operate('+', "21", "3"),24);
	assertEqual(operate('-', "21", "3"),18);
	assertEqual(operate('*', "21", "3"),63);
	assertEqual(operate('/', "21", "3"),7);
}

void test_storeChar_stores_given_number_char_in_given_string_at_given_index_and_increments_given_index_and_returns_1(){
	String numbers = malloc(sizeof(char)); int i=0;
	assert(storeChar(&numbers, &i, '5')==1);
	assert(numbers[0]=='5');
	assert(i==1); free(numbers);
}

void test_storeChar_doesnt_store_given_char_in_string_if_it_isnt_numChar_and_returns_0(){
	String numbers = malloc(sizeof(char)); int i=0;
	assert(storeChar(&numbers, &i, 'p')==0);
	assert(storeChar(&numbers, &i, '\0')==0);
	assert(i==0); free(numbers);
}

void test_storeChar_doesnt_store_given_char_in_string_when_given_string_is_NULL_and_returns_0(){
	String numbers = NULL; int i=0;
	assert(storeChar(&numbers, &i, '9')==0);
	assert(i==0);
}

void test_popElementsAndPushResult_returns_0_when_char_operator_is_invalid(){
	Stack stack = createStack();
	String num1 = "4", num2 = "23", result, expected = "27";
	push(stack, num1); push(stack, num2);
	assert(popElementsAndPushResult(stack, &result, 0)==0);
}

void test_evaluate_returns_the_result_of_postfix_addition_5_for_2_and_3(){
	Result result = evaluate("2 3 +");
	assertEqual(result.status, 5);
	assertEqual(result.error, 0);
}

void test_evaluate_returns_the_result_of_postfix_subtraction_minus_1_for_2_and_3(){
	Result result = evaluate("2 3 -");
	assertEqual(result.status, -1);
	assertEqual(result.error, 0);
}

void test_evaluate_returns_the_result_of_postfix_multiplication_6_for_2_and_3(){
	Result result = evaluate("2 3 *");
	assertEqual(result.status, 6);
}

void test_evaluate_returns_the_result_of_postfix_division_0_for_2_and_3(){
	Result result = evaluate("2 3 /");
	assertEqual(result.status, 0);
}

void test_evaluate_returns_the_result_of_postfix_two_digits_addition_15_for_12_and_3(){
	Result result = evaluate("12 3 +");
	assertEqual(result.status, 15);
}

void test_evaluate_returns_the_result_of_postfix_subtraction_two_digits_minus_1_for_21_and_23(){
	Result result = evaluate("21 23 -");
	assertEqual(result.status, -2);
}

void test_evaluate_returns_the_result_of_postfix_multiplication_of_two_digits_144_for_12_and_12(){
	Result result = evaluate("12 12 *");
	assertEqual(result.status, 144);
}

void test_evaluate_returns_the_result_of_postfix_division_of_two_digits_7_for_84_and_12(){
	Result result = evaluate("84 12 /");
	assertEqual(result.status, 7);
}

void test_evaluate_returns_the_result_of_postfix_three_digits_addition_465_for_123_and_342(){
	Result result = evaluate("123 342 +");
	assertEqual(result.status, 465);
}

void test_evaluate_returns_the_result_of_postfix_three_digits_division_80_for_960_and_12(){
	Result result = evaluate("960 12 /");
	assertEqual(result.status, 80);
}

void test_evaluate_returns_the_result_of_postfix_four_digits_addition_15_for_12_and_3(){
	Result result = evaluate("1234 4321 +");
	assertEqual(result.status, 5555);
}

void test_evaluate_returns_the_result_of_postfix_four_digits_subtraction_minus_3087_for_1234_and_4321(){
	Result result = evaluate("1234 4321 -");
	assertEqual(result.status, -3087);
}

void test_evaluate_returns_the_result_of_postfix_five_digits_addition_56561_for_12732_and_43827(){
	Result result = evaluate("12734 43827 +");
	assertEqual(result.status, 56561);
}

void test_evaluate_returns_the_result_of_postfix_five_digits_division_by_3_digit_number(){
	Result result = evaluate("27183 123 /");
	assertEqual(result.status, 221);
}

void test_evaluate_returns_the_result_of_postfix_expression_for_2_3_and_4(){
	Result result = evaluate("2 3 4 + -");
	assertEqual(result.status, -5);
}

void test_evaluate_returns_the_result_of_postfix_expression_for_22_3_and_4(){
	Result result = evaluate("22 3 4 * + ");
	assertEqual(result.status, 34);
}

void test_evaluate_returns_the_result_of_postfix_complex_multiplication_of_1_2_3_4_5(){
	Result result = evaluate("1 2 3 4 5 * * * * ");
	assertEqual(result.status, 120);
}

void test_evaluate_returns_the_result_of_postfix_complex_expression_of_2_2_2_2_3(){
	Result result = evaluate("2 2 2 * 2 - 3 + + ");
	assertEqual(result.status, 7);
}

void test_evaluate_returns_the_result_of_postfix_complex_expression_of_2_2_2_2_2_2_2(){
	Result result = evaluate("2 2 2 2 2 * * 2 + + 2 - *");
	assertEqual(result.status, 20);
}

void test_evaluate_returns_the_result_of_postfix_complex_expression_of_2_2_2_2_2_2(){
	Result result = evaluate("2 2 - 2 2 2 * 2 - - -");
	assertEqual(result.status, 0);
}

void test_evaluate_returns_the_result_of_postfix_complex_expression_of_5_1_2_4_3(){
	Result result = evaluate("5 1 2 + 4 * + 3 -");
	assertEqual(result.status, 14);
}

void test_evaluate_returns_the_result_with_errorValue_1_when_wrong_expression_isPassed(){
	Result result = evaluate("5 4 1 + 4 * + 3 5 -");
	assertEqual(result.error, 1);
	assertEqual(result.status, 0);
}

void test_evaluate_returns_the_result_with_error_having_1_for_less_number_of_operands(){
	Result result = evaluate("1 + - 4 * + 5 -");
	assertEqual(result.error, 1);
}

void test_evaluate_returns_the_result_with_error_having_1_for_less_number_of_operators(){
	Result result = evaluate("1 3 5 4 * + 5 -");
	assertEqual(result.error, 1);
}

void test_pushToQueue_enques_given_string_with_a_space_in_given_queue_and_returns_1_and_initializes_given_string_to_NULL_after_operation(){
	Queue q = createQueue();
	String name = "v"; int i = 1;
	assert(pushToQueue(q, &name, &i, "vicky", 2)==1);
	assert(i==0);
	assertEqual(strcmp(q.list->head->data,"v"),0);
	assert(strcmp(q.list->tail->data, " ")== 0);
	assertEqual(strcmp(name, " "), 0); 
	free(q.list);
}

void test_pushToQueue_doesnt_enque_string_in_given_queue_and_returns_0(){
	Queue q = createQueue();
	String name = "", name1 = NULL; int i = 1;
	assertEqual(pushToQueue(q, &name, &i, "vicky", 2),0);
	assertEqual(pushToQueue(q, &name1, &i, "vicky", 2),0);
	assertEqual(pushToQueue(q, &name, NULL, "vicky", 2),0);
}

void test_pushToQueue_enques_given_string_without_space_in_given_queue_and_returns_1_when_char_is_at_the_end_of_string(){
	Queue q = createQueue();
	String name = "y"; int i = 4;
	assert(pushToQueue(q, &name, &i, "vicky", 4)==1);
	assert(i==4);
	assertEqual(strcmp(q.list->head->data,"y"),0);
	free(q.list);
}

void test_precedenceOf_gives_preedence_of_given_operator(){
	assertEqual(precedenceOf('+'),1);
	assertEqual(precedenceOf('-'),1);
	assertEqual(precedenceOf('*'),2);
	assertEqual(precedenceOf('/'),2);
	assertEqual(precedenceOf('^'),3);
}

void test_gives_top_character_of_the_stack_otherwise_0(){
	Stack s = createStack();
	char ch1='v', ch2='s';
	push(s, &ch1); push(s, &ch2);
	assertEqual(topOfStack(s),'s');
	pop(s);
	assertEqual(topOfStack(s),'v');
	pop(s);
	assertEqual(topOfStack(s),0);
	free(s.list);
}

void test_sendToQ_enques_char_in_given_queue_sets_string_to_null_after_operation(){
	Queue q = createQueue();
	String str="hii";
	sendToQ(q, &str,'v');
	assertEqual(strcmp(q.list->head->data, "v"),0);
	assertEqual(strcmp(str,"hii"),-104);
	free(q.list);
}

void test_sendToStack_enques_char_in_given_queue_and_returns_1_and_changes_the_string(){
	Stack s = createStack();
	String str="hii";
	assert(sendToStack(s, &str, 'v'));
	assertEqual(strcmp((*s.top)->data, "v"),0);
	assertEqual(strcmp(str,"hii"),-104);
	free(s.list);
}

void test_sendToStack_doesnt_enque_char_in_given_queue_and_returns_0_when_given_string_is_NULL_or_given_char_is_0(){
	Stack s = createStack();
	String str="hii", str1=NULL;
	assert(sendToStack(s, &str, 0)==0);
	assertEqual(strcmp(str,"hii"),0);

	assert(sendToStack(s, &str, 0)==0);
	assertEqual(strcmp(str,"hii"),0);
	free(s.list);
}

void test_copyToPostfixString_copies_the_queue_and_stack_data_in_postfix_form_to_a_given_string(){
	String ch1="A", ch2=" ", ch3="B", ch4=" ", ch5="+", ch6="C", ch7="D", ch8="*";
	Queue q = createQueue(); Stack s = createStack();
	String result = calloc(7, sizeof(char));
	enque(q, ch1); enque(q, ch2); enque(q, ch3); enque(q, ch4); enque(q, ch5); 
	push(s, ch8); push(s, ch7); push(s, ch6);
	copyToPostfixString(q, s, result);
	assertEqual(strcmp(result, "A B + C D *"),0);
	free(q.list); free(s.list);
}

void test_infixToPostfix_returns_the_rpn_expression_from_given_infix_expression_for_single_digit(){
	String rpn_expression = infixToPostfix("3 + 4");
	assertEqual(strcmp(rpn_expression, "3 4 +"),0);
	free(rpn_expression);
}

void test_infixToPostfix_returns_the_rpn_expression_from_given_infix_expression_with_more_numbers(){
	String rpn_expression = infixToPostfix("2 - 4 + 1");
	assertEqual(strcmp(rpn_expression, "2 4 - 1 +"),0);
	free(rpn_expression);
}

void test_infixToPostfix_returns_the_rpn_expression_from_given_infix_expression_with_two_digit_number(){
	String rpn_expression = infixToPostfix("35 + 4");
	assertEqual(strcmp(rpn_expression, "35 4 +"),0);
	free(rpn_expression);
}

void test_infixToPostfix_returns_the_rpn_expression_from_given_infix_expression_with_two_digits_with_multiple_numbers(){
	String rpn_expression = infixToPostfix("50 + 4 - 19");
	assertEqual(strcmp(rpn_expression, "50 4 + 19 -"),0);
	free(rpn_expression);
}

void test_infixToPostfix_returns_the_rpn_expression_from_given_infix_expression_with_five_digits_with_multiple_numbers(){
	String rpn_expression = infixToPostfix("1234 + 432 - 12345");
	assertEqual(strcmp(rpn_expression, "1234 432 + 12345 -"),0);
	free(rpn_expression);
}

void test_infixToPostfix_returns_the_rpn_expression_from_given_infix_expression_with_five_digits_with_multiple_numbers_with_precedence(){
	String rpn_expression = infixToPostfix("1234 - 432 * 12345");
	assertEqual(strcmp(rpn_expression, "1234 432 12345 * -"),0);
	free(rpn_expression);
}

void test_infixToPostfix_returns_the_rpn_expression_from_given_infix_expression_with_two_digits_with_precedence(){
	String rpn_expression = infixToPostfix("50 / 4 - 19 * 12");
	assertEqual(strcmp(rpn_expression, "50 4 / 19 12 * -"),0);
	free(rpn_expression);
}

void test_infixToPostfix_returns_the_rpn_expression_from_given_infix_expression_with_mixed_digits_with_precedence(){
	String rpn_expression = infixToPostfix("125 ^ 14 * 9");
	assertEqual(strcmp(rpn_expression, "125 14 ^ 9 *"),0);
	free(rpn_expression);
}

void test_infixToPostfix_returns_rpn_expression_with_multiple_operators_infix_exprssn_with_precedence(){
	String rpn_expression = infixToPostfix("121 + 4 ^ 3 / 32 * 2 + 0");
	assertEqual(strcmp(rpn_expression, "121 4 3 ^ 32 / 2 * + 0 +"),0);
	free(rpn_expression);
}

void test_infixToPostfix_returns_rpn_expression_with_simple_infix_exprssn_with_precedence(){
	String rpn_expression = infixToPostfix("1 + 4 + 3 + 3 + 2 + 0 + 10");
	assertEqual(strcmp(rpn_expression, "1 4 + 3 + 3 + 2 + 0 + 10 +"),0);
	free(rpn_expression);
}

void test_infixToPostfix_returns_rpn_expression_with_plus_minus_infix_exprssion_with_precedence(){
	String rpn_expression = infixToPostfix("1 - 4 + 3 - 3 + 2 - 0 / 5");
	assertEqual(strcmp(rpn_expression, "1 4 - 3 + 3 - 2 + 0 5 / -"),0);
	free(rpn_expression);
}

void test_infixToPostfix_returns_rpn_expression_with_complex_infix_exprssn_with_precedence(){
	String rpn_expression = infixToPostfix(" 121 + 4 * 3 / 32 - 2 + 0 ");
	assertEqual(strcmp(rpn_expression, "121 4 3 * 32 / + 2 - 0 +"),0);
	free(rpn_expression);
}

void test_popOutToQ_moves_stack_top_to_que(){
	Queue q = createQueue();
	Stack s = createStack();
	String s1="+", s2="(", operator;
	push(s, s1); push(s, s2);
	assert((*s.top)->data == s2);
	popOutToQ(q, s, &operator);
	assert(strcmp(q.list->head->data,s2) == 0);
	assert((*s.top)->data == s1);
}

void test_popUntilOpeningParenthesisFound_moves_stack_elements_between_parenthesis_to_queue_with_space_in_between(){
	Queue q = createQueue();
	Stack s = createStack();
	String s1="+", s2="(", s3="+", s4="-",s5="*",space=" ",token;
	push(s, s1); push(s, s2); push(s, s3); 
	push(s, s4); push(s, s5);
	assert(popUntilOpeningParenthesisFound(s, q, &token)==1);
	assert(strcmp(q.list->head->data,s5) == 0);
	assert(strcmp(q.list->tail->data,space) == 0);
}

void test_popUntilOpeningParenthesisFound_returns_0_when_stack_is_empty(){
	Queue q = createQueue(); Stack s = createStack();
	assert(popUntilOpeningParenthesisFound(s, q, NULL)==0);
}

void test_infixToPostfix_returns_rpn_expression_with_simple_infix_exprssion_with_parenthises(){
	String rpn_expression = infixToPostfix(" 2 + ( 10 + 5 ) + 4");
	assertEqual(strcmp(rpn_expression, "2 10 5 + + 4 +"),0);
	free(rpn_expression);
}

void test_infixToPostfix_returns_rpn_expression_from_infix_exprssion_with_parenthises(){
	String rpn_expression = infixToPostfix("3 + 4 * 2 / ( 1 - 5 ) ^ 2 ^ 3");
	assertEqual(strcmp(rpn_expression, "3 4 2 * 1 5 - 2 ^ 3 ^ / +"),0);
	free(rpn_expression);
}

void test_infixToPostfix_returns_rpn_expression_from_complex_infix_exprssion_with_precedence_within_parenthises(){
	String rpn_expression = infixToPostfix("123456 - 4321 + ( 120 * 49 / 7 - 12345 ) ^ 3 + 11");
	assertEqual(strcmp(rpn_expression, "123456 4321 - 120 49 * 7 / 12345 - 3 ^ + 11 +"),0);
	free(rpn_expression);
}

void test_infixToPostfix_returns_rpn_expression_from_complex_infix_exprssion_with_precedence_within_multiple_parenthises(){
	String rpn_expression = infixToPostfix("123 - 41 + ( 12 * ( 9 / 7 ) - 12 + ( 9 * 30 ) ) ^ 2 + 10");
	assertEqual(strcmp(rpn_expression, "123 41 - 12 9 7 / * 12 - 9 30 * + 2 ^ + 10 +"),0);
	free(rpn_expression);
}

void test_infixToPostfix_returns_rpn_expression_from_complex_infix_exprssion_with_precedence_within_nested_parenthises(){
	String rpn_expression = infixToPostfix("1234 - 67 + (124 * ( 49 / 7 - 12 + ( 9 * 30 - 14 ) - ( 1 / 1 ) ) + 0 ) ^ 2 + 10");
	assertEqual(strcmp(rpn_expression, "1234 67 - 124 49 7 / 12 - 9 30 * 14 - + 1 1 / - * 0 + 2 ^ + 10 +"),0);
	free(rpn_expression);
}

void test_evaluate_gives_answer_of_rpn_expression_converted_by_infixToPostfix(){
	String rpn_expression = infixToPostfix("1 - 4 + 3 - 3 + 2 - 0 / 5");
	assertEqual(strcmp(rpn_expression, "1 4 - 3 + 3 - 2 + 0 5 / -"),0);
	assertEqual(evaluate(rpn_expression).status, -1);
	free(rpn_expression);
}

void test_evaluate_gives_answer_of_simple_rpn_expression_converted_by_infixToPostfix(){
	String rpn_expression = infixToPostfix("3 + 4 * 2 / ( 1 - 5 ) ^ 2 ^ 3");
	assertEqual(strcmp(rpn_expression, "3 4 2 * 1 5 - 2 ^ 3 ^ / +"),0);
	assert(evaluate(rpn_expression).status == 3);
	free(rpn_expression);
}

void test_evaluate_gives_answer_of_rpn_expression_converted_by_my_infixToPostfix(){
	String rpn_expression = infixToPostfix(" 123 -  41 + ( 12 * ( 9 / 7 ) - 12 + ( 9 * 30 )) ^ 1 + 10");
	assertEqual(strcmp(rpn_expression, "123 41 - 12 9 7 / * 12 - 9 30 * + 1 ^ + 10 +"),0);
	assert(evaluate(rpn_expression).status == 362);
	free(rpn_expression);
}