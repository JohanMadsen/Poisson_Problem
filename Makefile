SRCS	= poisson.c init.c datatools.c iterator.c xtime.c
OBJS	= $(SRCS:.c=.o)
TARGET	= poisson.$(CC)

CC	= suncc
INCS	=
DBG	= -g
OPT	= -O3 -march=native -xrestrict -xvpara -xlibmopt -xlibmil
PARA	= -xopenmp
CFLAGS	= $(DBG) $(OPT) $(PARA) $(XOPTS)

LIBS	= -lm

all: $(TARGET)

$(TARGET): $(OBJS)
	$(CC) $(CFLAGS) -o $@ $(OBJS) $(LIBS)

clean:
	@/bin/rm -f $(OBJS) *~ core*

realclean: clean
	@/bin/rm -f $(TARGET)
