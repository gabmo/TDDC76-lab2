CC = clang++
FLAGS = -std=c++11 -Wall -Wextra -Wpedantic -Werror #-L/sw/gcc-${GCC4_V}/lib -static-libstdc++
FILES = lab2.cc Monetary.cc

all:
	$(CC) $(FLAGS) -c $(FILES)
	$(CC) $(FLAGS) *.o

debug:
	$(CC) $(FLAGS) -c -g $(FILES)
	$(CC) $(FLAGS) -g *.o

clean:
	rm *.o
	rm a.out
