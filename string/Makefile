TARGET = main_test
CC = gcc 
CFLAGS = -Wall  -Wextra -std=c11
DLL = -lcheck -lsubunit -lm -pthread -lrt
GCOV_FLAGS = -fprofile-arcs -ftest-coverage

PATH_TEST = test/

PATH_STR = $(PATH_TEST)test_string/
PATH_SS = $(PATH_TEST)test_sscanf/
PATH_SP = $(PATH_TEST)test_sprintf/
PATH_CSH = $(PATH_TEST)test_c_sharp_func/

SRC = $(wildcard *.c)
OBJ = $(patsubst %.c, %.o, $(SRC))

SRC_TEST = $(wildcard $(PATH_TEST)*.c) $(wildcard $(PATH_STR)*.c) $(wildcard $(PATH_SS)*.c) $(wildcard $(PATH_SP)*.c) $(wildcard $(PATH_CSH)*.c)
OBJ_TEST = $(patsubst %.c, %.o, $(SRC_TEST))

all : all clean test s21_string.a gcov_report

s21_string.a : s21_string.o s21_sprintf.o s21_sscanf.o
	ar rcs s21_string.a s21_string.o s21_sprintf.o s21_sscanf.o 
s21_string.o : s21_string.c
	@$(CC)  $(CFLAGS) -c s21_string.c s21_string.o
s21_sprintf.o : s21_sprintf.c
	@$(CC)  $(CFLAGS) -c s21_sprintf.c s21_sprintf.o
s21_sscanf.o : s21_sscanf.c
	@$(CC)  $(CFLAGS) -c s21_sscanf.c s21_sscanf.o



s21_string.a_gcov : s21_string_gcov.o s21_sprintf_gcov.o s21_sscanf_gcov.o
	ar rcs s21_string.a s21_string_gcov.o s21_sprintf_gcov.o s21_sscanf_gcov.o
s21_string_gcov.o : s21_string.c
	@$(CC) --coverage $(CFLAGS) $(GCOV_FLAGS) -c s21_string.c -o s21_string_gcov.o
s21_sprintf_gcov.o : s21_sprintf.c
	@$(CC) --coverage $(CFLAGS) $(GCOV_FLAGS) -c s21_sprintf.c -o s21_sprintf_gcov.o
s21_sscanf_gcov.o : s21_sscanf.c
	@$(CC) --coverage $(CFLAGS) $(GCOV_FLAGS) -c s21_sscanf.c -o s21_sscanf_gcov.o



test : clean s21_string.a_gcov $(OBJ_TEST)
	@$(CC) --coverage $(OBJ_TEST) -o $(TARGET) $(GCOV_FLAGS) -L. -l:s21_string.a $(DLL) 
	@./$(TARGET)

gcov_report : test
	lcov -t "main_test" -o test.info -c -d .
	mkdir report
	genhtml -o report test.info
	open report/index.html

%.o : %.c
	@$(CC) --coverage $(CFLAGS) $(GCOV_FLAGS) -c $< -o $@ 
clean :
	rm -rf *.o *.gcda *.gcno *.gcov test.info s21_string.a $(TARGET) report
	rm -rf $(PATH_TEST)*.o $(PATH_TEST)*.gcda $(PATH_TEST)*.gcno
	rm -rf $(PATH_STR)*.o $(PATH_STR)*.gcda $(PATH_STR)*.gcno
	rm -rf $(PATH_SS)*.o $(PATH_SS)*.gcda $(PATH_SS)*.gcno
	rm -rf $(PATH_SP)*.o $(PATH_SP)*.gcda $(PATH_SP)*.gcno
	rm -rf $(PATH_CSH)*.o $(PATH_CSH)*.gcda $(PATH_CSH)*.gcno
format :
	clang-format -n *.c *.h $(PATH_TEST)*.c $(PATH_STR)*.c $(PATH_SS)*.c $(PATH_SP)*.c $(PATH_CSH)*.c
	
rebuild : clean test

valgrind :
	valgrind --tool=memcheck --leak-check=full --show-leak-kinds=all --track-origins=yes ./main_test
