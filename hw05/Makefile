all: problem1 problem2 problem3

%.o: %.c
	gcc -o $@ -c $^

problem1: problem1.o lineareq.o
	gcc -o $@ $^ -L ./nr/ -lnr -lm

problem2: problem2.o lineareq.o
	gcc -o $@ $^ -L ./nr/ -lnr -lm

problem3: problem3.o lineareq.o
	gcc -o $@ $^ -L ./nr/ -lnr -lm

clean:
	rm *.o problem1 problem2 problem3
