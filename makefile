ALTOBJS = example/alt.cpp src/config.cpp
OBJS = example/main.cpp src/config.cpp
CC = clang++
COMPILER_FLAGS = -Wall -Wextra -std=c++11 -pedantic
LINKER_FLAGS = 
OBJ_NAME = bin/config

all : $(OBJS)
	$(CC) $(OBJS) $(COMPILER_FLAGS) $(LINKER_FLAGS) -o $(OBJ_NAME)
	cp src/settings.conf bin/settings.conf

alt : $(OBJS)
	$(CC) $(ALTOBJS) $(COMPILER_FLAGS) $(LINKER_FLAGS) -o $(OBJ_NAME)
	cp src/settings.conf bin/settings.conf
