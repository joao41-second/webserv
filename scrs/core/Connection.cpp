#include <vector>
#include <map>
#include <poll.h>
#include "Socket.hpp"
#include "Server.hpp"

class Connection;

class EventLoop {
public:
    EventLoop();
    ~EventLoop();

    void addListeningSocket(const Socket& socket, Server& server);
    void loop(); // main event loop

private:
    struct PollEntry {
        struct pollfd pfd;
        Server* server;        // which server owns this socket
        Connection* conn;      // NULL if it's a listening socket
    };

    std::vector<PollEntry> _pollEntries;

    void handleNewConnection(PollEntry& entry);
    void closeConnection(PollEntry& entry);
};



EventLoop::EventLoop() {}

EventLoop::~EventLoop() {
    for (size_t i = 0; i < _pollEntries.size(); ++i) {
        if (_pollEntries[i].conn) {
            delete _pollEntries[i].conn;
        }
        close(_pollEntries[i].pfd.fd);
    }
}

void EventLoop::loop() {
    while (true) {
        int ret = poll(&_pollEntries[0].pfd, _pollEntries.size(), -1);
        if (ret < 0) {
            perror("poll");
            break;
        }

        for (size_t i = 0; i < _pollEntries.size(); ++i) {
            PollEntry& entry = _pollEntries[i];

            if (entry.pfd.revents & POLLIN) {
                if (entry.conn == NULL) {
                    // listening socket
                    handleNewConnection(entry);
                } else {
                    // client socket: read
                    if (!entry.conn->readRequest()) {
                        closeConnection(entry);
                    }
                }
            }

            if (entry.pfd.revents & POLLOUT) {
                if (entry.conn && !entry.conn->writeResponse()) {
                    closeConnection(entry);
                }
            }

            entry.pfd.revents = 0; // reset for next poll
        }
    }
}
