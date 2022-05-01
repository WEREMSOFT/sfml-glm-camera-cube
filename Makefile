SRC = $(shell find src -name *.cpp)
OBJ = $(patsubst %.cpp,%.o,$(SRC))
CC = g++
FLAGS = -g -O2
LIBS = -lsfml-window -lsfml-graphics -lsfml-system
TARGET = bin/main.bin


all: clean copy_assets $(OBJ)
	$(CC) $(FLAGS) $(OBJ) -o $(TARGET) $(LIBS)

%.o: %.cpp
	$(CC) -c $(FLAGS) $^ -o $@

run_main: all
	$(TARGET)

copy_assets:
	cp -rf resources bin

clean:
	rm -rf $(OBJ) $(TARGET)