/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   EventLoop.cpp                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cereais <cereais@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/25 19:35:11 by joseoliv          #+#    #+#             */
/*   Updated: 2025/10/10 17:45:05 by cereais          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/core/EventLoop.hpp"
#include "../../include/core/Server.hpp"
#include "../../include/core/Connection.hpp"

EventLoop::EventLoop() {}

EventLoop::~EventLoop() {

	for (size_t i = 0; i < _pollEntries.size(); ++i) {
		if (_pollEntries[0].conn)
			delete _pollEntries[0].conn;
		close(_pollEntries[i].pfd.fd);
	}
}

void	EventLoop::addListeningSocket(const Socket& socket, Server& server) {

	struct pollfd	pfd;
	pfd.fd = socket.getFd();
	pfd.events = POLLIN;
	pfd.revents = 0;

	PollEntry	entry;
	entry.pfd = pfd;
	entry.conn = NULL;
	entry.server = &server;
	entry.socketAddr = socket.getAddr();

	_pollEntries.push_back(entry);
}

void	EventLoop::run() {

	while (true) {

		if (!_pollEntries.empty()) {
			int errorCode = poll(&_pollEntries[0].pfd, _pollEntries.size(), 5000);
			if (errorCode < 0) {
				perror("poll");
				break ;
			}
		}
		for (size_t i = 0; i < _pollEntries.size(); ++i) {
			PollEntry& entry = _pollEntries[i];

			//ready to read
			if (entry.pfd.revents & POLLIN) {
				if (entry.conn == NULL)
					handleNewConnection(entry);
				else {
					if (!entry.conn->readRequest())
						closeConnection(entry);
					else if (entry.conn->isRequestComplete()) {
						//send to joao entry.conn->getReadBuffer();
						entry.pfd.events = POLLIN;
					}
				}
			}

			//ready to write
			if (entry.pfd.revents & POLLOUT) {

				if (entry.conn && !entry.conn->writeResponse()) {
					closeConnection(entry);
				}
			}
			entry.pfd.revents = 0;
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
void	EventLoop::handleNewConnection(PollEntry& entry) {

	socklen_t addrLen = sizeof(entry.socketAddr);

	int clientFd = accept(entry.pfd.fd, (sockaddr *)&entry.socketAddr, &addrLen);
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

void	EventLoop::closeConnection(PollEntry& entry) {

	close(entry.pfd.fd);
	delete entry.conn;
	entry.conn = NULL;
	std::cout << "Connection closed: fd " << entry.pfd.fd << std::endl;
}
