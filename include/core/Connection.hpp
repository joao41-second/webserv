/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Connection.hpp                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: joseoliv <joseoliv@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/13 18:43:35 by cereais           #+#    #+#             */
/*   Updated: 2025/09/25 23:31:42 by joseoliv         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once

#include <string>
#include <vector>
#include <sys/socket.h>
#include <../http/HttpRequest.hpp>
#include <../http/HttpResponse.hpp>

//Connection represents each client connected to the server

class ServerConfig;

class Connection {
	
public:
	Connection(int fd, Server &server);
	~Connection();

	void	handleRead();               // le dados do socket
	void	handleWrite(); 				// envia dados do socket
	void	processRequest();           // decide CGI, estático || erros

private:
	int				_fd;
	Server&			_server;
	HttpRequest		_request;
	HttpResponse	_response;
	std::string		_readBuffer;
	std::string		_writeBuffer;
};
