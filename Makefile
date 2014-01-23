
PROJECT_NAME := $(shell basename $(CURDIR))

LIB_EXTENSION := .a
OBJ_EXTENSION := .o
MODULE_EXTENSION := .pyd

TEST := bin/$(PROJECT_NAME)-TEST
LIB := lib/lib$(PROJECT_NAME)$(LIB_EXTENSION)
LIB_SRC :=$(wildcard src/lib$(PROJECT_NAME)*.cpp)
LIB_OBJS := $(patsubst %.cpp, %.o,$(patsubst src/%, obj/%,$(LIB_SRC)))
MODULE := bin/$(PROJECT_NAME)$(MODULE_EXTENSION)

PYTHON_LOCATION := $(PYTHON)#wherever your python binary is located.
PYTHON_VERSION := 33 #obviously this should be changed appropriately.

BIN_FILES := $(LIB) $(TEST)# $(MODULE)

CXXFLAGS := -g -std=c++0x -I$(PYTHON_LOCATION)\include -fpermissive

TEST_SOURCES:=$(wildcard src/test-*.cpp)
TEST_OBJS := $(patsubst %.cpp, %$(OBJ_EXTENSION),$(patsubst src/%, obj/%,$(TEST_SOURCES)))

ASTYLE_OPTIONS:=-Z -n -c -C -xG -S -K -xn -xc -y -j -k3 -W3 -xe -N -s2 -xw -q

.PHONY: pretty run clean rebuild

all: pretty $(BIN_FILES)

rebuild: clean all

module: $(MODULE)

$(MODULE): obj/$(PROJECT_NAME)module.o
	@g++ -shared $^ $(CXXFLAGS) -L$(PYTHON_LOCATION)\libs -lpython$(PYTHON_VERSION) -o $@

pretty: $(wildcard src/*.cpp) $(wildcard include/*.hpp) $(wildcard include/*.h)
	@AStyle $^ $(ASTYLE_OPTIONS)

clean:
	@rm -f $(BIN_FILES)
	@rm -f obj/*$(OBJ_EXTENSION)

run: all
	@$(TEST)

$(LIB): $(LIB_OBJS)
	@ar rsv $@ $^

obj/%$(OBJ_EXTENSION): src/%.cpp
	@g++ -o $@ $^ $(CXXFLAGS) -c

test: $(LIB) $(TEST)

$(TEST): $(TEST_OBJS)
	@g++ $^ -o $@ $(CXXFLAGS) -L./lib -l$(PROJECT_NAME)