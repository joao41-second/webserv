/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   EventLoop.cpp                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cereais <cereais@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/25 19:35:11 by joseoliv          #+#    #+#             */
/*   Updated: 2025/10/15 20:03:12 by cereais          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/core/EventLoop.hpp"
#include "../../include/core/Server.hpp"
#include "../../include/core/Connection.hpp"

EventLoop::EventLoop() {
	_pollEntries.reserve(1024);
}

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
			for (size_t i = 0; i < _pollEntries.size(); ++i) {
				sleep(1);
    			std::cout << "fd " << _pollEntries[i].pfd.fd 
              << " events=" << _pollEntries[i].pfd.events 
              << " revents=" << _pollEntries[i].pfd.revents << std::endl;
			}
		}
		for (size_t i = 0; i < _pollEntries.size(); ++i)
		{
			PollEntry &entry = _pollEntries[i];

			if (entry.pfd.revents & (POLLHUP | POLLERR | POLLNVAL)) 
			{
				std::cout << "Strange error, wow" << std::endl;
    			closeConnection(entry);
    			continue;
			}

			// ready to read
			if (entry.pfd.revents & POLLIN)
			{
				std::cout << "pollin" << std::endl;
				if (entry.conn == NULL)
				{
					handleNewConnection(entry);
					break ;
				}
				else
				{
					std::cout << "else!!!" << std::endl;
					if (!entry.conn->readRequest())
						closeConnection(entry);
					else if (entry.conn->isRequestComplete())
					{
						std::cout << entry.conn->getReadBuffer() << std::endl;
						entry.pfd.events = POLLIN;
					}
				}
			}
			/* sleep(3);
			std::cout << entry.pfd.events << std::endl; */
			if (entry.pfd.revents & POLLOUT)
			{
				std::cout << "POLLOUT" << std::endl;
				if (entry.conn && !entry.conn->writeResponse())
					closeConnection(entry);
			}
			entry.pfd.revents = 0;
		}
	}
}

void EventLoop::handleNewConnection(const PollEntry &entry)
{

	//socklen_t addrLen = sizeof(entry.socketAddr);

	int clientFd = accept(entry.pfd.fd, NULL, NULL);
	std::cout << "Accepted client fd: " << clientFd 
          << ", events=" << entry.pfd.events << std::endl;

	if (clientFd < 0)
	{
		std::cerr << "Failed to accept connection\n";
		return;
	}

	int flags = fcntl(clientFd, F_GETFL, 0);
	fcntl(clientFd, F_SETFL, flags | O_NONBLOCK);

	Connection *conn = new Connection(clientFd, *entry.server);

	struct pollfd pfd;
	pfd.fd = clientFd;
	pfd.events = POLLIN;
	pfd.revents = 0;

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
