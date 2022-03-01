DEBUG=1

OSTYPE:=$(shell uname)
VPATH=./src:./test
SLIB=./results/libcii.so
ALIB=./results/libcii.a
EXEC=./results/cii ./results/test_arith ./results/test_stack ./results/test_list ./results/test_table
OBJDIR=./obj/

ifeq ($(OSTYPE), "Darwin") # for MacOS
CC=clang
CPP=clang++
else
CC=gcc
CPP=g++
endif

AR=ar
ARFLAGS=rcs
OPTS=-Ofast
LDFLAGS= -lm -pthread
COMMON= -Iinclude/ -Isrc/
CFLAGS= -Wall -Wno-unused-result -Wno-unknown-pragmas -Wfatal-errors -fPIC
CXXFLAGS= -Wall -Wno-unused-result -Wno-unknown-pragmas -Wfatal-errors -fPIC -std=c++11

ifeq ($(DEBUG), 1)
OPTS=-O0 -g
endif

CFLAGS+=$(OPTS)

OBJ= arith.o assert.o except.o mem.o stack.o list.o atom.o table.o
EXECOBJA= cii.o test_arith.o test_stack.o test_list.o test_table.o

EXECOBJ = $(addprefix $(OBJDIR), $(EXECOBJA))
OBJS = $(addprefix $(OBJDIR), $(OBJ))
DEPS = $(wildcard src/*.h) Makefile include/cii.h


all: obj backup results $(SLIB) $(ALIB) $(EXEC)


$(EXEC): $(EXECOBJ) $(ALIB)
	$(CC) $(COMMON) $(CFLAGS) $^ -o $@ $(LDFLAGS) $(ALIB)

$(ALIB): $(OBJS)
	$(AR) $(ARFLAGS) $@ $^

$(SLIB): $(OBJS)
	$(CC) $(CFLAGS) -shared $^ -o $@ $(LDFLAGS)

$(OBJDIR)%.o: %.cpp $(DEPS)
	$(CPP) $(COMMON) $(CXXFLAGS) -c $< -o $@

$(OBJDIR)%.o: %.c $(DEPS)
	$(CC) $(COMMON) $(CFLAGS) -c $< -o $@

obj:
	mkdir -p obj
backup:
	mkdir -p backup
results:
	mkdir -p results

.PHONY: clean

clean:
	rm -rf $(OBJS) $(SLIB) $(ALIB) $(EXEC) $(EXECOBJ) $(OBJDIR)/*



