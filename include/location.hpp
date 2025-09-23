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

class Location
{
public:
	Location(); // TODO Class isn't well defined yet
	//Location(std::string filename);
	Location(const Location &orig); // TODO Class isn't well defined yet
	Location &operator = (const Location &orig); // TODO Class isn't well defined yet
	virtual ~Location();

	//unsigned int const	&getLocNum(void) const;
	//placeholder			&getplaceholder(unsigned int num) const;
	//void				setplaceholder(placeholder loc);

	void	parse_location(std::istream& location_file);

private:
	//std::vector<placeholder>	_placeholders;
	//unsigned int			_placeholder_num;
};

#endif