proj5: project5ClassFunctions.o project5NonClassFunctions.o
	g++ -o proj5 project5ClassFunctions.o project5NonClassFunctions.o

project5ClassFunctions.o: project5ClassFunctions.cpp project5Header.h
	g++ -c project5ClassFunctions.cpp

project5NonClassFunctions.o: project5NonClassFunctions.cpp project5Header.h
	g++ -c project5NonClassFunctions.cpp

clean:
	rm project5ClassFunctions.o project5NonClassFunctions.o proj5
