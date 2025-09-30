#include "../include/config.hpp"
#include "../include/server.hpp"
#include "../include/location.hpp"

// |----------------------
// | HELPER FUNCTIONS
// |----------------------

// |----------------------
// | MEMBER FUNCTIONS
// |----------------------

void	Server::parse_server(std::istream& server_file) // TODO Write function
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

		// TODO Consider using a switch for this
		if (line.compare(0, 8, "location") == 0)
		{
			this->setLocation(new Location(server_file, line));

			if (this->_locations.empty())
			{
				throw InputException("Input error (location)"); // TODO be more specific!
			}
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
			if (this->getPort() == "" || this->getInterface() == "")
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
	}
}

// |----------------------
// | GETTERS & SETTERS
// |----------------------

bool	Server::hasMethod(t_methods method) const
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

void	Server::setMethods(std::string const str)
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

void	Server::setOneMethod(std::string word)
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

void	Server::setPort(std::string str)
{
	if (str == "")
	{
		this->_interface = "";
		this->_port = "";
		return ;
	}

	for(unsigned int i = 0; i < str.size() ; i++)
	{
		if (str[i] == ':')
		{
			this->_interface = trim_whitespace(str.substr(0, i));
			this->_port = trim_whitespace(str.substr(i + 1));
			return ;
		}
	}

	throw InputException("Invalid syntax (listen)");
}

void	Server::setIndex(std::string index)
{
	this->_index = index;
}

void	Server::setRoot(std::string root)
{
	this->_root = root;
}

void	Server::setName(std::string name)
{
	this->_name = name;
}

void	Server::setLocation(Location* loc)
{
	if (loc)
	{
		this->_locations.push_back(*loc);
	}
}

Location const	&Server::getLocation(unsigned int num) const
{
	if (num >= this->_locations.size())
		throw InputException("Out of bounds (Locations)"); // TODO Write a proper exception
	return(this->_locations[num]);
}

size_t	Server::getLocNum(void) const
{
	return(this->_locations.size());
}

std::string const	&Server::getName(void) const
{
	return(this->_name);
}

std::string const	&Server::getPort(void) const
{
	return(this->_port);
}

std::string const	&Server::getInterface(void) const
{
	return(this->_interface);
}

std::string const	&Server::getRoot(void) const
{
	return(this->_root);
}

std::string const	&Server::getIndex(void) const
{
	return(this->_index);
}

// |----------------------
// | CONSTRUCTORS & DESTRUCTORS
// |----------------------

Server &Server::operator = (const Server &orig)
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
	}
	//std::cout << "Server assignment copy-constructed." << std::endl;
	return (*this);
}

Server::Server(const Server &orig)
{
	*this = orig;
	//std::cout << "Server copy-constructed." << std::endl;
}

Server::Server(std::istream& server_file)
{
	this->parse_server(server_file);
	//std::cout << "Server constructed." << std::endl;
}

Server::Server(void)
{
	this->setLocation(NULL);
	this->setMethods("");
	this->setName("");
	this->setPort("");
	this->setRoot("");
	this->setIndex("");
	//std::cout << "Server constructed." << std::endl;
}

Server::~Server(void)
{
	//delete[] _locations;
	//std::cout << "Server destructed." << std::endl;
}

// |----------------------
// | OVERLOAD OPERATIONS
// |----------------------

// |----------------------
// | EXCEPTIONS
// |----------------------

