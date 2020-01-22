restaurant: queueFunctions.o userFile.o supportFunctions.o
	gcc -o restaurant queueFunctions.o userFile.o supportFunctions.o

queueFunctions.o: queueFunctions.c restaurantSystem.h
	gcc -c queueFunctions.c

userFile.o: userFile.c restaurantSystem.h
	gcc -c userFile.c

supportFunctions.o: supportFunctions.c restaurantSystem.h
	gcc -c supportFunctions.c

clean:
	rm restaurant queueFunctions.o userFile.o supportFunctions.o
