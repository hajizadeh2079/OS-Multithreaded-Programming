CC = g++ -std=c++11

all: PhonePricePrediction.out

PhonePricePrediction.out: main.o
	${CC} main.o -o PhonePricePrediction.out -pthreaad

main.o: main.cpp
	${CC} -c main.cpp -pthreaad

.PHONY: clean
clean:
	rm *.o
	rm *.out