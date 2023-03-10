#pragma once
#include <SFML/Network.hpp>
#include <thread>
#include <mutex>
#include <condition_variable>

#include <sys/select.h>
#include <fcntl.h>
#include <unistd.h>

#include "../Constants/Constants.h"

/**
 * Wrapper class for SFML networking
 */
class Sockets {
public:
    Sockets() = default;
    ~Sockets()= default;
    /**
     * Function ideal for threads! Exit is via ":end"
     * @param mut mutex for thread
     * @param end end of thread
     */
    void consoleSendData(std::mutex *mut, bool *end);

    void consoleToBuffer(std::mutex *mut, bool *end, std::vector<std::string> &buffer,
                         std::condition_variable *writeToBuff);

    bool isEnd(std::mutex *mut, bool *pEnd);
    void setEnd(std::mutex *mut, bool *pEnd);
    /**
     * Send packet via socket
     * @param pPacket sending packet
     * @return if was correct sending
     */
    virtual bool socketSend(sf::Packet *pPacket) = 0;
    /**
     * Send packet via socket
     * @param pPacket packet will be stored here
     * @return if was correct recieving
     */
    virtual bool socketReceive(sf::Packet *pPacket) = 0;
    /**
     * Connect socket to the server
     * @param pIpAddress addres for server url or ip
     * @param pPort port for conection
     * @return if was connection done
     */
    virtual bool socketConnect(std::string pIpAddress, int pPort) = 0;
    /**
     * Disconnect from server
     */
    virtual void socketDisconnect() = 0;
protected:

};
