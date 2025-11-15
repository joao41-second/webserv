#pragma once

#ifndef SERVERCONFIG_H
#define SERVERCONFIG_H

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
#include <map>
#include <algorithm>
#include <typeinfo>

#include <sys/socket.h> // TODO Ver se ha melhor
#include <netinet/in.h> // TODO Ver se ha melhor

#include "./LocationConfig.hpp"

class ServerConfig
{
public:
	ServerConfig();
	ServerConfig(std::istream& server_file);
	ServerConfig(const ServerConfig &orig);
	ServerConfig &operator = (const ServerConfig &orig);
	virtual ~ServerConfig();

	bool					hasMethod(t_methods method) const;
	std::string const		&getName(void) const;
	std::string const		&getInterface(void) const;
	std::string const		&getRoot(void) const;
	std::string const		&getIndex(void) const;
	uint16_t				getPort(void) const;
	unsigned long			getClientMaxSize(void) const;
	std::string const		&getErrorPage(int error_num) const;
	void					validateErrorPage(const std::string &path);
	size_t					getLocNum(void) const;
	LocationConfig const	&getLocationConfig(unsigned int num) const;

	std::map<std::string, LocationConfig>	&getLocMap(void);
	std::vector<t_methods> const			&getMethods() const;
	
	void	setOneLocationConfig(LocationConfig* loc);
	void	setMethods(std::string const str);
	void	setOneMethod(std::string word);
	void	setOneErrorPage(std::string error_page_str);
	void	setClientMaxSize(std::string max_size);
	void	setPort(std::string str);
	void	setIndex(std::string index);
	void	setRoot(std::string root);
	void	setName(std::string name);

	uint16_t	stringToUint16(const std::string &str);
	void		parse_server(std::istream& server_file);

private:
	std::string		_name;		// ex: joao-rib
	std::string		_interface;	// ex: 0.0.0.0
	uint16_t		_port;		// ex: 8000
	std::string		_root;		// ex: ./joao-rib
	std::string		_index;		// ex: index.html
	unsigned long	_client_max_body_size; // ex: 10M

	std::vector<t_methods>		_methods;	// ex: GET
	std::map<int, std::string>	_error_pages; // ex: 404 , ./www/errors/404.html

	std::map<std::string, LocationConfig>	_locations;
};

#endif
