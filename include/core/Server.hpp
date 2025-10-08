/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Server.hpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: joseoliv <joseoliv@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/13 18:43:46 by cereais           #+#    #+#             */
/*   Updated: 2025/09/23 15:27:37 by jperpct          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once

#include <config/debug.hpp>
#include <vector>
#include <sys/socket.h>
#include <fstream>
#include <algorithm>

class Socket;
class ServerConfig;

class Server {

public:
    Server(const std::vector<ServerConfig>& configs,
           const std::vector<Socket>& sockets);
	~Server();

    void run(); //invoca o loop do eventLoop
    //void?   closeConnection();

private:
    std::vector<ServerConfig> _configs;
    std::vector<Socket> _listeningSockets;
};

/*
Server guarda:

std::vector<Socket> listeningSockets (cada um tem um fd).

std::map<int, Connection*> activeConnections (mapa fd → Connection*).

EventLoop loop (a abstracção de select/poll).

std::vector<ServerConfig> configs.

EventLoop encapsula select() (ou poll/epoll) e provê:

addFd(fd, mode) / removeFd(fd).

pollEvents() → devolve lista de eventos (fd + tipo: readable/writable).
*/

/*
when CGI is the way, create this environment variables
EQUEST_METHOD, QUERY_STRING, CONTENT_LENGTH, CONTENT_TYPE,
SCRIPT_NAME, PATH_INFO, SERVER_NAME, SERVER_PORT
*/
