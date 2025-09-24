/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cereais <cereais@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/13 18:30:05 by cereais           #+#    #+#             */
/*   Updated: 2025/09/24 11:40:17 by jperpct          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <core/Server.hpp>
#include <config/ServerConfig.hpp>
#include <net/Socket.hpp>
#include <http/HttpParser.hpp>
#include <string>
#include <vector>

int	main(int argc, char **argv) 
{
	
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
	}
}
