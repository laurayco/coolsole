
PROJECT_NAME := $(shell basename $(CURDIR))

LIB_EXTENSION := .a
OBJ_EXTENSION := .o

TEST := bin/$(PROJECT_NAME)-TEST
LIB := lib/lib$(PROJECT_NAME)$(LIB_EXTENSION)
MODULE := lib/lib$(PROJECT_NAME)MODULE$(LIB_EXTENSION)

BIN_FILES = $(LIB) $(TEST)

CXXFLAGS := -Wall

TEST_SOURCES:=$(wildcard src/test-*.cpp)
TEST_OBJS := $(patsubst %.cpp, %$(OBJ_EXTENSION),$(patsubst src/%, obj/%,$(TEST_SOURCES)))

ASTYLE_OPTIONS:=-Z -n -c -C -xG -S -K -xn -xc -y -j -k3 -W3 -xe -N -s2

.PHONY: pretty run clean rebuild

all: pretty $(BIN_FILES)

rebuild: clean all

library: $(LIB)

pretty: $(wildcard src/*.cpp) $(wildcard include/*.hpp) $(wildcard include/*.h)
	@AStyle $^ $(ASTYLE_OPTIONS)

clean:
	@rm -f $(BIN_FILES)
	@rm -f obj/*$(OBJ_EXTENSION)

run: all
	@$(TEST)

lib/%$(LIB_EXTENSION): obj/%$(OBJ_EXTENSION)
	@ar rvs $@ $<

obj/%$(OBJ_EXTENSION): src/%.cpp
	@g++ -o $@ $^ $(CXXFLAGS) -c

test: library $(TEST)

$(TEST): $(TEST_OBJS)
	@g++ $^ -o $@ $(CXXFLAGS) -L./lib -l$(PROJECT_NAME)