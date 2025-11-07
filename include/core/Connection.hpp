/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Connection.hpp                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cereais <cereais@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/13 18:43:35 by cereais           #+#    #+#             */
/*   Updated: 2025/10/19 18:54:46 by cereais          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once

#include <string>

class Connection {

public:
	Connection(int fd);
	~Connection();
	Connection(const Connection &copy);

	bool	readRequest();				// read data from socket
	bool	writeResponse(); 			// sends data to socket
	bool	isRequestComplete();		// check if _readbuffer contains a complete HTTP request

	std::string		getReadBuffer() const;
	std::string		getWriteBuffer() const;
	void			setWriteBuffer(std::string buffer);

	void set_readBuffer();
private:
	int				_fd;
	std::string		_readBuffer;
	std::string		_writeBuffer;
};
