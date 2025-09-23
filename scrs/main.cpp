/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cereais <cereais@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/13 18:30:05 by cereais           #+#    #+#             */
/*   Updated: 2025/09/22 15:36:44 by jperpct          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <core/Server.hpp>
#include <config/ServerConfig.hpp>
#include <net/Socket.hpp>
#include <http/HttpParser.hpp>

int	main(int argc, char **argv) 
{
	
	(void )(argv);
	if (argc != 2)
		std::cout << "ERROR! This program requires exactly one argument." << std::endl;
	std::ifstream file(argv[1]);
	
	std::string line;
	std::string char_file;
	while (std::getline(file,line))
		char_file+= line+"\n";
	HttpParser ok;
	try{
		ok.new_request(char_file);
	}
	catch(std::exception &e)
	{
		std::cout << e.what() <<std::endl;
	}
}
