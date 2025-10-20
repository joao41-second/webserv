/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Server.hpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cereais <cereais@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/13 18:43:46 by cereais           #+#    #+#             */
/*   Updated: 2025/10/19 18:55:04 by cereais          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once

#include <string>
#include <net/Socket.hpp>
#include <config/ServerConfig.hpp>

class Server {

public:
    Server(const std::vector<ServerConfig> &configs,
	    const std::vector<Socket*> &sockets);
	~Server();

	void launch(); // invoca o loop do eventLoop

	std::vector<ServerConfig> getConfig();

private:
	std::vector<ServerConfig> _configs;
	std::vector<Socket*> _listeningSockets;
};
