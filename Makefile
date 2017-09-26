TARGETS = timer_example

OBJECTS = timer.o

DEPS=$(patsubst %.o,%.d,$(OBJECTS))

CXX = g++
CXXFLAGS= -std=c++11 -g -fno-omit-frame-pointer \
					-Wall -Wextra -Wshadow -Wpedantic -fPIC \
					-Wno-unused-parameter -Wno-unused-function

INC = -I.
LIB = -L/usr/local/lib

all: $(TARGETS)

clean:
	rm -f $(OBJECTS) $(DEPS) $(TARGETS)

timer.so: $(OBJECTS)
	$(CXX) -shared $^ -o $@ $(LIB)


timer_example: main.c timer.so
	$(CXX) $^ -o $@ $(LIB)

%.o : %.cpp
	$(CXX) -MMD -MP $(CXXFLAGS) $(INC) $< -c -o $@

-include $(DEPS)
