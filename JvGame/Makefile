CC=g++
target = supercatrio

SRCS=$(wildcard *.cpp)
SRCS+=$(wildcard JvGame/*.cpp)
OBJS=$(patsubst %cpp,%o,$(SRCS))

INCLUDE = -I/usr/include/SDL2
LIB = -L/usr/lib -lSDL2 -lSDL2_image -lSDL2_ttf -lSDL2_mixer

all:$(OBJS)
	$(CC) $(OBJS) -o $(target) $(LIB)

%.o:%.cpp
	$(CC) -c $< -o $@  $(INCLUDE)

clean:
	rm $(OBJS) $(target) -f

