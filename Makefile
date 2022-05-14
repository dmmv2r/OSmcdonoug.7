C = gcc
CFLAGS = -Wall -g

TARGETS = chain

all: $(TARGETS)

chain: chain.o
	$(C) $(CFLAGS) -o $@ chain.o

clean:
	rm -rf *.o $(TARGETS)

