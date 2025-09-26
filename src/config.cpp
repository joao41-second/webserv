#include "../include/config.hpp"
#include "../include/server.hpp"

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

// |----------------------
// | MEMBER FUNCTIONS
// |----------------------

void	Config::parse_file(std::string filename) // TODO Write function
{
	std::ifstream	config_file(filename.c_str());
	if (!config_file.is_open())
		throw BadConfigException("Could not open file ", filename);

	std::string		line;

	// TODO Adequate checks
	// Basic checks in configuration file
	//getline(config_file, line);
	//if (line != "date | value")
	//	throw BadConfigException("Config file is not properly formatted");

	// Printing loop, once per line in configuration file
	while (getline(config_file, line))
	{
		// Only create a server when one is declared
		line = trim_whitespace(line);
		if (line != "server {")
			continue ;

		Server* curr_server = new Server();
		curr_server->parse_server(config_file); // TODO Add error case (ex.: bool)

		// Set the server into the vector
		this->setServer(curr_server);
		// TODO Make sure that the line is at the right spot after building the server
	}

	// Close configuration file
	config_file.close();
}

// |----------------------
// | GETTERS & SETTERS
// |----------------------

void	Config::setServer(Server* serv)
{
	if (serv)
	{
		this->_servers.push_back(*serv);
	}
}

Server const	&Config::getServer(unsigned int num) const
{
	if (num >= this->_servers.size())
		throw BadConfigException("Out of bounds", " - Servers");
	return(this->_servers[num]);
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

Config::Config(std::string filename)
{
	this->parse_file(filename);
	//std::cout << "Config constructed." << std::endl;
}

Config::Config(void)
{
	this->setServer(NULL);
	//std::cout << "Config constructed." << std::endl;
}

Config::~Config(void)
{
	//delete[] this->_servers;
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