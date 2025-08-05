TARGET = decimal
CC = gcc 
CFLAGS = -Wall -Wextra -std=c11
COVERAGE_FLAGS = --coverage
DLL = -lcheck -lsubunit -lm -pthread -lrt

PATH_TEST = test/
PATH_ARITHMETIC = arithmetic/
PATH_COMPARE = compare/
PATH_CONVERTORS = convertors/
PATH_OTHERS = others/
PATH_SERVICE = service/

SRC = $(wildcard *.c $(PATH_ARITHMETIC)*.c $(PATH_COMPARE)*.c $(PATH_CONVERTORS)*.c $(PATH_OTHERS)*.c $(PATH_SERVICE)*.c)
OBJ = $(patsubst %.c, %.o, $(SRC))
OBJ_COV = $(patsubst %.c, %_cov.o, $(SRC))

SRC_TEST = $(wildcard $(PATH_TEST)*.c)
OBJ_TEST = $(patsubst %.c, %.o, $(SRC_TEST))

all: s21_decimal.a s21_decimal_cov.a gcov_report

s21_decimal.a: $(OBJ)
	ar rcs s21_decimal.a $(OBJ)

s21_decimal_cov.a: $(OBJ_COV)
	ar rcs s21_decimal_cov.a $(OBJ_COV)

gcov_report: s21_decimal_cov.a $(OBJ_TEST)
	@$(CC) $(COVERAGE_FLAGS) $(OBJ_TEST) -L. -l:s21_decimal_cov.a $(DLL) -o $(TARGET)
	@./$(TARGET)
	lcov -t "$(TARGET)" -o $(TARGET).info -c -d .
	genhtml -o report $(TARGET).info

test: s21_decimal.a $(OBJ_TEST)
	@$(CC) $(OBJ_TEST) -L. -l:s21_decimal.a $(DLL) -o $(TARGET)
	@./$(TARGET)

%_cov.o: %.c
	@$(CC) $(CFLAGS) $(COVERAGE_FLAGS) -c $< -o $@

%.o: %.c
	@$(CC) $(CFLAGS) -c $< -o $@ 

clean:
	rm -rf *.o *.gcno *.gcda $(TARGET) *.a report *.info
	rm -rf $(PATH_TEST)*.o $(PATH_ARITHMETIC)*.o $(PATH_COMPARE)*.o $(PATH_CONVERTORS)*.o $(PATH_OTHERS)*.o $(PATH_SERVICE)*.o
	rm -rf $(PATH_TEST)*.gcda $(PATH_TEST)*.gcno 
	rm -rf $(PATH_ARITHMETIC)*.gcda $(PATH_ARITHMETIC)*.gcno 
	rm -rf $(PATH_COMPARE)*.gcda $(PATH_COMPARE)*.gcno 
	rm -rf $(PATH_CONVERTORS)*.gcda $(PATH_CONVERTORS)*.gcno 
	rm -rf $(PATH_OTHERS)*.gcda $(PATH_OTHERS)*.gcno 
	rm -rf $(PATH_SERVICE)*.gcda $(PATH_SERVICE)*.gcno 

format:
	clang-format -i *.h
	clang-format -i $(PATH_TEST)*.c $(PATH_TEST)*.h 
	clang-format -i $(PATH_ARITHMETIC)*.c $(PATH_ARITHMETIC)*.h 
	clang-format -i $(PATH_COMPARE)*.c $(PATH_COMPARE)*.h 
	clang-format -i $(PATH_CONVERTORS)*.c $(PATH_CONVERTORS)*.h 
	clang-format -i $(PATH_OTHERS)*.c $(PATH_OTHERS)*.h 
	clang-format -i $(PATH_SERVICE)*.c $(PATH_SERVICE)*.h 

rebuild: clean all

valgrind:
	valgrind --tool=memcheck --leak-check=full --show-leak-kinds=all --track-origins=yes ./$(TARGET)




 



