#include <config/Config.hpp>
#include "../../include/config/ServerConfig.hpp"
#include "../../include/net/Socket.hpp"

// |----------------------
// | HELPER FUNCTIONS
// |----------------------

bool	isDelim(char c)
{
	if (c == ' ' || c == '\t' || c == '\n'
		|| c == '\v' || c == '\f' || c == '\r')
		return (true);
	else
		return (false);
}

const std::string	trim_whitespace(const std::string& str)
{
	int i = 0;
	while (isDelim(str[i]))
		i++;
	if (!str[i])
		return ("");

	size_t j = str.size() - 1;
	while (isDelim(str[j]))
		j--;
	return (str.substr(i, j - i + 1));
}

std::string capitalize(std::string str)
{
	for (unsigned int i = 0; i < str.length(); i++)
	{
		if (std::isalpha(str[i]))
			str[i] = std::toupper(str[i]);
	}
	return (str);
}

// |----------------------
// | MEMBER FUNCTIONS
// |----------------------

void	Config::parse_file(std::string filename)
{
	std::ifstream	config_file(filename.c_str());
	if (!config_file.is_open())
		throw BadConfigException("Could not open file ", filename);

	std::string		line;

	// Printing loop, once per line in configuration file
	while (getline(config_file, line))
	{
		// Only create a server when one is declared
		line = trim_whitespace(line);
		if (line != "server {")
			continue ;

		ServerConfig* curr_server = new ServerConfig();
		curr_server->parse_server(config_file);

		// Set the server into the vector
		this->setServerConfig(curr_server);
	}

	// Close configuration file
	config_file.close();
}

// |----------------------
// | GETTERS & SETTERS
// |----------------------

void	Config::setEnv(char **env)
{
	this->_env = env;
}

void	Config::setServerConfig(ServerConfig* serv)
{
	if (serv)
	{
		this->_servers.push_back(*serv);
		delete (serv);
	}
}

void	Config::setSockets(void)
{
	size_t	sock_num = this->getServNum();
	for (unsigned int i = 0 ; i < sock_num ; i++)
	{
		Socket *curr_sock = new Socket(this->getServerConfig(i).getPort());
		this->_sockets.push_back(curr_sock);
	}
}

std::vector<Socket*> const	&Config::getSocketVector() const
{
	return (this->_sockets);
}

std::vector<ServerConfig> const	&Config::getServerConfigVector() const
{
	return (this->_servers);
}

ServerConfig const	&Config::getServerConfig(uint16_t port) const
{
	for (unsigned int i = 0; i < this->_servers.size(); i++)
	{
		if (this->_servers[i].getPort() == port)
		{
			return (this->_servers[i]);
		}
	}
	throw BadPortException("Could not find Port ", port);
}

ServerConfig const	&Config::getServerConfig(unsigned int num) const
{
	if (num >= this->_servers.size())
	{
		std::ostringstream oss;
		oss << (_servers.size() - 1);
		throw BadConfigException("Out of bounds: Servers only go to ", oss.str());
	}
	return(this->_servers[num]);
}

size_t	Config::getServNum() const
{
	return(this->_servers.size());
}

char**	Config::getEnv() const // maybe TODO considerar "const char *const *Config::getEnv() const"
{
	return(this->_env);
}

// |----------------------
// | CONSTRUCTORS & DESTRUCTORS
// |----------------------

Config &Config::operator = (const Config &orig)
{
	if (this != &orig)
	{
		this->_servers = orig._servers;
	}
	//std::cout << "Config assignment copy-constructed." << std::endl;
	return (*this);
}

Config::Config(const Config &orig): _servers(orig._servers)
{
	//std::cout << "Config copy-constructed." << std::endl;
}

Config::Config(std::string filename, char **env)
{
	this->parse_file(filename);
	this->setSockets();
	this->setEnv(env);
	//std::cout << "Config constructed." << std::endl;
}

Config::Config(void)
{
	this->setServerConfig(NULL);
	//std::cout << "Config constructed." << std::endl;
}

Config::~Config(void)
{
	// Delete vector of sockets
	for (std::vector<Socket*>::iterator it = this->_sockets.begin();
		it != this->_sockets.end(); ++it)
	{
		delete (*it);
	}
	this->_sockets.clear();
	//std::cout << "Config destructed." << std::endl;
}

// |----------------------
// | OVERLOAD OPERATIONS
// |----------------------

// |----------------------
// | EXCEPTIONS
// |----------------------

Config::BadConfigException::BadConfigException(std::string msg, std::string value)
{
	std::ostringstream out;
	out << msg << value;
	_msg = out.str();
}

Config::BadConfigException::~BadConfigException() throw()
{
	//std::cout << "Error message destroyed" << std::endl;
}

const char *Config::BadConfigException::what() const throw()
{
	return (this->_msg.c_str());
}

Config::BadPortException::BadPortException(std::string msg, uint16_t port)
{
	std::ostringstream out;
	out << msg << port;
	_msg = out.str();
}

Config::BadPortException::~BadPortException() throw()
{
	//std::cout << "Error message destroyed" << std::endl;
}

const char *Config::BadPortException::what() const throw()
{
	return (this->_msg.c_str());
}

InputException::InputException(std::string msg)
{
	std::ostringstream out;
	out << msg;
	_msg = out.str();
}

InputException::~InputException() throw()
{
	//std::cout << "Error message destroyed" << std::endl;
}

const char *InputException::what() const throw()
{
	return (this->_msg.c_str());
}
