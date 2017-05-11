ALTOBJS = example/alt.cpp #src/config.cpp
OBJS = example/main.cpp #src/config.cpp
CC = clang++
COMPILER_FLAGS = -Wall -Wextra -std=c++11 -pedantic
LINKER_FLAGS = 
ALTOBJ_NAME = bin/altexample
OBJ_NAME = bin/example

all : main alt

main : $(OBJS)
	$(CC) $(OBJS) $(COMPILER_FLAGS) $(LINKER_FLAGS) -o $(OBJ_NAME)
	cp src/settings.conf bin/settings.conf

alt : $(OBJS)
	$(CC) $(ALTOBJS) $(COMPILER_FLAGS) $(LINKER_FLAGS) -o $(ALTOBJ_NAME)
	cp src/settings.conf bin/settings.conf
