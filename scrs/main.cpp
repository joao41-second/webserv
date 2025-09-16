/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cereais <cereais@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/13 18:30:05 by cereais           #+#    #+#             */
/*   Updated: 2025/09/16 13:39:16 by cereais          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/core/Server.hpp"
#include "../include/config/ServerConfig.hpp"
#include "../include/net/Socket.hpp"

int	main(int argc, char *argv[]) {
	
	if (argc != 2) {
		std::cout << "ERROR! This program requires exactly one argument." << std::endl;
	}

	std::vector<ServerConfig> configs = //ConfigParser::parse("webserv.conf");
    std::vector<Socket> sockets = //SocketFactory::someListeningSockets(configs);

    Server server(configs, sockets);
    server.run();

    return 0;
}
