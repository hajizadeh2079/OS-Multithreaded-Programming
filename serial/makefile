CC = g++ -std=c++11

all: PhonePricePrediction.out

PhonePricePrediction.out: main.o
	${CC} main.o -o PhonePricePrediction.out

main.o: main.cpp
	${CC} -c main.cpp

.PHONY: clean
clean:
	rm *.o
	rm *.out