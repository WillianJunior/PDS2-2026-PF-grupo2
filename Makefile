CXX = g++
CXXFLAGS = -std=c++17 -Wall -Iinclude -Itests
COVERAGE_FLAGS = --coverage

SRC_DIR = src
TEST_DIR = tests
BUILD_DIR = build

SRCS = $(wildcard $(SRC_DIR)/*.cpp)
TESTS = $(wildcard $(TEST_DIR)/*.cpp)

MAIN_EXEC = $(BUILD_DIR)/sistema
TEST_EXEC = $(BUILD_DIR)/execute_tests

.PHONY: all test clean

all: $(MAIN_EXEC)

$(MAIN_EXEC): main.cpp $(SRCS)
	@mkdir -p $(BUILD_DIR)
	$(CXX) $(CXXFLAGS) main.cpp $(SRCS) -o $(MAIN_EXEC)

$(TEST_EXEC): $(SRCS) $(TESTS)
	@mkdir -p $(BUILD_DIR)
	$(CXX) $(CXXFLAGS) $(COVERAGE_FLAGS) $(SRCS) $(TESTS) -o $(TEST_EXEC)

test: $(TEST_EXEC)
	@echo "================ Executando os Testes ================"
	./$(TEST_EXEC)

	@echo ""
	@echo "================ Coverage ================"

	gcovr -r . \
	--html \
	--html-details \
	-o $(BUILD_DIR)/coverage.html \
	--exclude tests

	gcovr -r . --exclude tests

clean:
	rm -rf $(BUILD_DIR)
	find . -name "*.gcda" -delete
	find . -name "*.gcno" -delete
	find . -name "*.gcov" -delete
