SRC_DIR := src
INCLUDE_DIR := include
BIN_DIR := bin
BUILD_DIR := build
LIBS_DIR := libs
TESTS_DIR := tests

CXX := g++
CXXFLAGS := -Wall -g -I$(INCLUDE_DIR) -I$(LIBS_DIR)
MODULES := operation transaction sha1
OBJ_MODULES := $(addprefix $(BUILD_DIR)/, $(addsuffix .o, $(MODULES)))

ifdef DEBUG
CXXFLAGS += -DDEBUG
endif

makedirs:
	@if [ ! -d $(BUILD_DIR) ] || [ ! -d $(BIN_DIR) ]; then \
		echo "[INFO]: creating 'build' and 'bin' directories"; \
		mkdir -p $(BUILD_DIR) $(BIN_DIR); \
	fi

$(BUILD_DIR)/sha1.o: $(LIBS_DIR)/sha1.c $(LIBS_DIR)/sha1.h
	@echo "[INFO]: Building 'sha1' library"
	@$(CXX) $(CXXFLAGS) -c $< -o $@

$(BUILD_DIR)/%.o: $(SRC_DIR)/%.cpp $(INCLUDE_DIR)/%.h
	@echo "[INFO]: Building '$<' module"
	@$(CXX) $(CXXFLAGS) -c $< -o $@

build: makedirs $(OBJ_MODULES)

$(BUILD_DIR)/%.o: $(TESTS_DIR)/%.cpp
	@echo "[INFO]: Building '$<' test"
	@$(CXX) $(CXXFLAGS) -c $< -o $@

TESTS := $(basename $(notdir $(wildcard $(TESTS_DIR)/*.cpp)))
OBJ_TESTS := $(addprefix $(BUILD_DIR)/, $(addsuffix .o, $(TESTS)))

tests: makedirs $(OBJ_TESTS)
	@echo "[INFO]: Linking tests"
	@$(CXX) $(CXXFLAGS) $(filter %.o, $^) -o $(BIN_DIR)/tests
	@./$(BIN_DIR)/tests
