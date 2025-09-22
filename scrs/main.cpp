/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cereais <cereais@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/13 18:30:05 by cereais           #+#    #+#             */
/*   Updated: 2025/09/22 14:21:58 by jperpct          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <algorithm>
#include <core/Server.hpp>
#include <config/ServerConfig.hpp>
#include <fstream>
#include <net/Socket.hpp>
#include <http/HttpParser.hpp>
#include <string>

int	main(int argc, char **argv) 
{
	
	(void )(argv);
	if (argc != 2)
		std::cout << "ERROR! This program requires exactly one argument." << std::endl;
	std::ifstream file(argv[1]);
	
	std::string line;
	std::string char_file;
	while (std::getline(file,line))
		char_file+= "\n"+line;
	std::cout << char_file << std::endl;
	HttpParser ok;
}
