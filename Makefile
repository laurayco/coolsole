
PROJECT_NAME := "coolsole"

LIB_EXTENSION := ".a"

TEST := bin/$(PROJECT_NAME)-TEST
LIB := lib/lib$(PROJECT_NAME)$(LIB_EXTENSION)
MODULE := lib/lib$(PROJECT_NAME)MODULE$(LIB_EXTENSION)

BIN_FILES = $(LIB) $(TEST)

CXXFLAGS := -Wall

TEST_SOURCES:=$(wildcard src/test-*.cpp)
TEST_OBJS := $(patsubst %.cpp, %.o,$(patsubst src/%, obj/%,$(TEST_SOURCES)))

.PHONY: pretty run clean rebuild

all: pretty $(BIN_FILES)

rebuild: clean all

pretty: $(wildcard src/*.cpp) $(wildcard include/*.hpp) $(wildcard include/*.h)
	@echo "Prettifying sources..."
	@AStyle $^ $(ASTYLE_OPTIONS)

clean:
	@rm -f $(BIN_FILES)
	@rm -f obj/*.o

run: all
	./bin/$(TEST)

obj/%.o:./src/%.cpp
	g++ -o $@ -c $< $(CXXFLAGS)

$(TEST): $(LIB) $(TEST_OBJS)
	g++ $< -o $@ $(CXXFLAGS)