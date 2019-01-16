SRCS	= poisson.c init.c datatools.c iterator.c
OBJS	= $(SRCS:.c=.o)
TARGET	= poisson.$(CC)

CC	= gcc
INCS	=
DBG	= -g
OPT	= -Ofast -march=native -fno-trapping-math -funroll-loops
PARA	= -fopenmp
CFLAGS	= $(DBG) $(OPT) $(PARA) $(XOPTS)

LIBS	=

all: $(TARGET)

$(TARGET): $(OBJS)
	$(CC) $(CFLAGS) -o $@ $(OBJS) $(LIBS)

clean:
	@/bin/rm -f $(OBJS) *~ core*

realclean: clean
	@/bin/rm -f $(TARGET)
