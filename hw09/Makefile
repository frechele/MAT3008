all: main

%.o: %.c
	gcc -o $@ -c $^

main: main.o
	gcc -o $@ $^ -L ./nr/ -lnr -lm

clean:
	rm *.o main
