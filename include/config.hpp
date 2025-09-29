#pragma once

#ifndef CONFIG_H
#define CONFIG_H

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

class Server;
//class Location;

class Config
{
public:
	Config();
	Config(std::string filename);
	Config(const Config &orig);
	Config &operator = (const Config &orig);
	virtual ~Config();

	size_t			getServNum(void) const;
	Server const	&getServer(std::string port) const;
	//Server const	&getServer(unsigned int num) const; // TODO Should the return be const Server?
	void			setServer(Server* serv);

	void	parse_file(std::string filename); // TODO Write function...

	class BadConfigException: public std::exception
	{
	public:
		BadConfigException(std::string msg, std::string value);
		virtual ~BadConfigException() throw();
		virtual const char *what() const throw();
	private:
		std::string _msg;
	};
private:
	std::vector<Server>	_servers;
};

bool	isDelim(char c);
const std::string	trim_whitespace(const std::string& str);

class InputException: public std::exception
{
public:
	InputException(std::string msg);
	virtual ~InputException() throw();
	virtual const char *what() const throw();
private:
	std::string _msg;
};

#endif