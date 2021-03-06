CXX       = g++
LD        = g++

ifeq ($(OS), Windows_NT)
	LIB_DIR = lib/win
else
	UNAME_S := $(shell uname -s)
	ifeq ($(UNAME_S), Linux)
		LIB_DIR = lib/lnx
	endif
	ifeq ($(UNAME_S), Darwin)
		LIB_DIR = lib/osx
	endif
endif

CFLAGS    = -Wall -Wno-comment -std=c++11 -pedantic-errors
LIBS      = -L$(LIB_DIR) -lpoly34 -ltinyobjloader -lyaml-cpp

MODULES   = geometries nodes lights .
SRC_DIR   = $(addprefix src/, $(MODULES))
BUILD_DIR = $(addprefix build/, $(MODULES))
BIN_DIR   = bin

SRC       = $(foreach sdir, $(SRC_DIR), $(wildcard $(sdir)/*.cpp))
OBJ       = $(patsubst src/%.cpp, build/%.o, $(SRC))
INCLUDES  = $(addprefix -I, $(SRC_DIR)) -Iinclude

TARGET    = rayz

DEBUG     ?= 0
ifeq ($(DEBUG), 1)
	CFLAGS += -g3 -DDEBUG
else
	CFLAGS += -O3
endif

vpath %.cpp $(SRC_DIR)

define make-goal
$1/%.o: %.cpp
	$(CXX) $(CFLAGS) $(INCLUDES) -c $$< -o $$@
endef

.PHONY: all checkdirs clean

all: bindir builddirs $(TARGET)

$(TARGET): $(OBJ)
	$(LD) $^ -o $(BIN_DIR)/$@ $(LIBS)

bindir:
	mkdir -p $(BIN_DIR)

builddirs: $(BUILD_DIR)

$(BUILD_DIR):
	mkdir -p $@

clean:
	rm -rf $(BIN_DIR)/$(TARGET)
	rm -rf build/*

$(foreach bdir, $(BUILD_DIR), $(eval $(call make-goal, $(bdir))))