all: uniform gaussian

%.o: %.c
	gcc -o $@ -c $^

uniform: uniform.o
	gcc -o $@ $^ -L ./nr/ -lnr -lm

gaussian: gaussian.o
	gcc -o $@ $^ -L ./nr/ -lnr -lm

clean:
	rm *.o uniform gaussian
