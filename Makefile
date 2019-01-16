SRCS	= main.c
OBJS	= $(SRCS:.c=.o)
TARGET	= main.$(CC)

CC	= gcc
INCS	=
DBG	=
OPT	= -Ofast
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
