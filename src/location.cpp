#include "../include/config.hpp"
#include "../include/server.hpp"
#include "../include/location.hpp"

// |----------------------
// | HELPER FUNCTIONS
// |----------------------

/*bool	isDelim(char c)
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
}*/

// |----------------------
// | MEMBER FUNCTIONS
// |----------------------

void	Location::parse_location(std::istream& location_file, std::string line) // TODO Write function
{
	// TODO Adequate checks
	// Basic checks in Configuration file
	//getline(location_file, line);
	//if (line != "date | value")
	//	throw BadConfigException("Location file is not properly formatted");

	// Set name
	unsigned int range = line.size();
	if (line.at(range - 1) == '{')
	{
		range--;
	}
	this->_name = trim_whitespace(line.substr(8, range)); // TODO escrever setName()?
	if (this->_name == "") // TODO escrever getName()?
	{
		throw InputException("Empty field (server_name)");
	}

	// Printing loop, once per line in Configuration file
	while (getline(location_file, line))
	{
		line = trim_whitespace(line);
		// End function if Location segment ends
		if (line == "}")
			break ;

		// TODO Consider using a switch for this
		if (line.compare(0, 8, "location") == 0)
		{
			// Only create a location when one is declared
			//Location* curr_location = new Location();
			//curr_location->parse_location(location_file, line); // TODO Add error case (ex.: bool)

			// Set the Location into _sub_location
			//this->setSubLocation(curr_location);
			this->setSubLocation(new Location(location_file, line));
			if (this->_sub_location == NULL)
				throw InputException("Input error (location)");
			// TODO Make sure that the line is at the right spot after building the Location
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
		else if (line.compare(0, 8, "cgi_pass") == 0)
		{
			this->_cgi_pass = trim_whitespace(line.substr(5)); // TODO escrever setPass()?
			if (this->_cgi_pass == "") // TODO escrever getPass()?
				throw InputException("Empty field (cgi_pass)");
		}
		else if (line.compare(0, 13, "allow_methods") == 0)
		{
			this->setMethods(trim_whitespace(line.substr(13)));
			if (this->_methods.empty())
				throw InputException("Empty field (allow_methods)");
		}
		else if (line.compare(0, 24, "client_body_buffer_size") == 0)
		{
			char *safeguard;
			this->_client_body_buffer_size = std::strtoul(trim_whitespace(line.substr(24)).c_str(), &safeguard, 10);
			// TODO escrever setBufferSize()?
			if (*safeguard != '\0')
			{
				throw InputException("Invalid client_body_buffer_size");
			}
			// TODO Alterar se for para usar unsigned int
		}
		else if (line.compare(0, 5, "alias") == 0)
		{
			this->_alias = true; // TODO escrever setAlias()? Alterar se se converter em string
		}
	}
}

// |----------------------
// | GETTERS & SETTERS
// |----------------------

void	Location::setMethods(std::string const str)
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

void	Location::setOneMethod(std::string word)
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

void	Location::setSubLocation(Location* loc)
{
	if (loc)
	{
		this->_sub_location = loc;
	}
}

std::string const	&Location::getName(void) const
{
	return(this->_name);
}

std::string const	&Location::getRoot(void) const
{
	return(this->_root);
}

std::string const	&Location::getIndex(void) const
{
	return(this->_index);
}

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
	//std::cout << "Location assignment copy-constructed." << std::endl;
	return (*this);
}

Location::Location(const Location &orig)
{
	*this = orig;
	//std::cout << "Location copy-constructed." << std::endl;
}

Location::Location(std::istream& location_file, std::string line)
{
	this->parse_location(location_file, line);
	//std::cout << "Location constructed." << std::endl;
}

Location::Location(void)
{
	this->setMethods("");
	this->_sub_location = NULL;
	this->_name = ""; // TODO escrever setName()?
	this->_root = ""; // TODO escrever setRoot()?
	this->_index = ""; // TODO escrever setIndex()?
	this->_cgi_pass = ""; // TODO escrever setPass()?
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

