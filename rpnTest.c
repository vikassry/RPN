#include "expr_assert.h"
#include "rpn.h"


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

void test_infixToPostfix_returns_the_rpn_expression_from_given_infix_expression(){
	string rpn_expression = infixToPostfix("3 + 4 * 2 / ( 1 - 5 ) ^ 2 ^ 3");
	assert(rpn_expression == "3 4 2 * 1 5 - 2 3 ^ ^ / +");
}
