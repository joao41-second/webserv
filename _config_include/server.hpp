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

#include "../_config_include/location.hpp"

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
	size_t				getLocNum(void) const;
	//Location const	&getLocation(std::string name) const; // TODO Location should be found by name...
	Location const		&getLocation(unsigned int num) const; // TODO Should the return be const Server?
	bool				hasMethod(t_methods method) const;

	void	setLocation(Location* loc);
	void	setMethods(std::string const str);
	void	setOneMethod(std::string word);
	void	setPort(std::string str);
	void	setIndex(std::string index);
	void	setRoot(std::string root);
	void	setName(std::string name);

	void	parse_server(std::istream& server_file);

private:
	std::string		_name;		// ex: joao-rib
	std::string		_interface;	// ex: 0.0.0.0
	std::string		_port;		// ex: 8000
	std::string		_root;		// ex: ./joao-rib
	std::string		_index;		// ex: index.html

	std::vector<t_methods>	_methods;	// ex: GET
	std::vector<Location>	_locations;
};

std::string capitalize(std::string str);

#endif