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

void	Location::parse_Location(std::istream& location_file) // TODO Write function
{
	std::string		line;

	// TODO Adequate checks
	// Basic checks in Configuration file
	//getline(location_file, line);
	//if (line != "date | value")
	//	throw BadConfigException("Location file is not properly formatted");

	// Printing loop, once per line in Configuration file
	while (getline(config_file, line))
	{
		line = trim_whitespace(line);
		// End function if Location segment ends
		if (line == "}")
			break ;

		//parse_other_info(); // TODO Incorporate various types of information
	}
}

// |----------------------
// | GETTERS & SETTERS
// |----------------------

/*void	Location::setplaceholder(placeholder loc)
{
	if (!loc)
	{
		this->_placeholder_num = 0;
	}
	else
	{
		this->_placeholders.push_back(loc);
		this->_placeholder_num++;
	}
}

placeholder const	&getplaceholder(unsigned int num) const
{
	if (num >= this->getLocNum())
		throw BadConfigException("Out of bounds", " - placeholders");
	return(this->_placeholders[num]);
}

unsigned int const	&getLocNum(void) const
{
	return (this->_placeholder_num);
}*/

// |----------------------
// | CONSTRUCTORS & DESTRUCTORS
// |----------------------

Location &Location::operator = (const Location &orig) // TODO Class isn't well defined yet
{
	if (this != &orig)
	{
		this->_placeholder_num = orig._placeholder_num;
		this->_placeholders = orig._placeholders;
	}
	//std::cout << "Location assignment copy-constructed." << std::endl;
	return (*this);
}

Location::Location(const Location &orig): _placeholder_num(orig._placeholder_num), _placeholders(orig._placeholders) // TODO Class isn't well defined yet
{
	//std::cout << "Location copy-constructed." << std::endl;
}

/*Location::Location(std::string filename): _placeholder_num(0)
{
	this->_placeholder_num = 0;
	this->parse_Location(filename); //TODO review function...
	//std::cout << "Location constructed." << std::endl;
}*/

Location::Location(void) // TODO Class isn't well defined yet
{
	//this->setplaceholder(NULL);
	//std::cout << "Location constructed." << std::endl;
}

Location::~Location(void)
{
	//std::cout << "Location destructed." << std::endl;
}

// |----------------------
// | OVERLOAD OPERATIONS
// |----------------------

// |----------------------
// | EXCEPTIONS
// |----------------------

