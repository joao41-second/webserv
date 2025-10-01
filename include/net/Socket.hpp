/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Socket.hpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: joseoliv <joseoliv@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/15 16:58:14 by joseoliv          #+#    #+#             */
/*   Updated: 2025/10/01 17:10:23 by joseoliv         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once

#include <sys/socket.h>
#include <netinet/in.h>
#include <unistd.h>

class Socket {
	
public:
	Socket();
	~Socket();
	Socket(const Socket& copy);
	Socket& operator=(const Socket& src);

	void	close();

	int					getFd() const;
	struct sockaddr_in	getAddr() const;

private:
	struct sockaddr_in	_addr;
	int					_fd;
};
