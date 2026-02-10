# Evalexpr

Evalexpr is a C program that reads an arithmetic expression from standard input
and prints the result to standard output.

The expression can be provided either in standard (infix) notation or in
reverse polish notation (RPN). All computations are performed using integers.

## Overview

This project focuses on parsing and evaluating arithmetic expressions while
respecting operator precedence, associativity, and parentheses.

It covers core concepts such as:
- lexical analysis
- expression parsing
- stack-based evaluation
- operator precedence and associativity
- robust error handling

The goal is to build a correct and reliable expression evaluator using only
standard C and well-defined rules.

## Features

- Support for **infix notation** (standard arithmetic expressions)
- Support for **reverse polish notation** (`-rpn` option)
- Integer-only arithmetic
- Unary and binary operators
- Proper operator precedence and associativity
- Parentheses handling
- Clear and consistent error codes

### Supported operators

- Addition: `+`
- Subtraction: `-`
- Multiplication: `*`
- Division: `/`
- Modulo: `%`
- Exponentiation: `^`
- Unary `+` and `-`

## Build

Build the project using `make`:

```sh
make
```


## The resulting binary will be located at
```text
./evalexpr
```



## Usage
### Evaluate an infix expression
```c
echo "1 + 1" | ./evalexpr
```
### Output:
```text
2
```

### Evaluate an expression in reverse polish notation
```c
echo "1 1 +" | ./evalexpr -rpn
```
### Output:
```text
2
```
### More examples
#### 1)
```c
echo "5*(2^2+3)" | ./evalexpr
```
### Output:
```text
35
```

#### 2)
```c
echo "5 2 2 ^ 3 + *" | ./evalexpr -rpn
```
### Output:
```text
35
```


# Tests

## The project includes a functional testsuite.

### Run the tests with:
```sh
make check
```

