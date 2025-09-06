CC := g++
SHELL := /bin/bash

CFLAGS := -std=c++20 -g
INCLUDE_DIR := -Iinclude

LIB_NAME := libmnistdata.so
LIB_DIR := lib
OBJ_DIR := obj
SRC_DIR := src
BIN_DIR := bin

# Source and object lists (relative paths)
SRCS := $(wildcard $(SRC_DIR)/*.cpp)
OBJS := $(patsubst $(SRC_DIR)/%.cpp,$(OBJ_DIR)/%.o,$(SRCS))
BINS := $(patsubst $(SRC_DIR)/%.cpp,$(BIN_DIR)/%,$(SRCS))

BIN_DIR := bin

.PHONY: all clean info

# Default: build library
all: $(LIB_DIR)/$(LIB_NAME)

$(LIB_DIR):
	mkdir -p "$(LIB_DIR)"

$(OBJ_DIR):
	mkdir -p "$(OBJ_DIR)"

$(BIN_DIR):
	mkdir -p "$(BIN_DIR)"

$(OBJ_DIR)/%.o: $(SRC_DIR)/%.cpp | $(OBJ_DIR)
	$(CC) $(CFLAGS) -fPIC $(INCLUDE_DIR) -c "$<" -o "$@"

$(LIB_DIR)/$(LIB_NAME): $(OBJS) | $(LIB_DIR)
	$(CC) -dynamiclib $(CFLAGS) $(INCLUDE_DIR) -o "$@" $(OBJS)

# Build main executable by linking main.cpp with the library object files
$(BIN_DIR)/main: main.cpp $(OBJS) | $(BIN_DIR)
	$(CC) $(CFLAGS) $(INCLUDE_DIR) -o "$@" main.cpp $(OBJS)

# Run main (separate target so user can run it without rebuilding the library)
run-main: $(BIN_DIR)/main
	"$(BIN_DIR)/main"

clean:
	rm -rf "$(OBJ_DIR)" "$(LIB_DIR)"/* "$(BIN_DIR)"/*

info:
	@echo SRC_DIR = "$(SRC_DIR)"
	@echo SRCS    = $(SRCS)
	@echo OBJS    = $(OBJS)
