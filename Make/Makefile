CC = g++

TARGET = GameServer
INPUT_TARGET = ../src/Game/MainServer.cpp ../src/SFML-client_server/Sockets/Sockets.cpp ../src/SFML-client_server/Sockets/Sockets.h ../src/SFML-client_server/Sockets/MultiServer/MultiServer.h ../src/SFML-client_server/Sockets/MultiServer/MultiServer.cpp ../src/Constants/Constants.h ../src/Constants/GameData.h ../src/Game/Server/ServerLogic.cpp ../src/Game/Server/ServerLogic.h ../src/Game/Server/ServerGame.cpp ../src/Game/Server/ServerGame.h
OUTPUT = $(TARGET) MainServer.o Sockets.o MultiServer.o ServerLogic.o ServerGame.o
TARGET2 = GameClient
INPUT_TARGET2 = ../src/Game/MainClient.cpp ../src/Game/Graphics/Ball/Ball.cpp ../src/Game/Graphics/Ball/Ball.h ../src/Game/Graphics/Paddle/Paddle.cpp ../src/Game/Graphics/Paddle/Paddle.h ../src/Constants/GameData.h ../src/Game/Client/ClientLogic.cpp ../src/Game/Client/ClientLogic.h ../src/Game/Client/ClientGame.cpp ../src/Game/Client/ClientGame.h ../src/Game/Graphics/Resources/Resources.h ../src/Game/Graphics/Resources/Sounds/Sounds.cpp ../src/Game/Graphics/Resources/Sounds/Sounds.h ../src/Game/Graphics/Resources/Labels/Labels.cpp ../src/Game/Graphics/Resources/Labels/Labels.h
OUTPUT2 = $(TARGET2) MainClient.o Ball.o Paddle.o ClientLogic.o ClientGame.o Sounds.o Labels.o
all: $(TARGET) $(TARGET2)

clean:
	rm $(OUTPUT)
	rm $(OUTPUT2)

.PHONY: all clean

$(TARGET): $(INPUT_TARGET)
	$(CC) -c ../src/Game/MainServer.cpp ../src/SFML-client_server/Sockets/Sockets.cpp ../src/SFML-client_server/Sockets/MultiServer/MultiServer.cpp ../src/Game/Server/ServerLogic.cpp ../src/Game/Server/ServerGame.cpp -lpthread -lsfml-network -lsfml-graphics -lsfml-system
	$(CC) -o $(OUTPUT) -lpthread -lsfml-network -lsfml-graphics -lsfml-system

$(TARGET2): $(INPUT_TARGET2)
	$(CC) -c ../src/Game/MainClient.cpp ../src/Game/Graphics/Ball/Ball.cpp ../src/Game/Graphics/Paddle/Paddle.cpp   ../src/Game/Client/ClientLogic.cpp . ../src/Game/Client/ClientGame.cpp  ../src/Game/Graphics/Resources/Sounds/Sounds.cpp  ../src/Game/Graphics/Resources/Labels/Labels.cpp  -lsfml-system -lsfml-window -lsfml-graphics -lsfml-audio -lsfml-network
	$(CC) -o $(OUTPUT2) -lsfml-system -lsfml-window -lsfml-graphics -lsfml-audio -lsfml-network
