#include "../include/config.hpp"
#include "../include/server.hpp"
#include "../include/location.hpp"

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

void	Server::parse_server(std::istream& server_file) // TODO Write function
{
	std::string		line;

	// TODO Adequate checks
	// Basic checks in Configuration file
	//getline(server_file, line);
	//if (line != "date | value")
	//	throw BadConfigException("Server file is not properly formatted");

	// Printing loop, once per line in Configuration file
	while (getline(server_file, line))
	{
		line = trim_whitespace(line);
		// End function if server segment ends
		if (line == "}")
			break ;

		// TODO Consider using a switch for this
		if (line.compare(0, 8, "location") == 0)
		{
			// Only create a location when one is declared
			Location* curr_Location = Location();
			curr_Location->parse_location(server_file, line); // TODO Add error case (ex.: bool)

			// Set the Location into the vector
			this->setLocation(curr_Location);
			// TODO Make sure that the line is at the right spot after building the Location
			if (this->_locations.empty())
				throw InputException("Input error (location)");
		}
		else if (line.compare(0, 11, "server_name") == 0)
		{
			this->_name = trim_whitespace(line.substr(11)); // TODO escrever setName()?
			if (this->_name == "") // TODO escrever getName()?
				throw InputException("Empty field (server_name)");
		}
		else if (line.compare(0, 6, "listen") == 0) // TODO
		{
			this->setPort(trim_whitespace(line.substr(6)));
			if (this->_port == "" || this->_interface == "") // TODO escrever getPort/Interface()?
				throw InputException("Empty field (listen)");
		}
		else if (line.compare(0, 4, "root") == 0)
		{
			this->_root = trim_whitespace(line.substr(4)); // TODO escrever setRoot()?
			if (this->_root == "") // TODO escrever getRoot()?
				throw InputException("Empty field (root)");
		}
		else if (line.compare(0, 5, "index") == 0)
		{
			this->_index = trim_whitespace(line.substr(5)); // TODO escrever setIndex()?
			if (this->_index == "") // TODO escrever getIndex()?
				throw InputException("Empty field (index)");
		}
		else if (line.compare(0, 13, "allow_methods") == 0)
		{
			this->setMethods(trim_whitespace(line.substr(13)));
			if (this->_methods.empty())
				throw InputException("Empty field (allow_methods)");
		}
	}
}

// |----------------------
// | GETTERS & SETTERS
// |----------------------

void	Server::setPort(std::string str)
{
	for(unsigned int i = 0; i < str.size() ; i++)
	{
		if (str[i] == ':')
		{
			this->_interface = trim_whitespace(str.substr(0, i));
			this->_port = trim_whitespace(str.substr(i));
			return ;
		}
	}
	throw InputException("Invalid syntax (listen)");
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
		if (capitalize(word) == method_name[i])
		{
			/*switch (i)
			{
			case 0:
				this->_methods.push_back(GET);
				break;
			case 1:
				this->_methods.push_back(HEAD);
				break;
			case 2:
				this->_methods.push_back(POST);
				break;
			(...)
			default:
				throw InputException("Invalid method");
			}*/
			this->_methods.push_back(static_cast<t_methods>(i));
			// TODO Prevenir duplicados. Potencialmente usar um container "set", ou simplesmente escrever findMethod()
			return ;
		}
	}
	throw InputException("Invalid method");
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

/*Server::Server(std::istream& server_file)
{
	this->parse_server(filename); //TODO review function...
	//std::cout << "Server constructed." << std::endl;
}*/

Server::Server(void)
{
	this->setLocation(NULL);
	this->setMethods("");
	_name = ""; // TODO escrever setName()?
	_interface = ""; // TODO escrever setPort()?
	_port = ""; // TODO escrever setPort()?
	_root = ""; // TODO escrever setRoot()?
	_index = ""; // TODO escrever setIndex()?
	//std::cout << "Server constructed." << std::endl;
}

Server::~Server(void)
{
	//std::cout << "Server destructed." << std::endl;
}

// |----------------------
// | OVERLOAD OPERATIONS
// |----------------------

// |----------------------
// | EXCEPTIONS
// |----------------------

