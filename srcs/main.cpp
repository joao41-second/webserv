/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cereais <cereais@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/13 18:30:05 by cereais           #+#    #+#             */
/*   Updated: 2025/10/14 14:21:26 by cereais          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/core/Server.hpp"
#include "../include/config/ServerConfig.hpp"
#include "../include/config/Config.hpp"
#include "../include/net/Socket.hpp"

int	main(int argc, char **argv, char **envp)
{
	if (argc != 2)
	{
		throw InputException("The program should use the template './webserv [configuration file]'");
	}

	Config conf_info(argv[1], envp);

	std::vector<ServerConfig>	configs = conf_info.getServerConfigVector();
	std::vector<Socket*>		sockets = conf_info.getSocketVector();

	std::cout << "helooooo" << std::endl;
	Server server(configs, sockets);
	server.launch();

	return (0);
}

/*#include <core/Server.hpp>
#include <config/ServerConfig.hpp>
#include <net/Socket.hpp>
#include <http/HttpParser.hpp>

int	main(int argc, char *argv[]) {
	
	(void )(argv);
	if (argc != 2)
	{
		std::cout << "ERROR! This program requires exactly one argument." << std::endl;
		return (1);
	}
	std::ifstream file(argv[1]);	
	std::string line;
	std::string char_file;
	while (std::getline(file,line))
		char_file+= line+"\n";
	
	file.close();
	try{	
		HttpParser::new_request(char_file);
		std::vector<std::string> env = HttpParser::get_request_env();
		for (int i = 0; i < (int)env.size(); i++) 
			HTTP_MSG(env[i]);	
		HTTP_MSG(HttpParser::get_request_msg());
	}
	catch(std::exception &e)
	{
		std::cout << e.what() <<std::endl;
	}*/