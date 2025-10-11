#include "../../include/config/Config.hpp"
#include "../../include/config/ServerConfig.hpp"
#include "../../include/config/LocationConfig.hpp"

// |----------------------
// | HELPER FUNCTIONS
// |----------------------

// |----------------------
// | MEMBER FUNCTIONS
// |----------------------

void	ServerConfig::parse_server(std::istream& server_file) // TODO Write function
{
	std::string		line;

	// Printing loop, once per line in Configuration file
	while (getline(server_file, line))
	{
		line = trim_whitespace(line);
		// End function if server segment ends
		if (line == "}")
		{
			break ;
		}

		if (line.compare(0, 8, "location") == 0) // TODO locmap
		{
			this->setOneLocationConfig(new LocationConfig(server_file, line));

			/*if (this->getLocationConfig(this->getLocNum() - 1).checkSubLocation())
			{
				this-setOneLocationConfig(this->getLocationConfig(this->getLocNum() - 1).getSubLocation());
			}*/
			// TODO if subLocation exists, add one more to map, or allocate the pointer
		}
		else if (line.compare(0, 11, "server_name") == 0)
		{
			this->setName(trim_whitespace(line.substr(11)));
			if (this->getName() == "")
			{
				throw InputException("Empty field (server_name)"); // TODO be more specific!
			}
		}
		else if (line.compare(0, 6, "listen") == 0)
		{
			this->setPort(trim_whitespace(line.substr(6)));
			if (this->getPort() == 0 || this->getInterface() == "") // TODO Can ports actually be 0?
			{
				throw InputException("Empty field (listen)"); // TODO be more specific!
			}
		}
		else if (line.compare(0, 4, "root") == 0)
		{
			this->setRoot(trim_whitespace(line.substr(4)));
			if (this->getRoot() == "")
			{
				throw InputException("Empty field (root)"); // TODO be more specific!
			}
		}
		else if (line.compare(0, 5, "index") == 0)
		{
			this->setIndex(trim_whitespace(line.substr(5)));
			if (this->getIndex() == "")
			{
				throw InputException("Empty field (index)"); // TODO be more specific!
			}
		}
		else if (line.compare(0, 13, "allow_methods") == 0)
		{
			this->setMethods(trim_whitespace(line.substr(13)));
			if (this->_methods.empty())
			{
				throw InputException("Empty field (allow_methods)"); // TODO be more specific!
			}
		}
		else if (line.compare(0, 20, "client_max_body_size") == 0)
		{
			this->setClientMaxSize(trim_whitespace(line.substr(20)));
		}
		else if (line.compare(0, 10, "error_page") == 0)
		{
			this->setOneErrorPage(trim_whitespace(line.substr(10)));
		}
	}
}

uint16_t ServerConfig::stringToUint16(const std::string &str)
{
	char* safeguard;
	unsigned long ul = std::strtoul(str.c_str(), &safeguard, 10);

	if (*safeguard != '\0')
	{
		throw InputException("Input port is not a number");
	}

	if (ul > 65535)
	{
		throw InputException("Port cannot be higher than uint_16 max (65535)");
	}

	return (static_cast<uint16_t>(ul));
}

// |----------------------
// | GETTERS & SETTERS
// |----------------------

bool	ServerConfig::hasMethod(t_methods method) const
{
	for (unsigned int i = 0; i < this->_methods.size(); i++)
	{
		if (this->_methods[i] == method)
		{
			return (true);
		}
	}
	return (false);
}

void	ServerConfig::setMethods(std::string const str)
{
	for(unsigned int i = 0; i < str.size() ; i++)
	{
		if (!isDelim(str[i]))
		{
			size_t k = 0;
			while (i + k < str.size() && !isDelim(str[i + k]))
				k++;
			this->setOneMethod(str.substr(i, k));
			i += k - 1;
		}
	}
}

void	ServerConfig::setOneMethod(std::string word)
{
	const std::string method_name[] = 
	{
		"GET",
		"HEAD",
		"POST",
		"PUT",
		"DELETE",
		"OPTIONS",
		"PATCH",
		"TRACE",
		"CONNECT"
	};

	unsigned int method_num = sizeof(method_name) / sizeof(method_name[0]);
	for (unsigned int i = 0; i < method_num ; i++)
	{
		if (capitalize(word) == method_name[i] && !this->hasMethod(static_cast<t_methods>(i)))
		{
			this->_methods.push_back(static_cast<t_methods>(i));
			return ;
		}
	}
	throw InputException("Invalid method");
}

void	ServerConfig::setOneErrorPage(std::string error_page_str)
{
	char 			*safeguard;
	unsigned long	error_num = static_cast<int>(std::strtoul(error_page_str.substr(0, 3).c_str(), &safeguard, 10));
	if (*safeguard != '\0')
	{
		throw InputException("Invalid Error Page in configuration file");
	}

	this->_error_pages[error_num] = trim_whitespace(error_page_str.substr(3));
}

