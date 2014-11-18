CXX=g++
CXXFLAGS=-g -c -Wall -std=gnu++11
LDFLAGS=-pthread -lX11
SOURCES=$(wildcard *.cpp)
OBJECTS=${SOURCES:.cpp=.o}
TITLE=A7

.PHONY : all clean

# make all
all: $(TITLE)

# make
$(TITLE): $(OBJECTS)
	$(CXX) -g -o $@ $^ $(LDFLAGS)

# make %.o
%.o: %.cpp
	$(CXX) $(CXXFLAGS) -o $@ $< -MMD -MF ./$@.d $(LDFLAGS)

# make clean
clean :
	rm -f *.o *.d $(TITLE)

-include $(wildcard ./*.d)
