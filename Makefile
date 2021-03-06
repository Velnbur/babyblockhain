SRC_DIR := src
INCLUDE_DIR := include
BIN_DIR := bin
BUILD_DIR := build
LIBS_DIR := libs
TESTS_DIR := tests

UNAME_S := $(shell uname -s)
CXX := clang++
CXXFLAGS := -Wall -g -std=c++11 -I$(INCLUDE_DIR) -I$(LIBS_DIR)

LD_FLAGS :=
LIBS := -ldl -lcrypto

ifeq ($(UNAME_S),Darwin)
CXXFLAGS += -I/usr/local/opt/libressl/include
LD_FLAGS += -L/usr/local/opt/libressl/lib
endif

CC := clang
CCFLAGS := -Wall -g -I$(LIBS_DIR)

MODULES := operation commit sha1
OBJ_MODULES := $(addprefix $(BUILD_DIR)/, $(addsuffix .o, $(MODULES)))

ifdef DEBUG
CXXFLAGS += -DDEBUG
endif

all: makedirs build clean
	echo

makedirs:
	@if [ ! -d $(BUILD_DIR) ] || [ ! -d $(BIN_DIR) ]; then \
		echo "[INFO]: creating 'build' and 'bin' directories"; \
		mkdir -p $(BUILD_DIR) $(BIN_DIR); \
	fi

$(BUILD_DIR)/sha1.o: $(LIBS_DIR)/sha1.c $(LIBS_DIR)/sha1.h
	@echo "[INFO]: Building 'sha1' library"
	@$(CC) $(CCFLAGS) -c $< -o $@

$(BUILD_DIR)/%.o: $(SRC_DIR)/%.cpp $(INCLUDE_DIR)/%.h
	@echo "[INFO]: Building '$<' module"
	@$(CXX) $(CXXFLAGS) -c $< -o $@


build: makedirs $(OBJ_MODULES)

build_example: makedirs $(OBJ_MODULES)
	@echo "[INFO]: Linking example"
	@$(CXX) $(CXXFLAGS) $(filter %.o, $^) examples/main.cpp -o $(BIN_DIR)/example $(LIBS)

clean:
	@rm $(BUILD_DIR)/*
	@rm $(BIN_DIR)/*
	@rmdir $(BUILD_DIR)
	@rmdir $(BIN_DIR)

$(BUILD_DIR)/%.o: $(TESTS_DIR)/%.cpp
	@echo "[INFO]: Building '$<' test"
	@$(CXX) $(CXXFLAGS) -c $< -o $@

TESTS := $(basename $(notdir $(wildcard $(TESTS_DIR)/*.cpp)))
OBJ_TESTS := $(addprefix $(BUILD_DIR)/, $(addsuffix .o, $(TESTS)))
OBJ_TESTS += $(OBJ_MODULES)

tests: makedirs $(OBJ_TESTS)
	@echo "[INFO]: Linking tests"
	@$(CXX) $(CXXFLAGS) $(filter %.o, $^) -o $(BIN_DIR)/tests
	@./$(BIN_DIR)/tests
