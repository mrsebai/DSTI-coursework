# DSTI-coursework
This repo contains all course assignements, exams and projects produced during the year study at [Data ScienceTech Institute](https://www.datasciencetech.institute).

## C-Programming Unit:

We were assigned a fun little project: coding a *Small Formal Computation Engine Using Reverse Polish Notation Implementation*.
The goal is to acquire from the user a *mathematical expression in [infixed notation](https://en.wikipedia.org/wiki/Infix_notation)* and turn it into an *expression in postfixed notation* (also known as [Reversed Polish Notation](https://en.wikipedia.org/wiki/Reverse_Polish_notation)). The conversion from infixed to postfixed notation is implemented using [The famous Shunting-yard algorithm](https://en.wikipedia.org/wiki/Shunting-yard_algorithm).

Our implementation is in Plain C using linked-list data structure and has the following features:
- power `^` operator support along with `+`, `-`, `*`, `/`, `(` and `)` operators
- support for multi-letter variable and their repetition
- negative sign full support without collision with subtraction operator

Some examples:
- input in infixed notation:`3 + 4 × 2 ÷ ( 1 − 5 ) ^ 2 ^ 3`
- output of same expression in Reversed Polish Notation (or postfixed notation): `3 4 2 × 1 5 − 2 3 ^ ^ ÷ +`
- input with abstract variable names with repetition: `-a +2 *a +5*(alpha - beta +b *c +a)/alpha -(-beta)^c`

### Implementation:

- [link to c file ](C-Programming-Unit/maher_formal_engine.c)
- [link to log file](C-Programming-Unit/MaherFormalEngine.log.txt)

## SQL Unit:
Using [WideWorldImporters Sample Database for SQL Server](https://github.com/microsoft/sql-server-samples/tree/master/samples/databases/wide-world-importers), the 5 hours exam consists of 5 queries intended to produce table results that should perfectly match a provided ones.
- [Question & solution 1](SQL-Unit/SQL-Answer-1.txt)
- [Question & solution 2](SQL-Unit/SQL-Answer-2.txt)
- [Question & solution 3](SQL-Unit/SQL-Answer-3.txt)
- [Question & solution 4](SQL-Unit/SQL-Answer-4.txt)
- [Question & solution 5](SQL-Unit/SQL-Answer-5.txt)

## Fondation and Advanced Statistics for Machine Learning:

## Survival Analysis:

## metaheuristics optimization:

## Semantic Web:

## Agent-Based Modeling:

## Intro To Deep Learning:
