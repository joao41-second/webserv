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
#include <algorithm>
#include <typeinfo>

#include <sys/socket.h> // TODO Ver se ha melhor
#include <netinet/in.h> // TODO Ver se ha melhor

#include "./locationconfig.hpp"

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
	size_t					getLocNum(void) const;
	//LocationConfig const	&getLocationConfig(std::string name) const; // TODO Location should be found by name...
	LocationConfig const	&getLocationConfig(unsigned int num) const; // TODO Should the return be const Location?
	bool					hasMethod(t_methods method) const;

	void	setLocationConfig(LocationConfig* loc);
	void	setMethods(std::string const str);
	void	setOneMethod(std::string word);
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

	std::vector<t_methods>		_methods;	// ex: GET
	std::vector<LocationConfig>	_locations;
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
