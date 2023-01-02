CC= g++ 
CFLAGS= -std=c++20 -Wall
DEPS= $(wildcard *.h)
SOURCES= $(wildcard *.cpp)
OBJECTS= $(patsubst %.cpp, %.o, $(SOURCES))
#Created with help from Zan Huang
%.o: %.cpp $(DEPS)
	$(CC) -O3 -std=c++20 -c -o $@ $<

brainfuck: $(OBJECTS)
	$(CC) $(CFLAGS) -O3 -o brainfuck $(OBJECTS)
debug: $(OBJECTS)
	$(CC) $(CFLAGS) -g3 -o brainfuck_debug $(OBJECTS) 
.PHONY: clean
clean:
	rm -f *.o brainfuck brainfuck_debug
