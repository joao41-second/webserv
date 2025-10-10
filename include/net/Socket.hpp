#pragma once

#include <sys/socket.h>
#include <netinet/in.h>
#include <unistd.h>

#ifndef SOCKET_H
#define SOCKET_H

#include <sys/socket.h>
#include <netinet/in.h>
#include <unistd.h>

class Socket
{
public:
	//Socket();
	Socket(uint16_t port);
	//Socket(const Socket& orig);
	//Socket& operator=(const Socket& orig);
	virtual ~Socket();

	int							getFd() const;
	struct sockaddr_in const	&getAddr() const; // TODO Should the return be const sockaddr_in?
	uint16_t					getAddrPort() const;

private:
	struct sockaddr_in	_addr;
	int					_fd;
};

#endif