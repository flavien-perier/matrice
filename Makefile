CC=g++
CFLAGS=-Wall
LDFLAGS=
EXEC=main clean
SRC=$(wildcard *.cpp)
OBJ=$(SRC:.cpp=.o)

all: $(EXEC)

main: $(OBJ)
	$(CC) -o $@ $^ $(LDFLAGS)

%.o: %.cpp
	$(CC) -o $@ -c $< $(CFLAGS)

.PHONY: clean

clean :
	rm -f $(OBJ)