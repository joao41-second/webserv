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

#include <fcntl.h>		// TODO Ver se ha melhor
#include <sys/socket.h> // TODO Ver se ha melhor
#include <netinet/in.h> // TODO Ver se ha melhor
//#include <arpa/inet.h>

class Socket;
class ServerConfig;
//class LocationConfig;

class Config
{
public:
	Config();
	Config(std::string filename, char **env);
	Config(const Config &orig);
	Config &operator = (const Config &orig);
	virtual ~Config();

	size_t							getServNum(void) const;
	ServerConfig const				&getServerConfig(uint16_t port) const; // TODO Should the return be const?
	std::vector<ServerConfig> const	&getServerConfigVector() const; // TODO Should the return be const?
	std::vector<Socket> const		&getSocketVector() const; // TODO Should the return be const?

	void	setServerConfig(ServerConfig* serv);
	void	setSockets(void);
	void	setEnv(char **env);

	void	parse_file(std::string filename);

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
	std::vector<ServerConfig>	_servers;
	std::vector<Socket>			_sockets; // TODO testar
	char	**_env; // TODO Should this be a deep copy?

	ServerConfig const	&getServerConfig(unsigned int num) const; // TODO Should the return be const?
};

bool	isDelim(char c);
const std::string	trim_whitespace(const std::string& str);
std::string capitalize(std::string str);

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