/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Connection.cpp                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: joseoliv <joseoliv@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/02 20:10:16 by cereais           #+#    #+#             */
/*   Updated: 2025/10/03 15:14:45 by joseoliv         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/core/Connection.hpp"

Connection::Connection(int fd, Server &server) : _fd(fd), _server(server) {
	_readBuffer = "";
	_writeBuffer = "";
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
	
	char	buffer[1024];
    ssize_t	bytesRead;
	
	while ((bytesRead = read(_fd, buffer, sizeof(buffer))) > 0) {
		_readBuffer.append(buffer, bytesRead);
	}

    if (bytesRead > 0) {
        
        return (true);
    } else if (bytesRead == 0)
        return false;
    else {
        perror("read");
        return false;
    }
}

bool Connection::readRequest() {
    char buffer[1024];
    ssize_t bytesRead;

    while ((bytesRead = read(_fd, buffer, sizeof(buffer))) > 0) {
        _readBuffer.append(buffer, bytesRead);
    }
    if (bytesRead == 0)
        return false;
    if (bytesRead < 0) {
        perror("read");
        return false;
    }
    return true;
}



bool	Connection::writeResponse() {

}

bool	Connection::processRequest() {
	
}