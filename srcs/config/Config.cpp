#include "../../include/config/Config.hpp"
#include "../../include/config/ServerConfig.hpp"
#include "../../include/net/Socket.hpp"

// |----------------------
// | HELPER FUNCTIONS
// |----------------------

bool	isPath(const std::string& str)
{
	if (str.size() < 2)
	{
		return (false);
	}
	return (str[0] == '/' || str.compare(0, 2, "./") == 0 || str[str.size() - 1] == '/');
}

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

// |----------------------hasServerConfigPorts
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

		ServerConfig curr_server = ServerConfig();
		curr_server.parse_server(config_file);

		if (!this->hasServerConfigPort(curr_server.getPort()))
		{
			// Set the server into the vector
			this->setServerConfig(&curr_server);
		}
		else
		{
			// Invalid server, do not add
			std::cout << "Warning: Configuration file contains servers with repeated ports!" << std::endl;
			std::cout << "Warning: Considering only the first server of Port " << curr_server.getPort() << std::endl;
		}
	}

	// Close configuration file
	config_file.close();
}

// |----------------------
// | GETTERS & SETTERS
// |----------------------

void	Config::removeServerConfig(unsigned int num)
{
	if (num < this->getServNum())
	{
		this->_servers.erase(this->_servers.begin() + num);
	}
}

void	Config::setEnv(char **env)
{
	this->_env = env;
}

void	Config::setServerConfig(ServerConfig* serv)
{
	if (serv)
	{
		this->_servers.push_back(*serv);
	}
}

void	Config::setSockets(void)
{
	size_t	sock_num = this->getServNum();
	unsigned int i = 0;
	while (i < sock_num)
	{
		try
		{
			Socket *curr_sock = new Socket(this->getServerConfig(i).getPort());
			this->_sockets.push_back(curr_sock);
			i++;
		}
		catch (std::exception &e)
		{
			std::cerr << "Error: " << e.what() << std::endl;
			std::cerr << "Warning: Removing server for Port " << this->getServerConfig(i).getPort() << std::endl;
			this->removeServerConfig(i);
			sock_num--;
		}
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

bool	Config::hasServerConfigPort(uint16_t port)
{
	for (unsigned int i = 0; i < this->_servers.size(); i++)
	{
		if (this->_servers[i].getPort() == port)
		{
			return (true);
		}
	}
	return (false);
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
	// TODO Ver se pastas têm permissões
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
