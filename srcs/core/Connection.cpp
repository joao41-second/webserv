/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Connection.cpp                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cereais <cereais@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/02 20:10:16 by cereais           #+#    #+#             */
/*   Updated: 2025/10/19 18:53:36 by cereais          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <core/Connection.hpp>
#include <core/Server.hpp>
#include <config/color.hpp>

Connection::Connection(int fd) : _fd(fd) {
	_writeBuffer = "";
}

Connection::~Connection() {
}

Connection::Connection(const Connection &copy) {
	
	this->_fd = copy._fd;
	this->_readBuffer = copy._readBuffer;
	this->_writeBuffer = copy._writeBuffer;
}

void Connection::set_readBuffer()
{
	_readBuffer = "";
}

bool	Connection::readRequest() {

	char	buffer[1024];
	ssize_t	bytesRead;

	_readBuffer = "";
	for(int i = 0 ; i < 1024 ;i++ )
	{
		buffer[i] = '0';
	}
	while ((bytesRead = read(_fd, buffer, sizeof(buffer))) > 0) {
		_readBuffer.append(buffer, bytesRead);
	}

	if (bytesRead < 0) { 
		if (errno == EAGAIN || errno == EWOULDBLOCK) 
			return true;
		perror("read");
    	return (false);
	}

	if (bytesRead == 0)
    	return (false); //client closed connection
	return (true);
}

bool	Connection::writeResponse() {
	
	ssize_t	bytesWritten;

	if (_writeBuffer.empty())
		return (true);
	bytesWritten = write(_fd, _writeBuffer.c_str(), _writeBuffer.size()); 
	if (bytesWritten < 0) {
		perror("write");
		return (false);
	} else if (bytesWritten == 0)
		return (false);

	_writeBuffer.erase(0, static_cast<size_t>(bytesWritten));
	return (_writeBuffer.empty());
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

std::string	Connection::getWriteBuffer() const {
	
	return (_writeBuffer);
}

void	Connection::setWriteBuffer(std::string buffer) {

	_writeBuffer = buffer;
}
