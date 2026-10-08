CC = cc
CFLAGS = -std=c99 -pedantic -Wall -Wextra -Werror -Wvla
TARGET = evalexpr


# Source files
SRC = src/main.c \
      src/parser.c \
      src/rpn.c \
      src/stack.c \
      src/output.c \
      src/result.c \
      src/utils.c

HEADERS = src/parser.h \
          src/rpn.h \
          src/stack.h \
          src/output.h \
          src/result.h \
          src/utils.h

# Object files
OBJ = $(SRC:.c=.o)

all: $(TARGET)

$(TARGET): $(OBJ)
	$(CC) $(CFLAGS) $(OBJ) -o $(TARGET)

%.o: %.c $(HEADERS)
	$(CC) $(CFLAGS) -c $< -o $@

check: $(TARGET)
	./tests/test.sh

format:
	clang-format -i $(SRC) $(HEADERS)

check-format:
	clang-format --dry-run -Werror $(SRC) $(HEADERS)

clean:
	rm -f $(OBJ)

fclean: clean
	rm -f $(TARGET)

re: fclean all

.PHONY: all check format check-format clean fclean re
