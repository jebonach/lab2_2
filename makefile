CXX = g++
CXXFLAGS = -std=c++17 -Wall -Wextra -pedantic

all: tests lab2
	@clear
	@cowsay -f hellokitty "гениальная лаба компилится, пока представьте как ставите за нее отл"
	@./tests
	@cowsay -f ren "Она даже тесты прошла, это точно отл"
	@./lab2
	@cowsay -f dragon "гениальная лаба"

ui: lab2
	@clear
	@./lab2
tests: tests.o
	@clear
	@$(CXX) $(CXXFLAGS) tests.o -o tests
	@./tests

lab2: main.o ui.o
	@$(CXX) $(CXXFLAGS) main.o ui.o -o lab2

main.o: main.cpp ui.h
	@$(CXX) $(CXXFLAGS) -c main.cpp

ui.o: ui.cpp ui.h ListSequence.h
	@$(CXX) $(CXXFLAGS) -c ui.cpp

tests.o: tests.cpp DynamicArray.h LinkedList.h ArraySequence.h ListSequence.h Sequence.h
	@$(CXX) $(CXXFLAGS) -c tests.cpp

clean:
	@rm -f *.o lab2 tests
