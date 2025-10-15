/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   EventLoop.cpp                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cereais <cereais@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/25 19:35:11 by joseoliv          #+#    #+#             */
/*   Updated: 2025/10/15 14:58:13 by cereais          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/core/EventLoop.hpp"
#include "../../include/core/Server.hpp"
#include "../../include/core/Connection.hpp"

EventLoop::EventLoop() {}

EventLoop::~EventLoop()
{

	for (size_t i = 0; i < _pollEntries.size(); ++i)
	{
		if (_pollEntries[i].conn)
			delete _pollEntries[i].conn;
		close(_pollEntries[i].pfd.fd);
	}
}

void EventLoop::addListeningSocket(const Socket *socket, Server &server)
{

	struct pollfd pfd;
	pfd.fd = socket->getFd();
	pfd.events = POLLIN;
	pfd.revents = 0;

	PollEntry entry;
	entry.pfd = pfd;
	entry.conn = NULL;
	entry.server = &server;
	entry.socketAddr = socket->getAddr();

	_pollEntries.push_back(entry);
}

void EventLoop::run()
{

	while (true)
	{

		if (!_pollEntries.empty())
		{
			int errorCode = poll(&_pollEntries[0].pfd, _pollEntries.size(), 5000);
			if (errorCode < 0)
			{
				perror("poll");
				break;
			}
		}

		// collect newly accepted clients here to avoid invalidating _pollEntries while iterating
		std::vector<PollEntry> newClients;
		for (size_t i = 0; i < _pollEntries.size(); ++i)
		{
			PollEntry &entry = _pollEntries[i];

			// ready to read
			if (entry.pfd.revents & POLLIN)
			{
				std::cout << "pollin" << std::endl;
				if (entry.conn == NULL)
				{
					// accept but store the new client in newClients
					socklen_t addrLen = sizeof(entry.socketAddr);
					int clientFd = accept(entry.pfd.fd, (sockaddr *)&entry.socketAddr, &addrLen);
					if (clientFd < 0)
					{
						std::cerr << "Failed to accept connection\n";
						continue;
					}
					Connection *conn = new Connection(clientFd, *entry.server);

					struct pollfd pfd;
					pfd.fd = clientFd;
					pfd.events = POLLIN;
					pfd.revents = 0;

					PollEntry clientEntry;
					clientEntry.pfd = pfd;
					clientEntry.conn = conn;
					clientEntry.server = entry.server;
					clientEntry.socketAddr = entry.socketAddr;

					newClients.push_back(clientEntry);
					std::cout << "New client accepted: fd " << clientFd << std::endl;
				}
				else
				{
					if (!entry.conn->readRequest())
						closeConnection(entry);
					else if (entry.conn->isRequestComplete())
					{
						std::cout << entry.conn->getReadBuffer() << std::endl;
						entry.pfd.events = POLLIN;
					}
				}
			}
			// ready to write
			if (entry.pfd.revents & POLLOUT)
			{
				std::cout << "POLLOUT" << std::endl;
				if (entry.conn && !entry.conn->writeResponse())
				{
					closeConnection(entry);
				}
			}
			entry.pfd.revents = 0;
		}

		// append newly accepted clients after iterating to avoid invalidation
		if (!newClients.empty())
		{
			_pollEntries.insert(_pollEntries.end(), newClients.begin(), newClients.end());
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
void EventLoop::handleNewConnection(PollEntry &entry)
{

	socklen_t addrLen = sizeof(entry.socketAddr);

	int clientFd = accept(entry.pfd.fd, (sockaddr *)&entry.socketAddr, &addrLen);
	if (clientFd < 0)
	{
		std::cerr << "Failed to accept connection\n";
		return;
	}

	Connection *conn = new Connection(clientFd, *entry.server);

	struct pollfd pfd;
	pfd.fd = clientFd;
	pfd.events = POLLIN;

	PollEntry clientEntry;
	clientEntry.pfd = pfd;
	clientEntry.conn = conn;
	clientEntry.server = entry.server;

	_pollEntries.push_back(clientEntry);
	std::cout << "New client accepted: fd " << clientFd << std::endl;
}

void EventLoop::closeConnection(PollEntry &entry)
{

	close(entry.pfd.fd);
	delete entry.conn;
	entry.conn = NULL;
	std::cout << "Connection closed: fd " << entry.pfd.fd << std::endl;
}
