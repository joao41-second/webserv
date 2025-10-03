/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: joseoliv <joseoliv@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/13 18:30:05 by cereais           #+#    #+#             */
/*   Updated: 2025/09/25 19:43:20 by joseoliv         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/core/Server.hpp"
#include "../include/config/ServerConfig.hpp"
#include "../include/net/Socket.hpp"

int	main(int argc, char *argv[]) {
	
	if (argc != 2) {
		std::cout << "ERROR! Please introduce only one argument." << std::endl;
	}

	std::vector<ServerConfig> configs = //ConfigParser::parse("webserv.conf");
    std::vector<Socket> sockets = //SocketFactory::someListeningSockets(configs);

    Server server(configs, sockets);
    server.run();

    return 0;
}
