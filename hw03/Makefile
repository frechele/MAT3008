all: problem1 problem2 problem3 problem4

%.o: %.c
	gcc -o $@ -O3 -c $^

problem1: problem1.o
	gcc -o $@ $< -L ./nr/ -lnr -lm

problem2: problem2.o muller.o
	gcc -o $@ $^ -L ./nr/ -lnr -lm

problem3: problem3.o muller.o
	gcc -o $@ $^ -O3 -L ./nr/ -lnr -lm

problem4: problem4.o
	gcc -o $@ $< -L ./nr/ -lnr -lm

clean:
	rm *.o problem1 problem2 problem3 problem4
