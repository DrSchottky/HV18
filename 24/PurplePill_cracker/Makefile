all: red blue

blue:
		gcc -DTEST -Wall -O2 blue.c rabbit.c -oblue
red:
		gcc -DTEST -Wall -O3 -pthread red.c rabbit.c -ored
clean:
		rm -f blue red
		
.PHONY:all
