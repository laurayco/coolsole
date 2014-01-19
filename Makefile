
PROJECT_NAME := $(shell basename $(CURDIR))

LIB_EXTENSION := .a
OBJ_EXTENSION := .o

TEST := bin/$(PROJECT_NAME)-TEST
LIB := lib/lib$(PROJECT_NAME)$(LIB_EXTENSION)
LIB_SRC :=$(wildcard src/lib$(PROJECT_NAME)*.cpp)
LIB_OBJS := $(patsubst %.cpp, %.o,$(patsubst src/%, obj/%,$(LIB_SRC)))
MODULE := lib/lib$(PROJECT_NAME)MODULE$(LIB_EXTENSION)

BIN_FILES = $(LIB) $(TEST)

CXXFLAGS := -Wall -g

TEST_SOURCES:=$(wildcard src/test-*.cpp)
TEST_OBJS := $(patsubst %.cpp, %$(OBJ_EXTENSION),$(patsubst src/%, obj/%,$(TEST_SOURCES)))

ASTYLE_OPTIONS:=-Z -n -c -C -xG -S -K -xn -xc -y -j -k3 -W3 -xe -N -s2

.PHONY: pretty run clean rebuild

all: pretty $(BIN_FILES)

rebuild: clean all

pretty: $(wildcard src/*.cpp) $(wildcard include/*.hpp) $(wildcard include/*.h)
	@AStyle $^ $(ASTYLE_OPTIONS)

clean:
	@rm -f $(BIN_FILES)
	@rm -f obj/*$(OBJ_EXTENSION)

run: all
	@$(TEST)

$(LIB): $(LIB_OBJS)
	@ar rvs $@ $^

obj/%$(OBJ_EXTENSION): src/%.cpp
	@g++ -o $@ $^ $(CXXFLAGS) -c

test: $(LIB) $(TEST)

$(TEST): $(TEST_OBJS)
	@g++ $^ -o $@ $(CXXFLAGS) -L./lib -l$(PROJECT_NAME)