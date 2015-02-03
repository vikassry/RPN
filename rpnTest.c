#include "expr_assert.h"
#include "rpn.h"


void test_evaluate_returns_the_result_of_postfix_addition_5_for_2_and_3(){
	string expression = "2 3 +";
	assertEqual(evaluate(expression), 5);
}

void test_evaluate_returns_the_result_of_postfix_subtraction_minus_1_for_2_and_3(){
	string expression = "2 3 -";
	assertEqual(evaluate(expression), -1);
}

void test_evaluate_returns_the_result_of_postfix_multiplication_6_for_2_and_3(){
	string expression = "2 3 *";
	assertEqual(evaluate(expression), 6);
}

void test_evaluate_returns_the_result_of_postfix_division_0_for_2_and_3(){
	string expression = "2 3 /";
	assertEqual(evaluate(expression), 0);
}

void test_evaluate_returns_the_result_of_postfix_two_digits_addition_15_for_12_and_3(){
	string expression = "12 3 +";
	assertEqual(evaluate(expression), 15);
}

void test_evaluate_returns_the_result_of_postfix_subtraction_two_digits_minus_1_for_21_and_23(){
	string expression = "21 23 -";
	assertEqual(evaluate(expression), -2);
}

void test_evaluate_returns_the_result_of_postfix_three_digits_addition_15_for_12_and_3(){
	string expression = "123 342 +";
	assertEqual(evaluate(expression), 465);
}

void test_evaluate_returns_the_result_of_postfix_four_digits_addition_15_for_12_and_3(){
	string expression = "1234 4321 +";
	assertEqual(evaluate(expression), 5555);
}

void test_evaluate_returns_the_result_of_postfix_five_digits_addition_15_for_12_and_3(){
	string expression = "12734 43827 +";
	assertEqual(evaluate(expression), 56561);
}

// void test_evaluate_returns_the_result_of_postfix_expression_for_2_3_and_4(){
// 	string expression = "2 3 4 + -";
// 	assertEqual(evaluate(expression), -5);
// }