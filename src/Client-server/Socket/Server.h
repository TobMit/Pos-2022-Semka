
#include "Socket.h"

class Server : public Socket{
public:
    void setServerParameters() override;
    bool bind();

};