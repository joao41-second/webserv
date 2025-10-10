/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Connection.hpp                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cereais <cereais@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/13 18:43:35 by cereais           #+#    #+#             */
/*   Updated: 2025/10/10 18:08:13 by cereais          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once

#include <../http/HttpRequest.hpp>
#include <../http/HttpResponse.hpp>
#include <../core/Server.hpp>

class Sever;

class Connection {

public:
	Connection(int fd, Server &server);
	~Connection();
	Connection(const Connection &copy);

	bool	readRequest();				// read data from socket
	bool	writeResponse(); 			// sends data to socket
	bool	isRequestComplete();		// check if _readbuffer contains a complete HTTP request

	std::string		getReadBuffer() const;
	void			setWriteBuffer(HttpResponse response);
private:
	int				_fd;
	Server&			_server;
	std::string		_readBuffer;
	std::string		_writeBuffer;
};
