/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cereais <cereais@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/13 18:30:05 by cereais           #+#    #+#             */
/*   Updated: 2025/10/19 18:33:42 by cereais          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <core/Server.hpp>
#include <config/ServerConfig.hpp>
#include <config/Config.hpp>
#include <net/Socket.hpp>

int	main(int argc, char **argv, char **envp)
{
	if (argc != 2) {
		std::cout << "The program should use the template './webserv [configuration file]'" << std::endl;
		exit(EXIT_FAILURE);
	}

	try {

		Config conf_info(argv[1], envp);

		std::vector<ServerConfig>	configs = conf_info.getServerConfigVector();
		std::vector<Socket*>		sockets = conf_info.getSocketVector();

		Server server(configs, sockets);
		server.launch();
	} catch (const std::exception &e) {
		std::cerr << "Error: " << e.what() << std::endl;
	}
	return (0);
}

/*
while true; do   for i in $(seq 1 100); do     port=$((8000 + (i % 3)));     curl -s "http://localhost:$port/" >/dev/null &   done;   wait; done
*/