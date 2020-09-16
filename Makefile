DistanceVector:main.o
	g++ main.o -o DistanceVector

main.o:main.cpp
	g++ -std=c++11 -c main.cpp

clean:
	rm *.o DistanceVector