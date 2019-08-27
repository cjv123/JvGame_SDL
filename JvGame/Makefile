CC=g++
target = supercatrio

SRCS=$(wildcard *.cpp)
SRCS:=$(wildcard JvGame/*.cpp)
OBJS=$(patsubst %cpp,%o,$(SRCS))

INCLUDE = -I/usr/include/SDL2
LIB = -L/usr/lib

$(target):$(OBJS)
	$(CC) main.o -o super $(LIB)

%.o:%.cpp
	$(CC) -c $< -o $@  $(INCLUDE)

clean:
	rm $(OBJS) $(target) -f

