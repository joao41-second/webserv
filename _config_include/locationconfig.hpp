#pragma once

#ifndef LOCATIONCONFIG_H
#define LOCATIONCONFIG_H

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

enum t_methods
{
	GET,	// Retrieve a resource
	HEAD,	// Retrieve a header from a resource
	POST,	// Send data to server
	PUT,	// Upload a resource to a specific URL
	DELETE,	// Remove a resource
	OPTIONS,// Inquire server about available methods
	PATCH,	// Partially modify a resource
	TRACE,	// Echo a request
	CONNECT // Establish a proxy tunnel
};

class LocationConfig
{
public:
	LocationConfig();
	LocationConfig(std::istream& location_file, std::string line);
	LocationConfig(const LocationConfig &orig);
	LocationConfig &operator = (const LocationConfig &orig);
	virtual ~LocationConfig();

	std::string const		&getName(void) const;
	std::string const		&getRoot(void) const;
	std::string const		&getIndex(void) const;
	std::string const		&getPass(void) const;
	unsigned long			getClientBuffSize(void) const;
	bool const				&getAlias(void) const;
	bool					checkSubLocation(void) const;
	LocationConfig const	&getSubLocation(void) const;
	bool					hasMethod(t_methods method) const;

	void	setSubLocation(LocationConfig* loc);
	void	setMethods(std::string const str);
	void	setOneMethod(std::string word);
	void	setIndex(std::string index);
	void	setRoot(std::string root);
	void	setName(std::string name);
	void	setPass(std::string pass);
	void	setClientBuffSize(std::string buff_size);
	void	setAlias(bool alias);

	LocationConfig*	clone(void) const;

	void	parse_location(std::istream& location_file, std::string line);

private:
	std::string		_name;		// ex: /directory
	std::string		_root;		// ex: joao-rib/
	std::string		_index;		// ex: joao.bad_extension
	std::string		_cgi_pass;	// ex: test_linux/ubuntu_cgi_tester
	unsigned long	_client_body_buffer_size; // TODO appropriate type?
	bool			_alias;		// TODO should accept string?

	std::vector<t_methods>	_methods;	// ex: GET

	LocationConfig*	_sub_location;
};

#endif