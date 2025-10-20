/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Server.hpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cereais <cereais@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/13 18:43:46 by cereais           #+#    #+#             */
/*   Updated: 2025/10/18 17:16:22 by cereais          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once

#include <string>
#include <net/Socket.hpp>
#include <config/ServerConfig.hpp>

class Server {

public:
    Server(const std::vector<ServerConfig> &configs,
	    const std::vector<Socket*> &sockets);
	~Server();

	void launch(); // invoca o loop do eventLoop

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