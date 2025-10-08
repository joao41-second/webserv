#include "../../include/config/config.hpp"
#include "../../include/config/serverConfig.hpp"
#include "../../include/config/locationConfig.hpp"

// |----------------------
// | HELPER FUNCTIONS
// |----------------------

// |----------------------
// | MEMBER FUNCTIONS
// |----------------------

void	LocationConfig::parse_location(std::istream& location_file, std::string line) // TODO Write function
{
	// Set name
	unsigned int range = line.size();
	if (line.at(range - 1) == '{')
	{
		range--;
	}
	this->setName(trim_whitespace(line.substr(8, range - 8)));

	if (this->getName() == "")
	{
		throw InputException("Empty field (server_name)");
	}

	// Printing loop, once per line in Configuration file
	while (getline(location_file, line))
	{
		line = trim_whitespace(line);
		// End function if Location segment ends
		if (line == "}")
		{
			break ;
		}

		// TODO Consider using a switch for this
		if (line.compare(0, 8, "location") == 0)
		{
			this->setSubLocation(new LocationConfig(location_file, line));
			if (!this->checkSubLocation())
			{
				throw InputException("Input error (location)"); // TODO be more specific!
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
		else if (line.compare(0, 8, "cgi_pass") == 0)
		{
			this->setPass(trim_whitespace(line.substr(9)));
			if (this->getPass() == "")
			{
				throw InputException("Empty field (cgi_pass)"); // TODO be more specific!
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
		else if (line.compare(0, 24, "client_body_buffer_size") == 0)
		{
			this->setClientBuffSize(trim_whitespace(line.substr(24)));
		}
		else if (line.compare(0, 5, "alias") == 0)
		{
			this->setAlias(true); // TODO Alterar se se converter em string
		}
	}
}

// |----------------------
// | GETTERS & SETTERS
// |----------------------

bool	LocationConfig::hasMethod(t_methods method) const
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

void	LocationConfig::setMethods(std::string const str)
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

void	LocationConfig::setOneMethod(std::string word)
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

void	LocationConfig::setIndex(std::string index)
{
	this->_index = index;
}

void	LocationConfig::setRoot(std::string root)
{
	this->_root = root;
}

void	LocationConfig::setName(std::string name)
{
	this->_name = name;
}

void	LocationConfig::setPass(std::string pass)
{
	this->_cgi_pass = pass;
}

void	LocationConfig::setClientBuffSize(std::string buff_size)
{
	char *safeguard;
	this->_client_body_buffer_size = std::strtoul(buff_size.c_str(), &safeguard, 10); // TODO Alterar se for para usar unsigned int
	if (*safeguard != '\0')
	{
		throw InputException("Invalid client_body_buffer_size"); // TODO be more specific!
	}
}

void	LocationConfig::setAlias(bool alias)
{
	this->_alias = alias;
}

void	LocationConfig::setSubLocation(LocationConfig* loc)
{
	if (loc)
	{
		this->_sub_location = loc;
	}
}

std::string const	&LocationConfig::getName(void) const
{
	return(this->_name);
}

std::string const	&LocationConfig::getRoot(void) const
{
	return(this->_root);
}

std::string const	&LocationConfig::getIndex(void) const
{
	return(this->_index);
}

std::string const	&LocationConfig::getPass(void) const
{
	return(this->_cgi_pass);
}

unsigned long	LocationConfig::getClientBuffSize(void) const
{
	return(this->_client_body_buffer_size);
}

bool const	&LocationConfig::getAlias(void) const
{
	return(this->_alias);
}

bool	LocationConfig::checkSubLocation(void) const
{
	if (this->_sub_location)
	{
		return(true);
	}
	return(false);
}

LocationConfig const	&LocationConfig::getSubLocation(void) const
{
	// TODO potential error case?
	//if (!this->_sub_location)
	//	throw InputException("Sub_Location cannot contain another sub_location");
	return(*this->_sub_location);
}

LocationConfig*	LocationConfig::clone(void) const
{
	//std::cout << "LocationConfig was cloned" << std::endl;
	return (new LocationConfig(*this));
}

// |----------------------
// | CONSTRUCTORS & DESTRUCTORS
// |----------------------

LocationConfig &LocationConfig::operator = (const LocationConfig &orig)
{
	if (this != &orig)
	{
		if (orig._sub_location)
			this->_sub_location = orig._sub_location->clone();
		else
			this->_sub_location = NULL;

		this->_name = orig._name;
		this->_root = orig._root;
		this->_index = orig._index;
		this->_cgi_pass = orig._cgi_pass;
		this->_methods = orig._methods;
		this->_client_body_buffer_size = orig._client_body_buffer_size;
		this->_alias = orig._alias;
	}
	//std::cout << "LocationConfig assignment copy-constructed." << std::endl;
	return (*this);
}

LocationConfig::LocationConfig(const LocationConfig &orig)
{
	*this = orig;
	//std::cout << "LocationConfig copy-constructed." << std::endl;
}

LocationConfig::LocationConfig(std::istream& location_file, std::string line): _sub_location(NULL)
{
	this->_client_body_buffer_size = 0;
	this->parse_location(location_file, line);
	//std::cout << "LocationConfig constructed." << std::endl;
}

LocationConfig::LocationConfig(void)
{
	this->setMethods("");
	this->setSubLocation(NULL);
	this->setName("");
	this->setRoot("");
	this->setIndex("");
	this->setPass("");
	this->setClientBuffSize(0);
	this->setAlias(false);
	//std::cout << "LocationConfig constructed." << std::endl;
}

LocationConfig::~LocationConfig(void)
{
	if (this->_sub_location)
		delete this->_sub_location;
	//std::cout << "LocationConfig destructed." << std::endl;
}

// |----------------------
// | OVERLOAD OPERATIONS
// |----------------------

// |----------------------
// | EXCEPTIONS
// |----------------------

