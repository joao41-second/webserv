/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Connection.cpp                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cereais <cereais@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/02 20:10:16 by cereais           #+#    #+#             */
/*   Updated: 2025/10/02 20:27:04 by cereais          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/core/Connection.hpp"

Connection::Connection(int fd, Server &server) : _fd(fd), _server(server) {
}

Connection::~Connection() {

	//probably deletes server?
}

Connection::Connection(const Connection &copy) : 
	_server(copy._server), _response(copy._response),
	_request(copy._request) {
	
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