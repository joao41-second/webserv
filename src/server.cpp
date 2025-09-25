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

		if (line.substr(0,8) == "location")
		{
			// Only create a location when one is declared
			Location* curr_Location;
			curr_Location->parse_location(server_file); // TODO Add error case (ex.: bool)

			// Set the Location into the vector
			this->setLocation(curr_Location);
			// TODO Make sure that the line is at the right spot after building the Location
		}
		else if (line.substr(0,11) == "server_name")
		{
			this->_name = trim_whitespace(line.substr(12, line.size())); // TODO escrever setName()?
			if (this->_name == "")
				throw InputException("Empty field (server_name)");
		}
		else if (line.substr(0,6) == "listen") // TODO
		{
		}
		else if (line.substr(0,4) == "root") // TODO
		{
		}
		else if (line.substr(0,5) == "index") // TODO
		{
		}
		else if (line.substr(0,13) == "allow_methods") // TODO
		{
		}
	}
}

// |----------------------
// | GETTERS & SETTERS
// |----------------------

void	Server::setLocation(Location* loc)
{
	if (!loc)
	{
		this->_location_num = 0;
	}
	else
	{
		this->_locations.push_back(*loc);
		this->_location_num++;
	}
}

Location const	&Server::getLocation(unsigned int num) const
{
	if (num >= this->getLocNum())
		throw InputException("Out of bounds (Locations)"); // TODO Write a proper exception
	return(this->_locations[num]);
}

unsigned int const	&Server::getLocNum(void) const
{
	return (this->_location_num);
}

// |----------------------
// | CONSTRUCTORS & DESTRUCTORS
// |----------------------

Server &Server::operator = (const Server &orig)
{
	if (this != &orig)
	{
		this->_location_num = orig._location_num;
		this->_locations = orig._locations;
		this->_name = orig._name;
		this->_interface = orig._interface;
		this->_port = orig._port;
		this->_root = orig._root;
		this->_index = orig._index;
		this->_methods = orig._methods;
	}
	//std::cout << "Server assignment copy-constructed." << std::endl;
	return (*this);
}

Server::Server(const Server &orig)
{
	*this = orig;
	//std::cout << "Server copy-constructed." << std::endl;
}

/*Server::Server(std::istream& server_file): _location_num(0)
{
	this->_location_num = 0;
	this->parse_server(filename); //TODO review function...
	//std::cout << "Server constructed." << std::endl;
}*/

Server::Server(void)
{
	this->setLocation(NULL);
	_name = "";
	_interface = "";
	_port = "";
	_root = "";
	_index = "";
	_methods = NULL; // TODO find a valid equivalence
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

