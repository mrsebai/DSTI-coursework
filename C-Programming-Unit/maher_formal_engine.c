/**************************************************************************************************
Program Name:   maher_formal_engine.c
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


// Node initialzation
void initNode (CharNode_t * Node) {
    Node->value         = 0;
    Node->shadowvalue   = 0;
    memset(Node->varName, '\0', sizeof(Node->varName));
    Node->isOp          = false;
    Node->isValue       = false;    
    Node->isVariable    = false;
    Node->Next          = NULL;
}// initNode ...

// operator recognition
bool isOperator(char op) {
    bool result = false;
    if ( op == '+' || op == '-' || op == '*' || op == '/' || op == '^' || op == '(' || op == ')' ) result = true;
    return result;
}

// Operator precedence
int GetOpPrecedence(char op) {
    int result;
    switch (op) {
        case '+': result = 1; break;
        case '-': result = 1; break;
        case '*': result = 2; break;
        case '/': result = 2; break;
        case '^': result = 3; break;
        default : result = 0; break;
    }
    return result;
}//GetOpPrecedence ...

// function to remove all white spaces from a provided string
void RemoveSpaces(char* source) {
  char* i = source;
  char* j = source;
  do {
      *i = *j;
      if(*i != ' ') i++;
  } while (*j++ != 0);
}//RemoveSpaces ...

// linked list creation given a raw expression input
// in this step, every character (digit, letter & operator) will land in a separate node
// optimization will be performed in other steps
CharNode_t * ParseRawExpression ( const char * source) {
    CharNode_t * resultHead = NULL;
	CharNode_t * CurrentNode = NULL;
	// First we create the head of the linked list
	resultHead = malloc( sizeof(CharNode_t) );
	if (resultHead == NULL) {
	    printf("Unable to malloc in line %d file %s", __LINE__, __FILE__);
	    return NULL;
	}
	// Working node to process each Expression char
    initNode(resultHead);
	CurrentNode = resultHead;
	int i;
	// First parsing Loop. each char will fall in one the the 3 categories:
	// operator, single digit value, or single letter variable.
	// Any other char will cause Program Error.
	for (i = 0; source[i] != '\0'; i++) {
	    if ( isOperator(source[i]) ) {
	        // This is an operator Node
	        CurrentNode->op = source[i];
	        CurrentNode->isOp = true;
	        CurrentNode->Next = malloc( sizeof(CharNode_t) );
	        if (CurrentNode->Next == NULL) { printf("Unable to malloc in line %d file %s", __LINE__, __FILE__); return NULL; }
            initNode(CurrentNode->Next);
	        CurrentNode = CurrentNode->Next ;
	    } else if ( isdigit(source[i]) ) {
	        // This is a single digit Node
	        CurrentNode->value = (int)(source[i] - '0');
            CurrentNode->isValue = true;
	        CurrentNode->Next = malloc( sizeof(CharNode_t) );
	        if (CurrentNode->Next == NULL) { printf("Unable to malloc in line %d file %s", __LINE__, __FILE__); return NULL; }
            initNode(CurrentNode->Next);
	        CurrentNode = CurrentNode->Next ;
	    } else if ( isalpha(source[i]) ) {
	        // This is a single lettre Node
	        memset(CurrentNode->varName, '\0', sizeof(CurrentNode->varName));
	        strncpy( CurrentNode->varName, &source[i], 1 );
            CurrentNode->isVariable = true;
	        CurrentNode->Next = malloc( sizeof(CharNode_t) );
	        if (CurrentNode->Next == NULL) { printf("Unable to malloc in line %d file %s", __LINE__, __FILE__); return NULL; }
            initNode(CurrentNode->Next);
	        CurrentNode = CurrentNode->Next ;
	    } else {
	        // Error otherwise
	        printf("Illegal Character Encountered: %c. Only alpha-numeric and +-*/ characters allowed in line %d file %s",source[i], __LINE__, __FILE__);
	        return NULL;
	    } //else ...
	} //for  ...

	return resultHead ;
}//ParseRawExpression ...

