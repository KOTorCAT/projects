CC = gcc
CFLAGS = -Wall -Wextra -Werror -std=c11
COVERAGE_FLAGS = -fprofile-arcs -ftest-coverage
DLL = -lcheck -lsubunit -lm -lncurses

TARGET = tetris
TEST_TARGET = tetris_test

PATH_BACKEND = brick_game/tetris/
PATH_FRONTEND = gui/cli/
PATH_TESTS = tests/

SRC = tetris.c \
      $(PATH_BACKEND)fsm.c \
      $(PATH_BACKEND)fsm_matrix.c \
      $(PATH_BACKEND)tetris_backend.c \
      $(PATH_FRONTEND)tetris_frontend.c

SRC_H = tetris.h \
        $(PATH_BACKEND)defines.h \
        $(PATH_BACKEND)fsm.h \
        $(PATH_BACKEND)objects.h \
        $(PATH_BACKEND)tetris_backend.h \
        $(PATH_FRONTEND)tetris_frontend.h

OBJ = $(patsubst %.c, %.o, $(SRC))

BACKEND_SRC = $(PATH_BACKEND)fsm.c \
              $(PATH_BACKEND)fsm_matrix.c \
              $(PATH_BACKEND)tetris_backend.c

TEST_SRC = $(PATH_TESTS)test_main.c \
           $(PATH_TESTS)test_tetris_backend.c \
           $(PATH_TESTS)test_fsm.c \
           $(PATH_TESTS)test_fsm_matrix.c \
           $(PATH_TESTS)test_helpers.c

TEST_OBJ = $(patsubst %.c, %.o, $(TEST_SRC))

PREFIX ?= $(HOME)/.local
DESTDIR ?=
BIN_DIR = $(DESTDIR)$(PREFIX)/bin
SHARE_DIR = $(DESTDIR)$(PREFIX)/share/$(TARGET)

ifneq (,$(findstring gcov_report,$(MAKECMDGOALS)))
    CFLAGS += $(COVERAGE_FLAGS)
endif

all: $(TARGET)

$(TARGET): $(OBJ)
	$(CC) $(CFLAGS) -o $@ $^ $(DLL)

$(TEST_TARGET): $(filter-out tetris.o, $(OBJ)) $(TEST_OBJ)
	$(CC) $(CFLAGS) -o $@ $^ $(DLL)

test: $(TEST_TARGET)
	./$(TEST_TARGET)

gcov_report: clean $(TEST_TARGET)
	./$(TEST_TARGET)
	@gcov $(BACKEND_SRC) --object-directory $(PATH_BACKEND)
	@lcov --capture --directory $(PATH_BACKEND) --output-file coverage.info --ignore-errors unused
	@lcov --remove coverage.info "tests/*" "gui/*" "tetris.c" --output-file coverage.info --ignore-errors unused
	@genhtml coverage.info --output-directory gcov_report

install: $(TARGET)
	mkdir -p $(BIN_DIR)
	cp $(TARGET) $(BIN_DIR)/
	mkdir -p $(SHARE_DIR)
	cp -r ../docs/ $(SHARE_DIR)/ 2>/dev/null || true

uninstall:
	rm -f $(BIN_DIR)/$(TARGET)
	rm -rf $(SHARE_DIR)

clean:
	rm -f $(OBJ) $(TEST_OBJ) $(TARGET) $(TEST_TARGET)
	rm -f $(PATH_BACKEND)*.gcno $(PATH_BACKEND)*.gcda
	rm -f *.gcno *.gcda *.info coverage.info
	rm -rf gcov_report
	find . -name "*.gcov" -delete
	find . -name "*.gcda" -delete
	find . -name "*.gcno" -delete

dist:
	mkdir -p dist
	tar -czf dist/$(TARGET).tar.gz \
		$(SRC) $(SRC_H) Makefile ../README.md \
		../docs/state_diagram.png \
		--transform='s|^|$(TARGET)/|'

dvi:
	mkdir -p ../docs
	echo "BrickGame Tetris Documentation" > ../docs/manual.txt
	echo "=============================" >> ../docs/manual.txt
	echo "Build date: $(shell date)" >> ../docs/manual.txt
	echo "Version: 1.0" >> ../docs/manual.txt
	echo "Target: $(TARGET)" >> ../docs/manual.txt
	echo "" >> ../docs/manual.txt
	echo "Available make targets:" >> ../docs/manual.txt
	echo "- all: Build the main executable" >> ../docs/manual.txt
	echo "- test: Run unit tests" >> ../docs/manual.txt
	echo "- install: Install to system" >> ../docs/manual.txt
	echo "- clean: Remove build artifacts" >> ../docs/manual.txt
	echo "- dist: Create distribution package" >> ../docs/manual.txt

valgrind: $(TARGET)
	valgrind --leak-check=full --show-leak-kinds=definite --errors-for-leak-kinds=definite ./$(TARGET)

valgrind_clean: clean
	find . -name "vgcore.*" -delete

.PHONY: all test gcov_report install uninstall clean dist dvi valgrind valgrind_clean