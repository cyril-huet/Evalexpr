# Evalexpr

[![CI](https://github.com/cyril-huet/Evalexpr/actions/workflows/ci.yml/badge.svg)](https://github.com/cyril-huet/Evalexpr/actions/workflows/ci.yml)
![C](https://img.shields.io/badge/C-C99-blue.svg)
[![License](https://img.shields.io/badge/license-MIT-green.svg)](LICENSE)

Evalexpr is a small command-line calculator written in C99.

It evaluates arithmetic expressions written in the usual infix notation or in Reverse Polish Notation (RPN).

This project was made as an educational exercise to practice parsing, stacks, operator priorities and error handling.

## Features

- Addition, subtraction, multiplication and division
- Modulo and power operators
- Parentheses
- Positive and negative numbers
- Infix expressions
- RPN expressions
- Basic syntax error handling
- Division-by-zero detection
- Simple shell test suite
- Automatic checks with GitHub Actions

## Build

Requirements:

- A C99 compiler
- `make`
- `clang-format` for format checks

```sh
git clone https://github.com/cyril-huet/Evalexpr.git
cd Evalexpr
make
```

The executable is called `evalexpr`.

## Usage

### Infix expressions

```sh
printf "1 + 1\n" | ./evalexpr
```

```text
2
```

```sh
printf "(2 + 3) * 4\n" | ./evalexpr
```

```text
20
```

### RPN expressions

Use the `-rpn` option:

```sh
printf "1 1 +\n" | ./evalexpr -rpn
```

```text
2
```

```sh
printf "2 3 4 * +\n" | ./evalexpr -rpn
```

```text
14
```

## Operators

| Operator | Description |
|----------|-------------|
| `+`      | Addition |
| `-`      | Subtraction |
| `*`      | Multiplication |
| `/`      | Division |
| `%`      | Modulo |
| `^`      | Power |

Parentheses and negative numbers are supported in infix mode.

## Project structure

```text
.
├── Makefile
├── README.md
├── LICENSE
├── src/
│   ├── main.c
│   ├── parser.c
│   ├── parser.h
│   ├── rpn.c
│   ├── rpn.h
│   ├── stack.c
│   ├── stack.h
│   ├── output.c
│   ├── output.h
│   ├── result.c
│   ├── result.h
│   ├── utils.c
│   └── utils.h
├── tests/
│   └── test.sh
└── .github/
    └── workflows/
        └── ci.yml
```

Each source file has a specific responsibility:

- `main.c`: reads the input and prints the result
- `parser.c`: converts infix expressions into RPN
- `rpn.c`: evaluates RPN expressions
- `stack.c`: manages the operator stack
- `output.c`: manages parsed expression elements
- `result.c`: manages calculation results
- `utils.c`: contains small utility functions

## Tests

Run the complete test suite:

```sh
make check
```

Check the code formatting:

```sh
make check-format
```

Format the source files:

```sh
make format
```

The tests cover:

- Basic arithmetic
- Operator priorities
- Parentheses
- Negative numbers
- RPN expressions
- Invalid expressions
- Division by zero
- Invalid command-line arguments

## Error codes

| Code | Meaning |
|------|---------|
| `0`  | Successful execution |
| `1`  | Invalid expression |
| `3`  | Arithmetic error |
| `4`  | Invalid arguments or memory error |

## Limitations

Evalexpr is intentionally small. It does not currently support:

- Floating-point numbers
- Variables
- Mathematical functions
- Multiple expressions in one input
- Advanced mathematical notation

## Continuous integration

GitHub Actions automatically runs the following checks:

```sh
make
make check-format
make check
```

## License

This project is distributed under the MIT License.

See the [LICENSE](LICENSE) file for more information.