// Now we are going to concatenate contiguous digits into multi-digits Value
void ConcatenateValueNodes(CharNode_t * Head) {
    CharNode_t * CurrentNode = NULL;
    CharNode_t * TrashNode   = NULL;
    CurrentNode = Head;
    while (CurrentNode->Next != NULL) {
        // when two digits are contiguous
        if ( CurrentNode->isValue && CurrentNode->Next->isValue ) {
            // value computation: left_digit * 10 + right_digit
            CurrentNode->value = CurrentNode->value * 10 + CurrentNode->Next->value;
            CurrentNode->shadowvalue = (double) CurrentNode->value;
            TrashNode = CurrentNode->Next;
            CurrentNode->Next = CurrentNode->Next->Next;
            free(TrashNode);
        } else {
            CurrentNode->shadowvalue = (double) CurrentNode->value;
            CurrentNode = CurrentNode->Next;
        }//else ...

    }//while ...
}//ConcatenateValueNodes ...

// Now we are going to concatenate contiguous char into multi-letter variable
void ConcatenateVariableNodes(CharNode_t * Head) {
    CharNode_t * CurrentNode;
    CharNode_t * TrashNode;
    CurrentNode = Head;
    while (CurrentNode->Next != NULL) {
        // when two letters are contiguous, concatenate them
        if ( CurrentNode->isVariable && CurrentNode->Next->isVariable ) {
            strcat(CurrentNode->varName, CurrentNode->Next->varName);
            TrashNode = CurrentNode->Next;
            CurrentNode->Next = CurrentNode->Next->Next;
            free(TrashNode);
        } else {
            CurrentNode = CurrentNode->Next;
        }//else ...

    }//while ...
}//ConcatenateVariableNodes ...

// Utility function to find in a linked list repeated VarName and assign it the same value
void SearchAndAssign(CharNode_t * Head, char * str, int val) {
    CharNode_t * CurrentNode;
    CurrentNode = Head;
    while (CurrentNode->Next != NULL) {
        if ( strcmp(CurrentNode->varName, str) == 0 ) {
            CurrentNode->value = val;
            CurrentNode->shadowvalue = (double) val;
            CurrentNode->isValue = true;
        }
        CurrentNode = CurrentNode->Next;
    }//while ...

}//SearchAndAssign ...

// whenever we encounter a variable name symbol, ask the user to provide the value
// in case of duplication, the same value is assigned to all repeated symbol
void AssignVarNameValue(CharNode_t * Head) {
    int val = 0;
    CharNode_t * CurrentNode;
    CurrentNode = Head;
    while (CurrentNode->Next != NULL) {
        if ( CurrentNode->isVariable && !CurrentNode->isValue ) {
            printf("Please provide value for Variable %s = ", CurrentNode->varName);
            scanf("%d", &val);
            CurrentNode->value = val;
            CurrentNode->shadowvalue = (double) val;
            CurrentNode->isValue = true;
            // look for duplicated variable name
            SearchAndAssign(CurrentNode, CurrentNode->varName, val);
        }
        // Move on to next node
        CurrentNode = CurrentNode->Next;
    }//while ...

}//AssignVarNameValue ..

// handling of negative numbers at the input
// we differentiate between the negative sign
// and the '-' subtraction Operator
void ProcessNegative(CharNode_t * Head) {
        CharNode_t * CurrentNode;
        CharNode_t * TrashNode;
        CurrentNode = Head;
        // First let's process negative sign at the beginning of expression. ex: -a + b
        if ((CurrentNode->isOp) && (CurrentNode->op == '-') && (CurrentNode->Next->isValue)) {
            // we are going to transform Head Node from '-' op node to negative value node
            TrashNode = CurrentNode->Next;
            CurrentNode->op = 0;
            CurrentNode->isOp = false;
            CurrentNode->value = -(CurrentNode->Next->value);
            CurrentNode->shadowvalue = (double) CurrentNode->value;
            CurrentNode->isValue = true;
            CurrentNode->Next = CurrentNode->Next->Next;
            free(TrashNode);
        }
        // Process the rest of the list
        while (CurrentNode->Next->Next != NULL) {
            // if two op are followed by a value and the second op is '-' then negate value
            if ( (CurrentNode->isOp) &&
                (CurrentNode->op != ')') &&
                (CurrentNode->Next->isOp) &&
                (CurrentNode->Next->Next->isValue) &&
                (CurrentNode->Next->op == '-')) {
                // negate value
                CurrentNode->Next->Next->value = -(CurrentNode->Next->Next->value);
                CurrentNode->Next->Next->shadowvalue = (double) CurrentNode->Next->Next->value;
                //remove the negative sign Node
                TrashNode = CurrentNode->Next;
                CurrentNode->Next = CurrentNode->Next->Next;
                free(TrashNode);
            }
            // Move on to next node
            CurrentNode = CurrentNode->Next;
        }//while ...
}//ProcessNegative ...

