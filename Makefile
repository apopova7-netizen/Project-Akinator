CC = gcc
CFLAGS = -Wall -Wextra -std=c99 -O2 -I./Include -DDATA_FILE=\"tests/trees/extendedTrees\"
LDFLAGS = -lm
TARGET = akinator

# Main program sources
MAIN_SRCS = src/main.c src/front.c src/backend.c
MAIN_OBJS = $(MAIN_SRCS:.c=.o)

# Library sources for tests (without main.c)
LIB_SRCS = src/front.c src/backend.c
LIB_OBJS = $(LIB_SRCS:.c=.o)

# Test executables (each built separately)
TEST_BACK = tests/testBack.exe
TEST_GET_ANSWER = tests/testGetAnswer.exe
TEST_CHECK_FILE = tests/testCheckFile.exe
TEST_FRONT = tests/OtherTestsFront.exe

# ===== TARGETS =====

# Build main program
all: $(TARGET)

$(TARGET): $(MAIN_OBJS)
	@$(CC) $(CFLAGS) $(MAIN_OBJS) -o $(TARGET).exe $(LDFLAGS)
	@echo "Build complete: $(TARGET).exe"

# Build and run all tests
tests: $(TEST_BACK) $(TEST_GET_ANSWER) $(TEST_CHECK_FILE) $(TEST_FRONT)
	@echo "=== Running tests ==="
	@echo ""
	@echo "--- testBack ---"
	@.\$(TEST_BACK)
	@echo ""
	@echo "--- testGetAnswer ---"
	@-.\$(TEST_GET_ANSWER)
	@echo ""
	@echo "--- testCheckFile ---"
	@.\$(TEST_CHECK_FILE)
	@echo ""
	@echo "--- OtherTestsFront ---"
	@.\$(TEST_FRONT)
	@echo ""
	@echo "All tests completed"

# Build test executables
$(TEST_BACK): tests/testBack.o $(LIB_OBJS)
	@$(CC) $(CFLAGS) tests/testBack.o $(LIB_OBJS) -o $(TEST_BACK) $(LDFLAGS)
	@echo "Built: $(TEST_BACK)"

$(TEST_GET_ANSWER): tests/testGetAnswer.o $(LIB_OBJS)
	@$(CC) $(CFLAGS) tests/testGetAnswer.o $(LIB_OBJS) -o $(TEST_GET_ANSWER) $(LDFLAGS)
	@echo "Built: $(TEST_GET_ANSWER)"

$(TEST_CHECK_FILE): tests/testCheckFile.o $(LIB_OBJS)
	@$(CC) $(CFLAGS) tests/testCheckFile.o $(LIB_OBJS) -o $(TEST_CHECK_FILE) $(LDFLAGS)
	@echo "Built: $(TEST_CHECK_FILE)"

$(TEST_FRONT): tests/OtherTestsFront.o $(LIB_OBJS)
	@$(CC) $(CFLAGS) tests/OtherTestsFront.o $(LIB_OBJS) -o $(TEST_FRONT) $(LDFLAGS)
	@echo "Built: $(TEST_FRONT)"

# ===== COMPILATION =====

src/main.o: src/main.c
	@$(CC) $(CFLAGS) -c src/main.c -o src/main.o

src/front.o: src/front.c
	@$(CC) $(CFLAGS) -c src/front.c -o src/front.o

src/backend.o: src/backend.c
	@$(CC) $(CFLAGS) -c src/backend.c -o src/backend.o

tests/testBack.o: tests/testBack.c
	@$(CC) $(CFLAGS) -DDATA_FILE2=\"tests/trees/ForTestsFile\" -c tests/testBack.c -o tests/testBack.o

tests/testGetAnswer.o: tests/testGetAnswer.c
	@$(CC) $(CFLAGS) -c tests/testGetAnswer.c -o tests/testGetAnswer.o

tests/testCheckFile.o: tests/testCheckFile.c
	@$(CC) $(CFLAGS) -c tests/testCheckFile.c -o tests/testCheckFile.o

tests/OtherTestsFront.o: tests/OtherTestsFront.c
	@$(CC) $(CFLAGS) -c tests/OtherTestsFront.c -o tests/OtherTestsFront.o

# ===== RUN =====

run: $(TARGET)
	@.\$(TARGET).exe

# ===== CLEAN =====

clean:
	@del /Q src\*.o 2>nul
	@del /Q tests\*.o 2>nul
	@del /Q $(TARGET).exe 2>nul
	@del /Q tests\*.exe 2>nul
	@echo "Cleanup complete"