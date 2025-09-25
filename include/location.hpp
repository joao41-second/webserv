#pragma once

#ifndef LOCATION_H
#define LOCATION_H

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

class Location
{
public:
	Location();
	//Location(std::istream& location_file);
	Location(const Location &orig);
	Location &operator = (const Location &orig);
	virtual ~Location();

	void		setSubLocation(Location* loc);
	void		setMethods(std::string const str);
	void		setOneMethod(std::string word);
	Location*	clone(void) const;

	void	parse_location(std::istream& location_file, std::string line);

private:
	std::string		_name;
	std::string		_root;
	std::string		_index;
	std::string		_cgi_pass;
	unsigned long	_client_body_buffer_size; // TODO appropriate type?
	bool			_alias; // TODO should accept string?

	Location*		_sub_location;

	std::vector<t_methods>	_methods;
};

#endif