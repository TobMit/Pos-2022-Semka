#include "Socket.h"

Socket::Socket(int pPort) {
    port = pPort;
}

bool Socket::createSocket() {
    sock = socket(AF_INET, SOCK_STREAM, 0);
    return sock < 0 ? false : true;
}

void Socket::closeSocket() {
    closeSocket(sockClient);
}

Socket::~Socket() {

}

void Socket::closeSocket(int pSocket) {
    close(pSocket);
}
