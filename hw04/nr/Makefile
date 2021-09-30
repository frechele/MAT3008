SRCS:=rtbis.c rtflsp.c rtnewt.c rtsafe.c rtsec.c nrutil.c zbrak.c
OBJS:=$(SRCS:.c=.o)
STATIC_LIB:=libnr.a

all: $(STATIC_LIB)

%.o: %.c
	gcc -o $@ -c $^

$(STATIC_LIB): $(OBJS)
	ar cr $@ $^

clean:
	rm $(OBJS) $(STATIC_LIB)
