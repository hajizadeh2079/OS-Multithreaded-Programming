CC = g++ -std=c++11

all: PhonePricePrediction.out

PhonePricePrediction.out: main.o
	${CC} main.o -o PhonePricePrediction.out -pthread

main.o: main.cpp
	${CC} -c main.cpp -pthread

.PHONY: clean
clean:
	rm *.o
	rm *.out