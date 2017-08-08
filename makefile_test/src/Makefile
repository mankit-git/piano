SRC := $(wildcard *.c)
SRC := $(filter-out main.c, $(SRC))
OBJ := $(patsubst %.c, %.o, $(SRC))

CC = $(CROSS)gcc

LIBPATH = ../lib

all:$(OBJ)

$(OBJ):%.o:%.c
	 $(CC) $^ -o $@ -c

install:$(OBJ)
	$(CC) -shared -fPIC -o $(LIBPATH)/libsum.so $(OBJ)

clean:
	$(RM) $(OBJ)
