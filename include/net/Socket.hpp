#pragma once

#ifndef SOCKET_H
#define SOCKET_H

#include <sys/socket.h>
#include <netinet/in.h>
#include <unistd.h>

class Socket
{
public:
	Socket();
	Socket(int fd);
	Socket(const Socket& copy);
	Socket& operator=(const Socket& src);
	virtual ~Socket();

	//void	close();

	int							getFd() const;
	struct sockaddr_in const	&getAddr() const; // TODO Should the return be const sockaddr_in?

private:
	struct sockaddr_in	_addr;
	int					_fd;
};

#endif