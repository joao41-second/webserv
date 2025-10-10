/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Server.cpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cereais <cereais@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/13 18:30:29 by cereais           #+#    #+#             */
/*   Updated: 2025/10/10 18:04:08 by cereais          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/core/Server.hpp"
#include "../../include/core/EventLoop.hpp"

Server::Server(const std::vector<ServerConfig>& configs,
			   const std::vector<Socket>& sockets)
	: _configs(configs), _listeningSockets(sockets)
{
	std::cout << "Server initialized with " 
			  << _configs.size() << " configs and " 
			  << _listeningSockets.size() << " sockets." << std::endl;
}

Server::~Server() {

	/* for (size_t i = 0; i < _listeningSockets.size(); i++)
		_listeningSockets[i].close(); */

	std::cout << "Server stopped." << std::endl;
}

void	Server::launch() {

	EventLoop	loop;

	for (size_t i = 0; i < _listeningSockets.size(); i++)
		loop.addListeningSocket(_listeningSockets[i], *this);

	std::cout << "Server running..." << std::endl;
	loop.run();
}

std::vector<ServerConfig>	Server::getConfig() {
	
	return (_configs);
}
