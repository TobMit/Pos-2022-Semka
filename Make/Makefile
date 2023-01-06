TARGET = GameServer
CC = g++

all: $(TARGET)

.PHONY: all clean

GameServer: ../src/Game/MainServer.cpp ../src/SFML-client_server/Sockets/Sockets.cpp ../src/SFML-client_server/Sockets/Sockets.h ../src/SFML-client_server/Sockets/MultiServer/MultiServer.h ../src/SFML-client_server/Sockets/MultiServer/MultiServer.cpp ../src/Constants/Constants.h ../src/Constants/GameData.h ../src/Game/Server/ServerLogic.cpp ../src/Game/Server/ServerLogic.h ../src/Game/Server/ServerGame.cpp ../src/Game/Server/ServerGame.h
	#$(CC) -c  ../src/Game/MainServer.cpp ../src/SFML-client_server/Sockets/Sockets.cpp ../src/SFML-client_server/Sockets/MultiServer/MultiServer.cpp ../src/Game/Server/ServerLogic.cpp ../src/Game/Server/ServerGame.cpp -lpthread -lsfml-network -lsfml-graphics -lsfml-system
	$(CC) -o $(TARGET) MainServer.o Sockets.o MultiServer.o ServerLogic.o ServerGame.o -lpthread -lsfml-network -lsfml-graphics -lsfml-system
	#$(CC) -o GameServer src/Game/MainServer.o src/SFML-client_server/Sockets/Sockets.o src/SFML-client_server/Sockets/MultiServer/MultiServer.o src/Game/Server/ServerLogic.o src/Game/Server/ServerGame.o -lpthread -lsfml-network -lsfml-graphics -lsfml-system

GameServer.o: ../src/Game/MainServer.cpp ../src/SFML-client_server/Sockets/Sockets.cpp ../src/SFML-client_server/Sockets/Sockets.h ../src/SFML-client_server/Sockets/MultiServer/MultiServer.h ../src/SFML-client_server/Sockets/MultiServer/MultiServer.cpp ../src/Constants/Constants.h ../src/Constants/GameData.h ../src/Game/Server/ServerLogic.cpp ../src/Game/Server/ServerLogic.h ../src/Game/Server/ServerGame.cpp ../src/Game/Server/ServerGame.h
	$(CC) -o $(TARGET) MainServer.o Sockets.o MultiServer.o ServerLogic.o ServerGame.o -lpthread -lsfml-network -lsfml-graphics -lsfml-system
#clean:
#	rm $(OUTPUTS)

# Makefile for Writing Make Files Example

# *****************************************************
# Variables to control Makefile operation

#CC = g++
#CFLAGS = -Wall -g

# ****************************************************
# Targets needed to bring the executable up to date

#main: main.o Point.o Square.o
    #$(CC) $(CFLAGS) -o main main.o Point.o Square.o

# The main.o target can be written more simply

#main.o: main.cpp Point.h Square.h
    #$(CC) $(CFLAGS) -c main.cpp

#Point.o: Point.h

#Square.o: Square.h Point.h