#include "Sockets.h"

void Sockets::consoleSendData(std::mutex *mut, bool *end) {
    char buffer[constants::BUFF_SIZE + 1];
    buffer[constants::BUFF_SIZE] = '\0';

    fcntl(STDIN_FILENO, F_SETFL, fcntl(STDIN_FILENO, F_GETFL, 0) | O_NONBLOCK);
    fd_set inputs;
    FD_ZERO(&inputs);
    struct timeval tv;
    tv.tv_usec = 0;
    while (!isEnd(mut, end)) {
        int position = -1;
        tv.tv_sec = 1;
        FD_SET(STDIN_FILENO, &inputs);
        select(STDIN_FILENO + 1, &inputs, NULL, NULL, &tv);

        if (FD_ISSET(STDIN_FILENO, &inputs)) {
            char *testStart = buffer;

            while (fgets(testStart, constants::BUFF_SIZE-1, stdin)!= nullptr) {
                std::string inputFromConsole = testStart;
                position = inputFromConsole.find(":end",0);
                {
                    std::unique_lock<std::mutex> lock(*mut);
                    sf::Packet packet;
                    packet << inputFromConsole;
                    if (!socketSend(&packet)) {
                        setEnd(mut, end);
                    }
                }
                if (position != -1) {
                    setEnd(mut, end);
                }
            }
        }
    }
    fcntl(STDIN_FILENO, F_SETFL, fcntl(STDIN_FILENO, F_GETFL, 0) & ~O_NONBLOCK);
}

void Sockets::consoleToBuffer(std::mutex *mut, bool *end, std::vector<std::string> &buffer,
                              std::condition_variable *writeToBuff) {
    char inputBuff[constants::BUFF_SIZE + 1];
    inputBuff[constants::BUFF_SIZE] = '\0';

    fcntl(STDIN_FILENO, F_SETFL, fcntl(STDIN_FILENO, F_GETFL, 0) | O_NONBLOCK);
    fd_set inputs;
    FD_ZERO(&inputs);
    struct timeval tv;
    tv.tv_usec = 0;
    while (!isEnd(mut, end)) {
        tv.tv_sec = 1;
        FD_SET(STDIN_FILENO, &inputs);
        select(STDIN_FILENO + 1, &inputs, NULL, NULL, &tv);

        if (FD_ISSET(STDIN_FILENO, &inputs)) {
            std::unique_lock<std::mutex> lock(*mut);
            while (!buffer.empty()) {
                writeToBuff->wait(lock);
            }
            char *testStart = inputBuff;
            while (fgets(testStart, constants::BUFF_SIZE-1, stdin)!= nullptr) {
                buffer.push_back(testStart);
            }
        }
    }
    fcntl(STDIN_FILENO, F_SETFL, fcntl(STDIN_FILENO, F_GETFL, 0) & ~O_NONBLOCK);
}

bool Sockets::isEnd(std::mutex *mut, bool *pEnd) {
    bool end;
    {
        std::unique_lock<std::mutex> lock(*mut);
        end = *pEnd;
    }
    return end;
}

void Sockets::setEnd(std::mutex *mut, bool *pEnd) {
    std::unique_lock<std::mutex> lock(*mut);
    *pEnd = true;
}
