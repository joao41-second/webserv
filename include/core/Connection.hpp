/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Connection.hpp                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: joseoliv <joseoliv@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/13 18:43:35 by cereais           #+#    #+#             */
/*   Updated: 2025/09/15 19:16:01 by joseoliv         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once

#include <string>

//Connection represents each client connected to the server
//usage of accept() if the fd is readable

class ServerConfig;

class Connection {
	
public:
	Connection(int fd, const ServerConfig& cfg);
	~Connection();

	void	handleRead();               // le dados do socket
    void	handleWrite(); 				// envia dados do socket
	void	processRequest();           // decide CGI, estático || erros

private:
	std::string	_readBuffer;
    std::string	_writeBuffer;
	
};