// Duplicate Node
// utility function to duplicate/clone node in order not to corrupt linked list pointers chain
CharNode_t * DuplicateNode (CharNode_t * Node) {
    CharNode_t * NewNode;
    if (Node != NULL) {
        NewNode =  malloc ( sizeof(CharNode_t) );
        if (NewNode == NULL) { printf("Unable to malloc in line %d file %s", __LINE__, __FILE__); return NULL; }
        NewNode->value          = Node->value;
        NewNode->shadowvalue    = Node->shadowvalue;
	    NewNode->op             = Node->op;
	    strcpy(NewNode->varName   ,Node->varName);
	    NewNode->isOp           = Node->isOp;
	    NewNode->isValue        = Node->isValue;
    	NewNode->isVariable     = Node->isVariable;
    	// next pointer NOT duplicated, NULL instead
    	NewNode->Next           = NULL;
    }
	return NewNode;
}//DuplicateNode ...

// Duplicate linked list
// Utility function to clone a whole linked list using previous function
CharNode_t * DuplicateList (CharNode_t * Head) {
    CharNode_t * DuplicatedHead;
    CharNode_t * CurrentNode;
    CharNode_t * DuplicatedNode;
    DuplicatedHead  = DuplicateNode(Head);
    CurrentNode = Head;
    DuplicatedNode = DuplicatedHead;
    while (CurrentNode->Next != NULL) {
        DuplicatedNode->Next  = DuplicateNode(CurrentNode->Next);
        CurrentNode = CurrentNode->Next;
        DuplicatedNode = DuplicatedNode->Next;
    }
    return DuplicatedHead;
}//DuplicateList ...

// Stack push
void push(CharNode_t ** Top, CharNode_t * op) {
    if (*Top == NULL) {
        *Top = op;
    } else {
        op->Next = *Top;
        *Top = op;
    }
}//push ...

// Stack pop
CharNode_t * pop(CharNode_t ** Top) {
    CharNode_t * result = *Top;
    CharNode_t * NextTop = *Top;
    NextTop = NextTop->Next;
    *Top = NextTop;
    return result;
}//pop ...

// Append to Queue
void AppendToQueue(CharNode_t ** Head, CharNode_t * Node) {
        CharNode_t * CurrentNode;
        CurrentNode = *Head;
        if (*Head == NULL) {
            *Head = Node;
        } else {
            // Append at the end of Queue
            while (CurrentNode->Next != NULL) {
                CurrentNode = CurrentNode->Next;
            }
            CurrentNode->Next = Node;
        }//else ...
}//AppendToQueue ...

// Destroy a linked list to free memory
void DestroyList (CharNode_t ** Head) {
        CharNode_t * CurrentNode;
        CharNode_t * TrashNode;
        CurrentNode = *Head;
        while (CurrentNode->Next != NULL) {
            TrashNode = CurrentNode;
            CurrentNode = CurrentNode->Next;
            free(TrashNode);
        }//while ...
        // don't forget last one
        free(CurrentNode);
}//DestroyList ...

