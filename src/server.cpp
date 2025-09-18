#include "Server.hpp"

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

void	Server::parse_server(std::string filename) // TODO Write function
{
	std::ifstream	Server_file(filename.c_str());
	std::string		line;

	// Basic checks in Serveruration file
	getline(Server_file, line);
	if (line != "date | value") // TODO Adequate checks
		throw BadConfigException("Server file is not properly formatted");

	// TODO While loop, trim all whitespace and ignore empty lines
	// TODO Start building a Location when finding "Location {"
		// TODO BUILD THE Location CLASS
	// TODO Make sure that the line is at the right spot after building the Location
	// TODO Set the Location (function is done) and continue the loop
	// TODO Stop after reaching the end of the file

	// Printing loop, once per line in Serveruration file
	while (getline(Server_file, line))
	{
		// Register date and value
		/*std::string	date;
		float		value;
		size_t	sep = line.find('|');
		if (sep == std::string::npos)
		{
			date = line.substr(0, line.size());
			value = 0;
		}
		else
		{
			date = trim_whitespace(line.substr(0, sep));
			char* safeguard;
			value = std::strtof(trim_whitespace(line.substr(sep + 1, line.size() - sep)).c_str(), &safeguard);
			if (date == safeguard || *safeguard != '\0')
				value = 0;
		}

		// Validate date and value
		if (!isDate(date) || value == 0)
			throw BadConfigException("bad Server_fileut => ", date);
		else if (value < 0)
			throw BadConfigException("not a positive number.", "");
		else if (value > 1000)
			throw BadConfigException("too large a number.", "");

		// Find corresponding date (or lower) in data.csv
		std::map<std::string, float>::iterator it_data = this->_data.lower_bound(date);
		if (it_data->first != date && it_data != this->_data.begin())
			it_data--;
		float exchanged = value * it_data->second;*/

		// Set the Location into the vector
		this->setLocation(curr_Location);
	}

	// Close Serveruration file
	Server_file.close();
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

Server::Server(std::string filename): _location_num(0)
{
	this->_location_num = 0;
	this->parse_server(filename); //TODO review function...
	//std::cout << "Server constructed." << std::endl;
}

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

