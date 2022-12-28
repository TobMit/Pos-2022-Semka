#include <stdlib.h>
#include <iostream>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <netdb.h>
#include <unistd.h>

using namespace std;

class Socket {
protected:
    int port;
    struct hosten *serverAdd;
    int sock;
    int sockClient;
    struct sockaddr_in;
public:
    Socket(int pPort);
    bool createSocket();
    virtual void setServerParameters();
    virtual void setServerParameters(char *ipAddress);

    int * getSock() {
      return &sock;
    };
    void closeSocket();
    ~Socket();
private:
    void closeSocket(int pSocket);
};
