/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Connection.cpp                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: joseoliv <joseoliv@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/02 20:10:16 by cereais           #+#    #+#             */
/*   Updated: 2025/10/07 14:19:08 by joseoliv         ###   ########.fr       */
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
		perror("read");
		return false;
	}
	return (true);
}

bool	Connection::writeResponse() {

}

bool	Connection::isRequestComplete() {

	size_t headerEnd = _readBuffer.find("\r\n\r\n");
	if (headerEnd == std::string::npos)
		return (false);

	size_t contentLengthPos = _readBuffer.find("Content-Length:");
	if (contentLengthPos != std::string::npos) {

		size_t valueStart = _readBuffer.find(":", contentLengthPos) + 1;
		size_t valueEnd = _readBuffer.find("\r\n", valueStart);
		std::string lengthStr = _readBuffer.substr(valueStart, valueEnd - valueStart);
		int contentLength = atoi(lengthStr.c_str());

		size_t bodyStart = headerEnd + 4;
		size_t bodyLength = _readBuffer.size() - bodyStart;
		if (bodyLength < (size_t)contentLength)
			return (false); // Body not fully received
	}
	return (true);
}

std::string	Connection::getReadBuffer() const {
	
	return (_readBuffer);
}
