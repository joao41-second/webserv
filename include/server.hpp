#pragma once

#ifndef SERVER_H
#define SERVER_H

// TODO Considerar meter estas libraries num unico ficheiro
#include <iostream>
#include <sstream>
#include <fstream>
#include <locale>
#include <iomanip>
#include <cstdlib>
#include <cmath>
#include <climits>

#include <vector>
#include <algorithm>
#include <typeinfo>

#include <sys/socket.h> // TODO Ver se ha melhor
#include <netinet/in.h> // TODO Ver se ha melhor

#include "../include/location.hpp"

class Server
{
public:
	Server();
	//Server(std::istream& server_file);
	Server(const Server &orig);
	Server &operator = (const Server &orig);
	virtual ~Server();

	Location const		&getLocation(unsigned int num) const;
	void	setLocation(Location* loc);
	void	setMethods(std::string const str);
	void	setOneMethod(std::string word);
	void	setPort(std::string str);

	void	parse_server(std::istream& server_file);

private:
	std::string		_name;
	std::string		_interface;
	std::string		_port;
	std::string		_root;
	std::string		_index;

	std::vector<t_methods>	_methods;
	std::vector<Location>	_locations;
};

#endif