void	ServerConfig::setOneLocationConfig(LocationConfig* loc)
{
	if (loc)
	{
		std::string	locname = loc->getName();
		//this->_locations.push_back(*loc); // TODO locmap
		this->_locations[locname] = *loc; // TODO testar
		delete (loc);
	}
}

void	ServerConfig::setClientMaxSize(std::string max_size)
{
	size_t	lim = max_size.size() - 1;
	char	unit = max_size[lim];
	char	*safeguard;

	this->_client_max_body_size = std::strtoul(max_size.substr(0, lim).c_str(), &safeguard, 10);
	if (*safeguard != '\0')
	{
		throw InputException("Invalid client_max_body_size");
	}

	if (unit == 'k' || unit == 'K')
	{
		this->_client_max_body_size *= 1024;
	}
	else if (unit == 'm' || unit == 'M')
	{
		this->_client_max_body_size *= 1024 * 1024;
	}
	else if (unit == 'g' || unit == 'G')
	{
		this->_client_max_body_size *= 1024 * 1024 * 1024;
	}
}

void	ServerConfig::setPort(std::string str)
{
	if (str == "")
	{
		this->_interface = "";
		this->_port = 0;
		return ;
	}

	for(unsigned int i = 0; i < str.size() ; i++)
	{
		if (str[i] == ':')
		{
			this->_interface = trim_whitespace(str.substr(0, i));
			this->_port = stringToUint16(trim_whitespace(str.substr(i + 1)));
			return ;
		}
	}

	throw InputException("Invalid syntax (listen)");
}

void	ServerConfig::setIndex(std::string index)
{
	this->_index = index;
}

void	ServerConfig::setRoot(std::string root)
{
	this->_root = root;
}

void	ServerConfig::setName(std::string name)
{
	this->_name = name;
}

LocationConfig const	&ServerConfig::getLocationConfig(unsigned int num) const
{
	if (num >= this->_locations.size())
		throw InputException("Out of bounds (Locations)"); // TODO Write a proper exception

	std::map<std::string, LocationConfig>::const_iterator it = this->_locations.begin(); // TODO should this be const?
	unsigned int i = 0;
	while (i < num)
	{
		i++;
		it++;
	}

	return(it->second); // TODO testar
}

size_t	ServerConfig::getLocNum(void) const
{
	return(this->_locations.size());
}

std::string const		&ServerConfig::getErrorPage(int error_num) const
{
	std::map<int, std::string>::const_iterator it = this->_error_pages.find(error_num);
	if (it != this->_error_pages.end())
	{
		return (it->second);
	}

	return(this->_error_pages.find(404)->second); // Default error page
}

std::string const	&ServerConfig::getName(void) const
{
	return(this->_name);
}

uint16_t	ServerConfig::getPort(void) const
{
	return(this->_port);
}

std::string const	&ServerConfig::getInterface(void) const
{
	return(this->_interface);
}

std::string const	&ServerConfig::getRoot(void) const
{
	return(this->_root);
}

std::string const	&ServerConfig::getIndex(void) const
{
	return(this->_index);
}

unsigned long	ServerConfig::getClientMaxSize(void) const
{
	return(this->_client_max_body_size);
}

// |----------------------
// | CONSTRUCTORS & DESTRUCTORS
// |----------------------

ServerConfig &ServerConfig::operator = (const ServerConfig &orig)
{
	if (this != &orig)
	{
		this->_locations = orig._locations;
		this->_methods = orig._methods;
		this->_name = orig._name;
		this->_interface = orig._interface;
		this->_port = orig._port;
		this->_root = orig._root;
		this->_index = orig._index;
		this->_client_max_body_size = orig._client_max_body_size;
		this->_error_pages = orig._error_pages;
	}
	//std::cout << "ServerConfig assignment copy-constructed." << std::endl;
	return (*this);
}

ServerConfig::ServerConfig(const ServerConfig &orig)
{
	*this = orig;
	//std::cout << "ServerConfig copy-constructed." << std::endl;
}

ServerConfig::ServerConfig(std::istream& server_file)
{
	this->_client_max_body_size = 0;
	this->setOneErrorPage("404 ./www/errors/404.html"); // TODO define the default error
	this->parse_server(server_file);
	//std::cout << "ServerConfig constructed." << std::endl;
}

ServerConfig::ServerConfig(void)
{
	this->setOneLocationConfig(NULL);
	this->setMethods("");
	this->setName("");
	this->setPort("");
	this->setRoot("");
	this->setIndex("");
	this->setOneErrorPage("404 ./www/errors/404.html"); // TODO define the default error
	this->_client_max_body_size = 0;
	//std::cout << "ServerConfig constructed." << std::endl;
}

ServerConfig::~ServerConfig(void)
{
	//std::cout << "ServerConfig destructed." << std::endl;
}

// |----------------------
// | OVERLOAD OPERATIONS
// |----------------------

// |----------------------
// | EXCEPTIONS
// |----------------------

