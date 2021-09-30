all: problem1 problem2

%.o: %.c
	gcc -o $@ -O3 -c $^

problem1: problem1.o muller.o
	gcc -o $@ $^ -L ./nr/ -lnr -lm

problem2: problem2.o muller.o
	gcc -o $@ $^ -L ./nr/ -lnr -lm

clean:
	rm *.o problem1 problem2
