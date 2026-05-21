CXX = g++
CXXFLAGS = -std=c++17 -Wall -Iinclude -Itests
COVERAGE_FLAGS = -fprofile-arcs -ftest-coverage

SRC_DIR = src
INCLUDE_DIR = include
TEST_DIR = tests
BUILD_DIR = build

SRCS = $(wildcard $(SRC_DIR)/*.cpp)
TESTS = $(wildcard $(TEST_DIR)/*.cpp)

MAIN_EXEC = $(BUILD_DIR)/sistema
TEST_EXEC = $(BUILD_DIR)/execute_tests

.PHONY: all clean test

all: $(MAIN_EXEC)

$(MAIN_EXEC): $(SRCS)
	@mkdir -p $(BUILD_DIR)
	$(CXX) $(CXXFLAGS) main.cpp $(SRCS) -o $(MAIN_EXEC)

test: $(TEST_EXEC)
	@echo "================ Executando os Testes Unitários ================"
	./$(TEST_EXEC)
	@echo "\n================ Gerando Relatório de Cobertura ================"
	gcovr -r . --html --html-details -o $(BUILD_DIR)/coverage.html
	gcovr -r . --text

$(TEST_EXEC): $(SRCS) $(TESTS)
	@mkdir -p $(BUILD_DIR)
	$(CXX) $(CXXFLAGS) $(COVERAGE_FLAGS) $(SRCS) $(TESTS) -o $(TEST_EXEC)

clean:
	rm -rf $(BUILD_DIR)
	rm -f *.gcda *.gcno $(SRC_DIR)/*.gcda $(SRC_DIR)/*.gcno $(TEST_DIR)/*.gcda $(TEST_DIR)/*.gcno
