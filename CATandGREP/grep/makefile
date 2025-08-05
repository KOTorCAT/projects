CC = gcc
FLAGS = -std=c11 -Wall -Wextra -Werror
SRC = s21_grep.c
HDR = s21_grep.h  
OBJ = $(SRC:.c=.o)
EXE = s21_grep

all: $(EXE)

$(EXE): $(OBJ) $(HDR)
	$(CC) $(FLAGS) $(OBJ) -o $(EXE)

%.o: %.c $(HDR)
	$(CC) $(FLAGS) -c $< -o $@

clean:
	rm -f $(EXE) $(OBJ)

tests: all test_s21_grep.sh
	bash test_s21_grep.sh

rebuild: clean all

.PHONY: all clean tests rebuild
