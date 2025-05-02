CXX = g++
CXXFLAGS = -std=c++17 -Wall -Wextra -pedantic -g

SRC_COMMON = errors.cpp
OBJ_COMMON = $(SRC_COMMON:.cpp=.o)

SRC_APP = main.cpp ui.cpp
OBJ_APP = $(SRC_APP:.cpp=.o)

SRC_TEST = tests.cpp
OBJ_TEST = $(SRC_TEST:.cpp=.o)

all: tests lab3
	@clear
	@./tests
	@./lab3

ui: lab3
	@clear
	@./lab3

tests: $(OBJ_TEST) $(OBJ_COMMON)
	@clear
	@$(CXX) $(CXXFLAGS) $^ -o $@
	@./tests

lab3: $(OBJ_APP) $(OBJ_COMMON)
	@$(CXX) $(CXXFLAGS) $^ -o $@

main.o: main.cpp ui.h
	@$(CXX) $(CXXFLAGS) -c $<

ui.o: ui.cpp ui.h \
      Sequence.h Queue.h \
      ArraySequence.h ListSequence.h \
      ArrayQueue.h  CycleQueue.h \
      ArrayPQueue.h ListQueue.h ListPQueue.h \
      errors.h
	@$(CXX) $(CXXFLAGS) -c $<

tests.o: tests.cpp \
         DynamicArray.h LinkedList.h \
         Sequence.h ArraySequence.h ListSequence.h \
         Queue.h ArrayQueue.h  CycleQueue.h \
         ArrayPQueue.h ListQueue.h ListPQueue.h \
         errors.h
	@$(CXX) $(CXXFLAGS) -c $<

errors.o: errors.cpp errors.h how_to_train_your_exception.h
	@$(CXX) $(CXXFLAGS) -c $<

clean:
	@rm -f *.o lab3 tests
