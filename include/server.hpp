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

class Location;

class Server
{
public:
	Server();
	//Server(std::string filename);
	Server(const Server &orig);
	Server &operator = (const Server &orig);
	virtual ~Server();

	unsigned int const	&getLocNum(void) const;
	Location const		&getLocation(unsigned int num) const;
	void				setLocation(Location* loc);

	void	parse_server(std::istream& server_file);

private:
	std::string		_name;
	std::string		_port;
	std::string		_root;
	std::string		_index;
	std::string		_allow_methods;  // TODO enum?

	std::vector<Location>	_locations;
	unsigned int			_location_num;
};

#endif