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

void test_evaluate_returns_the_result_of_postfix_multiplication_of_two_digits_144_for_12_and_12(){
	string expression = "12 12 *";
	assertEqual(evaluate(expression), 144);
}

void test_evaluate_returns_the_result_of_postfix_division_of_two_digits_7_for_84_and_12(){
	string expression = "84 12 /";
	assertEqual(evaluate(expression), 7);
}

void test_evaluate_returns_the_result_of_postfix_three_digits_addition_465_for_123_and_342(){
	string expression = "123 342 +";
	assertEqual(evaluate(expression), 465);
}

void test_evaluate_returns_the_result_of_postfix_three_digits_division_80_for_960_and_12(){
	string expression = "960 12 /";
	assertEqual(evaluate(expression), 80);
}

void test_evaluate_returns_the_result_of_postfix_four_digits_addition_15_for_12_and_3(){
	string expression = "1234 4321 +";
	assertEqual(evaluate(expression), 5555);
}

void test_evaluate_returns_the_result_of_postfix_four_digits_subtraction_minus_3087_for_1234_and_4321(){
	string expression = "1234 4321 -";
	assertEqual(evaluate(expression), -3087);
}

void test_evaluate_returns_the_result_of_postfix_five_digits_addition_15_for_12_and_3(){
	string expression = "12734 43827 +";
	assertEqual(evaluate(expression), 56561);
}

void test_evaluate_returns_the_result_of_postfix_five_digits_division_by_3_digit_number(){
	string expression = "27183 123 /";
	assertEqual(evaluate(expression), 221);
}

void test_evaluate_returns_the_result_of_postfix_expression_for_2_3_and_4(){
	string expression = "2 3 4 + -";
	assertEqual(evaluate(expression), -5);
}

void test_evaluate_returns_the_result_of_postfix_expression_for_22_3_and_4(){
	string expression = "22 3 4 * + ";
	assertEqual(evaluate(expression), 34);
}

void test_evaluate_returns_the_result_of_postfix_complex_multiplication_of_1_2_3_4_5(){
	string expression = "1 2 3 4 5 * * * * ";
	assertEqual(evaluate(expression), 120);
}

void test_evaluate_returns_the_result_of_postfix_complex_expression_of_2_2_2_2_3(){
	string expression = "2 2 2 * 2 - 3 + + ";
	assertEqual(evaluate(expression), 7);
}

void test_evaluate_returns_the_result_of_postfix_complex_expression_of_2_2_2_2_2_2_2(){
	string expression = "2 2 2 2 2 * * 2 + + 2 - *";
	assertEqual(evaluate(expression), 20);
}

void test_evaluate_returns_the_result_of_postfix_complex_expression_of_2_2_2_2_2_2(){
	string expression = "2 2 - 2 2 2 * 2 - - -";
	assertEqual(evaluate(expression), 0);
}

// void test_evaluate_returns_the_result_of_postfix_complex_expression_of_5_1_2_4_3(){
// 	string expression = "5 1 2 + 4 × + 3 −"; printf("%s\n",expression);
// 	assertEqual(evaluate(expression), 14);
// }