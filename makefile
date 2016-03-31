OBJS = src/main.cpp src/config.cpp
CC = clang++
COMPILER_FLAGS = -Wall -Wextra -std=c++11 -pedantic
#LINKER_FLAGS = -lSDL2
LINKER_FLAGS = 
OBJ_NAME = bin/configtestbin

all : $(OBJS)
	$(CC) $(OBJS) $(COMPILER_FLAGS) $(LINKER_FLAGS) -o $(OBJ_NAME)
