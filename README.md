# DSTI-coursework
This repo contains all course assignements, exams and projects produced during the year study at [Data ScienceTech Institute](https://www.datasciencetech.institute).

## C-Programming Unit:

We were assigned a fun little project: coding a *Small Formal Computation Engine Using Reverse Polish Notation Implementation*.

The goal is to acquire from the user a *mathematical expression in [infixed notation](https://en.wikipedia.org/wiki/Infix_notation)* and turn it into an *expression in postfixed notation* (also known as [Reversed Polish Notation](https://en.wikipedia.org/wiki/Reverse_Polish_notation)). The conversion from infixed to postfixed notation is implemented using [The famous Shunting-yard algorithm](https://en.wikipedia.org/wiki/Shunting-yard_algorithm)

An example of infixed notation of an expression for the input:
`3 + 4 × 2 ÷ ( 1 − 5 ) ^ 2 ^ 3`

The same expression using Reversed Polish Notation (or postfixed notation) for the output:
`3 4 2 × 1 5 − 2 3 ^ ^ ÷ +`

Our implementation is in Plain C using linked-list data structure and has the following features:
- power '^' operator support along with '+', '-', '*', '/', '(' and ')' operators
- support for multi-letter variable and their repetition
- negative sign full support without collision with subtraction operator

Example of input with abstract variable names: `-a +2 *a +5*(alpha - beta +b *c +a)/alpha -(-beta)^c`

### Implementation:

- [link to c file ](C-Programming-Unit/maher_formal_engine.c)
- [link to log file](C-Programming-Unit/MaherFormalEngine.log.txt)
