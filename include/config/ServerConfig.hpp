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

	std::string const		&getName(void) const;
	std::string const		&getInterface(void) const;
	std::string const		&getRoot(void) const;
	std::string const		&getIndex(void) const;
	uint16_t				getPort(void) const;
	unsigned long			getClientMaxSize(void) const;
	std::string const		&getErrorPage(int error_num) const;
	size_t					getLocNum(void) const;
	LocationConfig const	&getLocationConfig(unsigned int num) const; // TODO Should the return be const Location? // TODO locmap
	bool					hasMethod(t_methods method) const;

	void	setOneLocationConfig(LocationConfig* loc); // TODO locmap
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
	unsigned long	_client_max_body_size; // ex: 10M // TODO should this be size_t?

	std::map<int, std::string>	_error_pages; // ex: 404 , ./www/errors/404.html

	std::vector<t_methods>		_methods;	// ex: GET
	//std::vector<LocationConfig>	_locations;
	std::map<std::string, LocationConfig>	_locations; // TODO locmap: sub-location é mais um elemento deste map, key é nome
};

#endif

/*

Quando o servidor inicia:
O parser lê o ficheiro .conf e cria objetos ServerConfig

A Connection ou o Server usa ServerConfig para:
Saber qual root usar para ficheiros estáticos.
Saber qual server name corresponde ao header Host: do request (virtual host).
Aplicar limites globais (client_max_body_size).
Escolher error_pages personalizadas.

example of config file:

server {
    listen 127.0.0.1:8080;
    server_name localhost;

    root ./www;
    index index.html;

    client_max_body_size 10M;

    error_page 404 ./www/errors/404.html;
    error_page 500 ./www/errors/500.html;

    location / {
        root ./www/html;
        index index.html;
    }

    location /uploads {
        root ./www/uploads;
    }

    location /cgi-bin/ {
        cgi_pass /usr/bin/python3;
    }
}

*/
