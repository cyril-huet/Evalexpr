CC = gcc
CFLAGS = -std=c99 -pedantic -Werror -Wall -Wextra -Wvla

TARGET = evalexpr

SRC = src/main.c src/stack.c src/output.c src/result.c src/utils.c src/rpn.c src/shunting.c
OBJ = $(SRC:.c=.o)

all: $(TARGET)

$(TARGET): $(OBJ)
	$(CC) $(CFLAGS) -o $(TARGET) $(OBJ)

# règle pour compiler les .c en .o
src/%.o: src/%.c
	$(CC) $(CFLAGS) -c $< -o $@

check: all
	./tests/test.sh

clean:
	$(RM) $(OBJ) $(TARGET)
