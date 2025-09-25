/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Connection.hpp                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: joseoliv <joseoliv@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/13 18:43:35 by cereais           #+#    #+#             */
/*   Updated: 2025/09/25 21:12:29 by joseoliv         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once

#include <string>
#include <vector>
#include <sys/socket.h>

//Connection represents each client connected to the server

class ServerConfig;

class Connection {
	
public:
	Connection(int fd, std::vector<ServerConfig>);
	~Connection();

	void	handleRead();               // le dados do socket
    void	handleWrite(); 				// envia dados do socket
	void	processRequest();           // decide CGI, estático || erros

private:
	std::string	_readBuffer;
    std::string	_writeBuffer;
	
};
