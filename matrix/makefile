TARGET = test_matrix
CC = gcc
CFLAGS = -Wall -Wextra -Werror -std=c11 -g
COVERAGE_FLAGS = -fprofile-arcs -ftest-coverage
TEST_LIBS = -lcheck -lm -lpthread -lsubunit
SRC = s21_matrix.c
OBJ = $(SRC:.c=.o)
OBJ_COV = $(SRC:.c=_cov.o)

TEST_SRC = test.c
TEST_OBJ = $(TEST_SRC:.c=.o)
TEST_OBJ_COV = $(TEST_SRC:.c=_cov.o)  

LIB_NAME = s21_matrix.a
LIB_COV_NAME = s21_matrix_cov.a

.PHONY: all clean test gcov_report rebuild valgrind format

all: build test gcov_report

build: $(LIB_NAME)

$(LIB_NAME): $(OBJ)
	ar rcs $(LIB_NAME) $(OBJ)
	ranlib $(LIB_NAME)

$(LIB_COV_NAME): $(OBJ_COV)
	ar rcs $(LIB_COV_NAME) $(OBJ_COV)
	ranlib $(LIB_COV_NAME)

test: $(LIB_NAME) $(TEST_OBJ)
	$(CC) $(CFLAGS) $(TEST_OBJ) -L. -l:$(LIB_NAME) $(TEST_LIBS) -o $(TARGET)
	./$(TARGET)

gcov_report: $(LIB_COV_NAME) $(TEST_OBJ_COV)  
	$(CC) $(CFLAGS) $(COVERAGE_FLAGS) $(TEST_OBJ_COV) -L. -l:$(LIB_COV_NAME) $(TEST_LIBS) -o $(TARGET)
	./$(TARGET)
	lcov -t "$(TARGET)" -o $(TARGET).info -c -d . --include "*.c"
	lcov --remove $(TARGET).info "/usr/*" --ignore-errors unused -o $(TARGET).filtered.info
	genhtml -o report $(TARGET).filtered.info
	@echo "Coverage report: report/index.html"

%_cov.o: %.c
	$(CC) $(CFLAGS) $(COVERAGE_FLAGS) -c $< -o $@

%.o: %.c s21_matrix.h
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	rm -rf *.o *.gcno *.gcda $(TARGET) *.a report *.info

format:
	clang-format -i *.h *.c

rebuild: clean all

valgrind: $(TARGET)
	valgrind --leak-check=full --show-leak-kinds=definite --errors-for-leak-kinds=definite ./$(TARGET)