// Shunting Yard algorithm: transform infix expression to postfix expression
// using operator stack
CharNode_t * ShuntingYard(CharNode_t * Head) {
    // Operator stack
    CharNode_t * OpStack = NULL;
    // Output list representing postfix expression
    CharNode_t * Output = NULL;
    // Working nodes
    CharNode_t * CurrentNode = NULL;
    CharNode_t * OutputNode = NULL;
    CurrentNode = Head;

    while (CurrentNode->Next != NULL) {
        if ( CurrentNode->isValue ) {
            AppendToQueue( &Output, DuplicateNode(CurrentNode) );
        } else if (CurrentNode->isOp) {
            // three cases to consider, '(', ')', '+-*/^'
            if (CurrentNode->op == '(') {
                // if '(' just push it in OpStack
                push( &OpStack, DuplicateNode(CurrentNode) );
            } else if (CurrentNode->op == ')') {
                //if ')' then pop all op from OpStack till '('
                do {
                    OutputNode = pop( &OpStack );
                    if (OutputNode->op != '(') {
                        AppendToQueue( &Output, DuplicateNode(OutputNode) );
                    }
                } while(OutputNode->op != '(');
                // get rid of '(' node
                free(OutputNode);
            } else  {
                // if '+-*/' then manage according to precedence
                while( (OpStack != NULL) && (GetOpPrecedence(CurrentNode->op) <= GetOpPrecedence(OpStack->op)) ) {
                        OutputNode = pop( &OpStack );
                        AppendToQueue( &Output, DuplicateNode(OutputNode) );
                        free(OutputNode);
                }//while ...
                push( &OpStack, DuplicateNode(CurrentNode) );
            }//else ...
        }//else ...
        // Move on to next Expression node
        CurrentNode = CurrentNode->Next;
    }//while ...

    // At the end of parsing infix expression, we need to empty OpStack into Output
    while( OpStack != NULL ) {
        OutputNode = pop( &OpStack );
        AppendToQueue( &Output, DuplicateNode(OutputNode) );
        free(OutputNode);
    }//while ...

    // Queue a dummy final node
    AppendToQueue( &Output, DuplicateNode(CurrentNode) );

    // Algorithm done
    return Output;

}//ShuntingYard ...

// Reverse Polish Notation calculation
// using value stack
double ComputeRPN(CharNode_t * Head) {
    double result = 0;
    double operand_left = 0, operand_right = 0;
    CharNode_t * valStack = NULL;
    CharNode_t * TrashNode = NULL;
    CharNode_t * CurrentNode;
    CurrentNode = Head;
    while (CurrentNode->Next != NULL) {
        if (CurrentNode->isValue) {
            push( &valStack, DuplicateNode(CurrentNode) );
        } else {
            TrashNode = pop(&valStack);
            operand_right = TrashNode->shadowvalue;
            operand_left  = valStack->shadowvalue;
            switch(CurrentNode->op) {
                case '^': valStack->shadowvalue = pow(operand_left, operand_right); break;
                case '/': valStack->shadowvalue = operand_left / operand_right;     break;
                case '*': valStack->shadowvalue = operand_left * operand_right;     break;
                case '+': valStack->shadowvalue = operand_left + operand_right;     break;
                case '-': valStack->shadowvalue = operand_left - operand_right;     break;
                default : printf("Error, Unrecognized Operator\n");
            }//switch ...
            free(TrashNode);
        }//else ...
        CurrentNode = CurrentNode->Next;
    }//while ...

    // at the end of Algorithm, only one element
    // should remain in the stack with end result
    if(valStack->Next == NULL) {
        result = valStack->shadowvalue;
        printf("Computed RPN = %.4f\n", result);
        return result;
    } else {
        printf("Error, Too Many items left on the Value stack");
        return 0;
    }//else ...

}//ComputeRPN ...


// utilility function to find number of Variable Nodes
int CountVariables(CharNode_t * Head) {
    CharNode_t * CurrentNode;
    int result = 0;
    CurrentNode = Head;
    while (CurrentNode->Next != NULL) {
        if ( CurrentNode->isVariable == true ) {
            result++ ;
        }
        CurrentNode = CurrentNode->Next;
    }//while ...
    return result;
    
}//CountVariables ...

//utility function to removed Redundant variable Nodes
void RemoveRedundantNode(CharNode_t * Head) {
    CharNode_t * CurrentNode;
    CharNode_t * TrashNode;
    CurrentNode = Head;
    while (CurrentNode->Next != NULL) {
        if (( CurrentNode->Next->isVariable == true ) && ( strcmp(CurrentNode->Next->varName, Head->varName) == 0 )) {
            TrashNode = CurrentNode->Next;
            CurrentNode->Next = CurrentNode->Next->Next;
            free(TrashNode);
        }
        CurrentNode = CurrentNode->Next;
    }//while ...    
}//RemoveRedundantNode ...

