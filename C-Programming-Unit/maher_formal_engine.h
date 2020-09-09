/**************************************************************************************************
Program Name:   maher_formal_engine.h
Author:         Maher SEBAI
Organization:   DSTI - C Programming Introduction
Date:           19/04/2018
Version:        v1.0
Brief:          Header File for Formal Computation Engine Using Reverse Polish Notation Implementation
***************************************************************************************************/
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include <ctype.h>
#include <math.h>
#define MAX_EXPRESSION_LENGTH 1024
#define MAX_VAR_LENGTH        24

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


// Basic Node structure, holds either a value, a variable name or an operator
typedef struct CharNode {
    int value;                      // number
    double shadowvalue;             // mirroring value as RPN should output a double (due to division operator)
	char op;                        // operator
	char varName[MAX_VAR_LENGTH];   // variable name/symbol
	bool isOp;                      // true if node is an operator
	bool isValue;                   // true if node is a value
	bool isVariable;                // true is node is a variable name
	struct CharNode * Next;         // Next linked list node pointer
} CharNode_t;

// Node initialzation
void initNode (CharNode_t * Node); 

// operator recognition
bool isOperator(char op); 

// Operator precedence
int GetOpPrecedence(char op); 

// function to remove all white spaces from a provided string
void RemoveSpaces(char* source);

// linked list creation given a raw expression input
// in this step, every character (digit, letter & operator) will land in a separate node
// optimization will be performed in other steps
CharNode_t * ParseRawExpression ( const char * source); 

// Now we are going to concatenate contiguous digits into multi-digits Value
void ConcatenateValueNodes(CharNode_t * Head); 

// Now we are going to concatenate contiguous char into multi-letter variable
void ConcatenateVariableNodes(CharNode_t * Head); 

// Utility function to find in a linked list repeated VarName and assign it the same value
void SearchAndAssign(CharNode_t * Head, char * str, int val); 

// whenever we encounter a variable name symbol, ask the user to provide the value
// in case of duplication, the same value is assigned to all repeated symbol
void AssignVarNameValue(CharNode_t * Head);

// handling of negative numbers at the input
// we differentiate between the negative sign
// and the '-' subtraction Operator
void ProcessNegative(CharNode_t * Head); 

// Duplicate Node
// utility function to duplicate/clone node in order not to corrupt linked list pointers chain
CharNode_t * DuplicateNode (CharNode_t * Node); 

// Duplicate linked list
// Utility function to clone a whole linked list using previous function
CharNode_t * DuplicateList (CharNode_t * Head); 

// Stack push
void push(CharNode_t ** Top, CharNode_t * op); 

// Stack pop
CharNode_t * pop(CharNode_t ** Top);

// Append to Queue
void AppendToQueue(CharNode_t ** Head, CharNode_t * Node); 

// Destroy a linked list to free memory
void DestroyList (CharNode_t ** Head); 

// Shunting Yard algorithm: transform infix expression to postfix expression
// using operator stack
CharNode_t * ShuntingYard(CharNode_t * Head); 

// Reverse Polish Notation calculation
// using value stack
double ComputeRPN(CharNode_t * Head); 

// utilility function to find number of Variable Nodes
int CountVariables(CharNode_t * Head); 

//utility function to removed Redundant variable Nodes
void RemoveRedundantNode(CharNode_t * Head); 

// utility function to print Unique variable names.
// This function is just cosmetic, SearchAndAssign works just fine without it
void PrintUniqueVariable(CharNode_t * Head); 

// Utility function to print linked list Node with its content
void PrintLinkedList(CharNode_t * Head);

// Utility function to convert and print a linked list into a string
void PrintListToString(CharNode_t * Head);

// Main Formal Engine Function
double MaherFormalEngine ( const char * rawInput);