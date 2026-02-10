CC = gcc
CFLAGS = -std=c99 -pedantic -Werror -Wall -Wextra -Wvla
TARGET = evalexpr
all: evalexpr


evalexpr: src/evalexpr.o
		$(CC)  -o evalexpr src/evalexpr.o

check:
		 ./tests/test.sh
clean:
		$(RM) $(OBJS) $(TARGET) src/evalexpr.o 
