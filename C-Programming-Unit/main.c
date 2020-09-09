/**************************************************************************************************
Program Name:   maher_rpn.c
Author:         Maher SEBAI
Organization:   DSTI - C Programming Introduction
Date:           19/04/2018
Version:        v1.0
Brief:          Small Formal Computation Engine Using Reverse Polish Notation Implementation
***************************************************************************************************/
#include "maher_formal_engine.h"

// => Program Features:
// - DSTI "C Programming intro" Project specs all implemented with following additional Features
// - power '^' operator support along with '+', '-', '*', '/', '(' and ')' operators
// - support for multi-letter variable and their repetition
// - negative sign full support without collision with subtraction operator
// => Future enhancements:
// - infix well formatting error checking (ex number of parenthesis, contiguous operators)
// - implicit operators
// - decimal number support (ex 53.97)
// - support for more operators, functions etc ...


// => Algorithm steps
// 1) Infix expression acquisition in a simple string
// 2) process raw string to eliminate all white spaces
// 3) parse the infix expression and construct a linked list out of it: every char lands in a node
// 5) process the linked list to concatenate digits to form integers
// 6) process the linked list to concatenate all letters to form multi-letter variable names
// 7) ask the user to assign values for variables while taking care of duplicates (assign same value)
// 8) process any negative sign value (not to confuse it with subtraction operator) and merge it with contiguous values
// 8) the linked list is now ready to be processed by Shunting Yard Algorithm to produce a Postfix linked list expression
// 9) The Postfix linked list expression is then processed using the Reverse Polish Notation Algorithm to calculate the result

int main() {
	char rawInput[MAX_EXPRESSION_LENGTH] = "";
    char rawInput1[MAX_EXPRESSION_LENGTH] = "-1 + 3 * -4 + 5 /(2 - -3)";
    char rawInput2[MAX_EXPRESSION_LENGTH] = "10* (5+ 5*(-9))- -3";
	int c;
    double result = 0;
    
    // Ask user for Expression to process
	printf("[Program Start] Welcome to RPN Calculator! Please input your expression, Press enter to finish: \n");
	if (scanf("%[^\n]", rawInput) == 1) {
	    // successful input
	    if ( ( c = getchar()) != '\n') {
		    // input too long
		    printf("input expression too long. Buffer overflow. Program exit\n");
		    return 1;
	    }
    } else {
	    // scanf failed
	    printf("Empty Expression detected. Nothing to Process. Program exit\n");
	    return 1;
    }
    
    // Calling Formal Engine Algorithm for user provided expression
    result = MaherFormalEngine(rawInput);
    // expected result = -12
    printf("\nPredefined Expression 1 evaluation. Expected result = -12 \n");
    result = MaherFormalEngine(rawInput1);
    printf("\nPredefined Expression 2 evaluation. Expected result = -397 \n");
    result = MaherFormalEngine(rawInput2);

	// This is the END
	printf("\n[Program End] An end is only a beginning in disguise.\n");
	return 0;
}
