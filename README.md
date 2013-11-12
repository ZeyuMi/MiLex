# MiLex

## Introduction

MiLex is a project for generating lexical analyzer, whose idea is exactly the same as Flex. 

### Features

* Supporting not only regular expression meta symbols described in Dragon book, such as * | (), but also some other symbols like ? + []
* Converting regular expression to its corresponding non-deterministic finite automaton(NFA)
* Converting NFA to a DFA(Deterministic finite automaton)
* Optimizeing a DFA to a DFA with minimum states(Not included now)
* Generating lexical analyzer from an optimized DFA

## Usage
Build sources:

    make

Write your own lex.l which defines lexical grammers


Generate lex.yy.c:

	./Milex lex.l


## Input File Format

* MiLex input files have the same structures as those of Lex and Flex, which are splitted into three sections, say definition section, rule section and additional function section
* You can use *, ?, +, |, (, ), [, ], ., and " to write your regular expressions
* All files ended with ".l" in tests directory are conrete examples of MiLex input files

## Contributors

* [ZeyuMi](http://www.github.com/ZeyuMi)
