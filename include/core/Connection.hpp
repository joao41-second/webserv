/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Connection.hpp                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: joseoliv <joseoliv@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/13 18:43:35 by cereais           #+#    #+#             */
/*   Updated: 2025/10/03 12:40:32 by joseoliv         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once

#include <string>
#include <vector>
#include <sys/socket.h>
#include <../http/HttpRequest.hpp>
#include <../http/HttpResponse.hpp>
#include <../core/Server.hpp>

//Connection represents each client connected to the server

class Connection {
	
public:
	Connection(int fd, Server &server);
	~Connection();
	Connection(const Connection &copy);

	bool	readRequest();				// read data from socket
	bool	writeResponse(); 			// sends data from socket
	bool	processRequest();			// check if CGI, static || error

private:
	int				_fd;
	Server&			_server;
	std::string		_readBuffer;
	std::string		_writeBuffer;
};
