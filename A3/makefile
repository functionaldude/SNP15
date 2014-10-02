CC=g++
CFLAGS=-c -Wall
LDFLAGS=
SOURCES=main.cpp Student.cpp Lecture.cpp Assignment.cpp
OBJECTS=$(SOURCES:.cpp=.o)
EXECUTABLE=a3


all: $(SOURCES) $(EXECUTABLE)
	
$(EXECUTABLE): $(OBJECTS) 
	$(CC) $(LDFLAGS) $(OBJECTS) -o $@

.cpp.o:
	$(CC) $(CFLAGS) $< -o $@
	

clean:
	rm -rf *o $(EXECUTABLE)
