/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   EventLoop.hpp                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: joseoliv <joseoliv@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/13 18:44:16 by cereais           #+#    #+#             */
/*   Updated: 2025/09/26 00:07:56 by joseoliv         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once

#include <map>
#include <vector>
#include <poll.h>
#include <unistd.h>

class Server;
class Connection;

class EventLoop {

public:
	EventLoop();
	~EventLoop();

	void addListeningSocket(const Socket& socket, Server& server);
	void run();

private:
	struct PollEntry {

		struct pollfd	pfd;
		Server*			server;
		Connection*		conn;
	};

	std::vector<PollEntry>	_pollEntries;

	void	handleNewConnection(PollEntry& entry);
	void	closeConnection(PollEntry& entry);
};


/*
pollfd struct:
int    fd       The following descriptor being polled. 
short  events   The input event flags (see below). 
short  revents  The output event flags (see below).


LOOP PRINCIPAL

Recebe uma lista de listening sockets (fd)

Cria estruturas internas para acompanhar:

fds de leitura

fds de escrita

fds de erro (exception)



Monitora fds usando poll().

Quando um listening socket fica pronto chama Server::acceptConnection() -> cria uma nova Connection.

Quando um client socket fica pronto para leitura chama Connection::handleRead() -> acumula dados e parseia request.

Quando um client socket fica pronto para escrita chama Connection::handleWrite()-> envia resposta parcial ou completa.

Repete tudo até o servidor ser encerrado.
*/