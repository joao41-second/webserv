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
	Server(std::istream& server_file);
	Server(const Server &orig);
	Server &operator = (const Server &orig);
	virtual ~Server();

	std::string const	&getName(void) const;
	std::string const	&getInterface(void) const;
	std::string const	&getPort(void) const;
	std::string const	&getRoot(void) const;
	std::string const	&getIndex(void) const;
	size_t const		&getLocNum(void) const;
	Location const		&getLocation(unsigned int num) const;
	void	setLocation(Location* loc);
	void	setMethods(std::string const str);
	void	setOneMethod(std::string word);
	void	setPort(std::string str);

	void	parse_server(std::istream& server_file);

private:
	std::string		_name;		// ex: joao-rib
	std::string		_interface;	// ex: 0.0.0.0
	std::string		_port;		// ex: 8000
	std::string		_root;		// ex: 
	std::string		_index;		// ex: 

	std::vector<t_methods>	_methods;
	std::vector<Location>	_locations;
};

std::string capitalize(std::string str);

#endif