// utility function to print Unique variable names.
// This function is just cosmetic, SearchAndAssign works just fine without it
void PrintUniqueVariable(CharNode_t * Head) {
    CharNode_t * DuplicatedHead;
    CharNode_t * CurrentNode;
    char str[MAX_EXPRESSION_LENGTH] = "";
    int count = 0;    
    DuplicatedHead = DuplicateList(Head);
    CurrentNode = DuplicatedHead;
    
    // print message only if there are variables in the expression list
    if (CountVariables(DuplicatedHead) != 0) {
        while (CurrentNode->Next != NULL) {
            if ( CurrentNode->isVariable == true ) {
                RemoveRedundantNode(CurrentNode);
            }
            CurrentNode = CurrentNode->Next;
        }//while ...
        // at this step, unique variable names remains
        count = CountVariables(DuplicatedHead);
        CurrentNode = DuplicatedHead;
        while (CurrentNode->Next != NULL) {
            if ( CurrentNode->isVariable == true ) {
                sprintf(str, "%s %s", str, CurrentNode->varName);
            }
            CurrentNode = CurrentNode->Next;
        }//while ...
        printf("There are %d Unique Variable Names: %s\n", count, str);
        DestroyList(&DuplicatedHead);       
    }//if ...  
    
}//PrintUniqueVariable ...

// Utility function to print linked list Node with its content
void PrintLinkedList(CharNode_t * Head) {
    int i = 0;
    CharNode_t * CurrentNode;
    CurrentNode = Head;
    while (CurrentNode->Next != NULL) {
        printf("Node #%d \t Value = %d, \t ShadowValue = %f, \t Variable = %s, \t Operator = %c \n", i, CurrentNode->value, CurrentNode->shadowvalue, CurrentNode->varName, CurrentNode->op);
        CurrentNode = CurrentNode->Next;
        i++;
    }//while ...
}//PrintLinkedList ...

// Utility function to convert and print a linked list into a string
void PrintListToString(CharNode_t * Head) {
    char str[MAX_EXPRESSION_LENGTH] = "";
    CharNode_t * CurrentNode;
    CurrentNode = Head;
    while (CurrentNode->Next != NULL) {
        if (CurrentNode->isValue) {
            sprintf(str,"%s %d",str,CurrentNode->value);
        } else if (CurrentNode->isOp) {
            sprintf(str,"%s %c",str,CurrentNode->op);
        }//if ...
        CurrentNode = CurrentNode->Next;
    }//while ...
    printf("%s\n",str);
}// PrintListToString ...

// Main Formal Engine Function
double MaherFormalEngine ( const char * rawInput) {
	CharNode_t * infixHead = NULL;
	CharNode_t * postfixHead = NULL;
    
	printf("=> Removing White Spaces ...\n");
	RemoveSpaces(rawInput);
	printf("Raw input Expression to process:\n%s\n",rawInput);
	printf("Raw input Expression Length =  %d\n",strlen(rawInput));

	printf("=> Parsing Raw Expression ...\n");
	infixHead = ParseRawExpression(rawInput);
	//PrintLinkedList(infixHead);

	printf("=> Concatenating Values ...\n");
	ConcatenateValueNodes(infixHead);
	//PrintLinkedList(infixHead);

	printf("=> Concatenating Variable letters ...\n");
	ConcatenateVariableNodes(infixHead);
	//PrintLinkedList(infixHead);

	printf("=> Parsing Variables  ...\n");
	PrintUniqueVariable(infixHead);
	//PrintLinkedList(infixHead);

	printf("=> Assigning Variables ...\n");
	AssignVarNameValue(infixHead);
	//PrintLinkedList(infixHead);

	printf("=> Processing Negative Signs ...\n");
	ProcessNegative(infixHead);
	//PrintLinkedList(infixHead);

	printf("=> Shunting Yard ...\n");
	postfixHead = ShuntingYard(infixHead);
	//PrintLinkedList(postfixHead);
	printf("=> Infix Expression Original:\n");
	PrintListToString(infixHead);
	printf("=> Postfix Expression Result:\n");
	PrintListToString(postfixHead);

	printf("=> Reverse Polish Notation ...\n");
	ComputeRPN(postfixHead);

	//House Keeping
	DestroyList(&infixHead);
	DestroyList(&postfixHead);    
}