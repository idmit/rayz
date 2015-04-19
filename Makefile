CXX       = g++
LD        = g++

CFLAGS    = -g -Wall -std=c++11 -pedantic-errors
LIBS      = -Llib -lpng -lyaml-cpp -lpoly34 -ltinyobjloader

MODULES   = geometries nodes .
SRC_DIR   = $(addprefix src/, $(MODULES))
BUILD_DIR = $(addprefix build/, $(MODULES))
BIN_DIR   = bin

SRC       = $(foreach sdir, $(SRC_DIR), $(wildcard $(sdir)/*.cpp))
OBJ       = $(patsubst src/%.cpp, build/%.o, $(SRC))
INCLUDES  = $(addprefix -I, $(SRC_DIR)) -Iinclude

TARGET    = rayz

vpath %.cpp $(SRC_DIR)

define make-goal
$1/%.o: %.cpp
	$(CXX) $(CFLAGS) $(INCLUDES) -c $$< -o $$@
endef

.PHONY: all checkdirs clean

all: checkdirs $(TARGET)

$(TARGET): $(OBJ)
	$(LD) $(LIBS) $^ -o $(BIN_DIR)/$@

checkdirs: $(BUILD_DIR)

$(BUILD_DIR):
	mkdir -p $@

clean:
	rm $(BIN_DIR)/$(TARGET)
	rm -rf build/*

$(foreach bdir, $(BUILD_DIR), $(eval $(call make-goal, $(bdir))))