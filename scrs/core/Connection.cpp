/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Connection.cpp                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: joseoliv <joseoliv@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/02 20:10:16 by cereais           #+#    #+#             */
/*   Updated: 2025/10/03 12:45:48 by joseoliv         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/core/Connection.hpp"

Connection::Connection(int fd, Server &server) : _fd(fd), _server(server) {
}

Connection::~Connection() {

	//probably deletes server?
}

Connection::Connection(const Connection &copy) : 
	_server(copy._server) {
	
	this->_fd = copy._fd;
	this->_readBuffer = copy._readBuffer;
	this->_writeBuffer = copy._writeBuffer;
}

bool	Connection::readRequest() {
	
}

bool	Connection::writeResponse() {

}

bool	Connection::processRequest() {
	
}