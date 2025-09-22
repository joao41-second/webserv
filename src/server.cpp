#include "../include/Server.hpp"
#include "../include/Location.hpp"

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
	while (getline(config_file, line))
	{
		line = trim_whitespace(line);
		// End function if server segment ends
		if (line == "}")
			break ;

		if (line.substr(0,8) == "location")
		{
			// Only create a location when one is declared
			Location curr_Location;
			curr_Location.parse_location(config_file); // TODO BUILD THE LOCATION CLASS

			// Set the Location into the vector
			this->setLocation(curr_Location);
			// TODO Make sure that the line is at the right spot after building the Location
		}
		else
		{
			//parse_other_info(); // TODO Incorporate remaining types of information
		}
	}
}

// |----------------------
// | GETTERS & SETTERS
// |----------------------

void	Server::setLocation(Location loc)
{
	if (!loc)
	{
		this->_location_num = 0;
	}
	else
	{
		this->_locations.push_back(loc);
		this->_location_num++;
	}
}

Location const	&getLocation(unsigned int num) const
{
	if (num >= this->getLocNum())
		throw BadConfigException("Out of bounds", " - Locations");
	return(this->_locations[num]);
}

unsigned int const	&getLocNum(void) const
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
	}
	//std::cout << "Server assignment copy-constructed." << std::endl;
	return (*this);
}

Server::Server(const Server &orig): _location_num(orig._location_num), _locations(orig._locations)
{
	//std::cout << "Server copy-constructed." << std::endl;
}

/*Server::Server(std::string filename): _location_num(0)
{
	this->_location_num = 0;
	this->parse_server(filename); //TODO review function...
	//std::cout << "Server constructed." << std::endl;
}*/

Server::Server(void)
{
	this->setLocation(NULL);
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

