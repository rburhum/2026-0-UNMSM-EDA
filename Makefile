CXX = g++
CXXFLAGS = -std=c++17 -Wall -g -pthread -I. # Añadido -pthread
LDFLAGS = -pthread # Añadido -pthread

TARGET = main
SRCS = main.cpp util.cpp pointers.cpp \
       DemoArray.cpp \
	   algorithms/sorting.cpp DemoBTree.cpp

OBJS = $(SRCS:.cpp=.o)

TEST_TARGET = tests/test_runner
TEST_SRCS = tests/catch_amalgamated.cpp \
            tests/test_sorting.cpp \
            tests/test_array.cpp \
            tests/test_btree.cpp \
            tests/test_linkedlist.cpp \
            tests/test_binarytree.cpp
TEST_OBJS = $(TEST_SRCS:.cpp=.o)

all: $(TARGET)

$(TARGET): $(OBJS)
	$(CXX) $(LDFLAGS) $^ -o $@

%.o: %.cpp
	$(CXX) $(CXXFLAGS) -c $< -o $@

test: $(TEST_TARGET)
	./$(TEST_TARGET)

$(TEST_TARGET): $(TEST_OBJS)
	$(CXX) $(LDFLAGS) $^ -o $@

clean:
	rm -f $(OBJS) $(TARGET) $(TEST_OBJS) $(TEST_TARGET)

.PHONY: all clean test