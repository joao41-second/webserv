/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   EventLoop.hpp                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: joseoliv <joseoliv@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/13 18:44:16 by cereais           #+#    #+#             */
/*   Updated: 2025/09/25 19:51:53 by joseoliv         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once

#include <map>
#include <vector>

class Server;
class Connection;

class EventLoop {

public:
    EventLoop();
    ~EventLoop();

    void addListeningSocket(const Socket& socket, Server& server);
    void run();

private:
    // listening sockets: fd -> Server
    std::map<int, Server*> _listeningSockets;

    // active client connections: fd -> Connection
    std::map<int, Connection*> _connections;

    fd_set _readFds;
    fd_set _writeFds;
    int _maxFd;

    void	handleNewConnection(int fd, Server& server);
    void	handleClientRead(int fd);
    void	handleClientWrite(int fd);
    void	closeConnection(int fd);
};


/*

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