CC = gcc
FLAGS = -std=c11 -Wall -Wextra -Werror
SRC = s21_cat.c
HDR = s21_cat.h  
OBJ = $(SRC:.c=.o)
EXE = s21_cat

all: $(EXE)

$(EXE): $(OBJ) $(HDR)
	$(CC) $(FLAGS) $(OBJ) -o $(EXE)

%.o: %.c $(HDR)
	$(CC) $(FLAGS) -c $< -o $@

clean:
	rm -f $(EXE) $(OBJ)

tests: all test_s21_cat.sh
	chmod +x test_s21_cat.sh
	./test_s21_cat.sh

rebuild: clean all

.PHONY: all clean tests rebuild
