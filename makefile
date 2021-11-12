all: main.o inread.o inread.h
	gcc -o output main.o inread.o

main.o: main.c inread.h
	gcc -c main.c

inread.o: inread.c inread.h
	gcc -c inread.c

run:
	./output

read_csv:
	./output -read_csv

read_data:
	./output -read_data

add_data:
	./output -add_data

update_data:
	./output -update_data

clean:
	rm *.o
	rm output
	rm nyc_pop.data
