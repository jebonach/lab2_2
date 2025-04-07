CXX = g++
CXXFLAGS = -std=c++17 -Wall -Wextra -pedantic -g

all: tests lab2
	@clear
	@./tests
	@./lab2

ui: lab2
	@clear
	@./lab2

tests: tests.o errors.o
	@clear
	@$(CXX) $(CXXFLAGS) tests.o errors.o -o tests
	@./tests

lab2: main.o ui.o errors.o
	@$(CXX) $(CXXFLAGS) main.o ui.o errors.o -o lab2

main.o: main.cpp ui.h
	@$(CXX) $(CXXFLAGS) -c main.cpp

ui.o: ui.cpp ui.h ListSequence.h errors.h
	@$(CXX) $(CXXFLAGS) -c ui.cpp

tests.o: tests.cpp DynamicArray.h LinkedList.h ArraySequence.h ListSequence.h Sequence.h errors.h
	@$(CXX) $(CXXFLAGS) -c tests.cpp

errors.o: errors.cpp errors.h how_to_train_your_exception.h
	@$(CXX) $(CXXFLAGS) -c errors.cpp

clean:
	@rm -f *.o lab2 tests
