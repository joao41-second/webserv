/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Server.hpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cereais <cereais@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/13 18:43:46 by cereais           #+#    #+#             */
/*   Updated: 2025/10/14 14:36:57 by cereais          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once

#include <string>
#include "../include/net/Socket.hpp"
#include "../include/config/ServerConfig.hpp"

class Server {

public:
    Server(const std::vector<ServerConfig> &configs,
	    const std::vector<Socket*> &sockets);
	~Server();

	void launch(); // invoca o loop do eventLoop
	void closeConnection();

	std::vector<ServerConfig> getConfig();

private:
	std::vector<ServerConfig> _configs;
	std::vector<Socket*> _listeningSockets;
};

/*
Server guarda:

std::map<int, Connection*> activeConnections (mapa fd → Connection*).

EventLoop loop (a abstracção de poll).


EventLoop encapsula poll e provê:

addFd(fd, mode) / removeFd(fd).

pollEvents() → devolve lista de eventos (fd + tipo: readable/writable).
*/