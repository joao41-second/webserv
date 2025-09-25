/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   EventLoop.cpp                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: joseoliv <joseoliv@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/25 19:35:11 by joseoliv          #+#    #+#             */
/*   Updated: 2025/09/25 21:11:52 by joseoliv         ###   ########.fr       */
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
	
}

void	EventLoop::run() {

	while (true) {
		
		
	}
}

void EventLoop::handleNewConnection(int fd, Server& server) {

	int clientFd = accept(fd, NULL, NULL);
	if (clientFd < 0) {
		std::cerr << "Failed to accept connection\n";
		return;
	}

	if (clientFd > _maxFd) 
		_maxFd = clientFd;

    _connections[clientFd] = new Connection(clientFd, server.getConfig());
    std::cout << "New connection accepted: fd " << clientFd << std::endl;
}