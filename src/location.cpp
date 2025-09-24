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

void	Location::parse_location(std::istream& location_file) // TODO Write function
{
	std::string		line;

	// TODO Adequate checks
	// Basic checks in Configuration file
	//getline(location_file, line);
	//if (line != "date | value")
	//	throw BadConfigException("Location file is not properly formatted");

	// Printing loop, once per line in Configuration file
	while (getline(location_file, line))
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

/*
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

Location*	Location::clone(void) const
{
	//std::cout << "Location was cloned" << std::endl;
	return (new Location(*this));
}

// |----------------------
// | CONSTRUCTORS & DESTRUCTORS
// |----------------------

Location &Location::operator = (const Location &orig)
{
	if (this != &orig)
	{
		if (orig._sub_location)
			this->_sub_location = orig._sub_location.clone();
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
	//std::cout << "Location assignment copy-constructed." << std::endl;
	return (*this);
}

Location::Location(const Location &orig)
{
	*this = orig;
	//std::cout << "Location copy-constructed." << std::endl;
}

/*Location::Location(std::istream& location_file): _placeholder_num(0)
{
	this->_placeholder_num = 0;
	this->parse_Location(filename); //TODO review function...
	//std::cout << "Location constructed." << std::endl;
}*/

Location::Location(void)
{
	this->_sub_location = NULL;
	this->_name = NULL;
	this->_root = NULL;
	this->_index = NULL;
	this->_cgi_pass = NULL;
	this->_methods = NULL;
	this->_client_body_buffer_size = 0;
	this->_alias = false;
	//std::cout << "Location constructed." << std::endl;
}

Location::~Location(void)
{
	if (this->_sub_location)
		delete this->_sub_location;
	//std::cout << "Location destructed." << std::endl;
}

// |----------------------
// | OVERLOAD OPERATIONS
// |----------------------

// |----------------------
// | EXCEPTIONS
// |----------------------

