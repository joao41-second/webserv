/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   EventLoop.cpp                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: joseoliv <joseoliv@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/25 19:35:11 by joseoliv          #+#    #+#             */
/*   Updated: 2025/10/01 16:39:35 by joseoliv         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/core/EventLoop.hpp"
#include "../include/core/Server.hpp"
#include "../include/core/Connection.hpp"
#include "../include/net/Socket.hpp"

EventLoop::EventLoop() {
}

EventLoop::~EventLoop() {

}

void	EventLoop::addListeningSocket(const Socket& socket, Server& server) {
	
	struct pollfd pfd;
	pfd.fd = socket.getFd();
	pfd.events = POLLIN;
	pfd.revents = POLLOUT; //not sure

	PollEntry entry;
	entry.pfd = pfd;
	entry.conn = NULL;
	entry.server = &server;

	_pollEntries.push_back(entry);
}

void	EventLoop::run() {

	while (true) {
		
		if (!_pollEntries.empty()) {
    		int errorCode = poll(&_pollEntries[0].pfd, _pollEntries.size(), -1);
			if (errorCode < 0) {
            	perror("poll");
            	break ;
        	}
		}
	}
}

/*
accept() :
The first argument is the server’s socket, 
the second is a pointer to a socket address 
and the third is the length of the address object passed prior. 
Accept() returns the new peer socket 
and writes the socket address information 
into the socket address pointer passed in as the second argument.
*/
void EventLoop::handleNewConnection(PollEntry& entry) {

	int clientFd = accept(entry.pfd.fd, NULL, NULL);
	if (clientFd < 0) {
		std::cerr << "Failed to accept connection\n";
		return ;
	}

	Connection* conn = new Connection(clientFd, *entry.server);
	
	struct pollfd	pfd;
	pfd.fd = clientFd;
	pfd.events = 0;

	PollEntry clientEntry;
    clientEntry.pfd = pfd;
    clientEntry.conn = conn;
    clientEntry.server = entry.server;

	_pollEntries.push_back(clientEntry);
	std::cout << "New client accepted: fd " << clientFd << std::endl;
}

void EventLoop::closeConnection(PollEntry& entry) {

    close(entry.pfd.fd);
    delete entry.conn;
    entry.conn = NULL;
    std::cout << "Connection closed: fd " << entry.pfd.fd << std::endl;
}
