#include "Config.hpp"

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

/*bool	isDigit(char c)
{
	if (c >= '0' && c <= '9')
		return (true);
	return (false);
}*/

// |----------------------
// | MEMBER FUNCTIONS
// |----------------------

void	Config::parse_file(std::string filename) // TODO Write function
{
	std::ifstream	config_file(filename.c_str());
	std::string		line;

	// Basic checks in configuration file
	getline(config_file, line);
	if (line != "date | value") // TODO Adequate checks
		throw BadConfigException("Config file is not properly formatted");

	// TODO While loop, trim all whitespace and ignore empty lines
	// TODO Start building a Server when finding "server {"
	// TODO Make sure that the line is at the right spot after building the server
	// TODO Set the server (function is done) and continue the loop
	// TODO Stop after reaching the end of the file

	// Printing loop, once per line in configuration file
	while (getline(config_file, line))
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
			throw BadConfigException("bad config_fileut => ", date);
		else if (value < 0)
			throw BadConfigException("not a positive number.", "");
		else if (value > 1000)
			throw BadConfigException("too large a number.", "");

		// Find corresponding date (or lower) in data.csv
		std::map<std::string, float>::iterator it_data = this->_data.lower_bound(date);
		if (it_data->first != date && it_data != this->_data.begin())
			it_data--;
		float exchanged = value * it_data->second;*/

		// Set the server into the vector
		this->setServer(curr_server);
	}

	// Close configuration file
	config_file.close();
}

// |----------------------
// | GETTERS & SETTERS
// |----------------------

void	Config::setServer(Server serv)
{
	this->_servers.push_back(serv);
	this->_server_num++;
}

Server const	&getServer(unsigned int num) const
{
	if (num >= this->getServNum())
		throw BadConfigException("Out of bounds", " - Servers");
	return(this->_servers[num]);
}

unsigned int const	&getServNum(void) const
{
	return (this->_server_num);
}

// |----------------------
// | CONSTRUCTORS & DESTRUCTORS
// |----------------------

Config &Config::operator = (const Config &orig)
{
	if (this != &orig)
	{
		this->_server_num = orig._server_num;
		this->_servers = orig._servers;
	}
	//std::cout << "Config assignment copy-constructed." << std::endl;
	return (*this);
}

Config::Config(const Config &orig): _server_num(orig._server_num), _servers(orig._servers)
{
	//std::cout << "Config copy-constructed." << std::endl;
}

Config::Config(std::string filename): _server_num(0)
{
	this->_server_num = 0;
	this->parse_file(filename);
	//std::cout << "Config constructed." << std::endl;
}

Config::Config(void)
{
	this->setServer(NULL);
	//std::cout << "Config constructed." << std::endl;
}

Config::~Config(void)
{
	//std::cout << "Config destructed." << std::endl;
}

// |----------------------
// | OVERLOAD OPERATIONS
// |----------------------

// |----------------------
// | EXCEPTIONS
// |----------------------

Config::BadConfigException::BadConfigException(std::string msg, std::string value)
{
	std::ostringstream out;
	out << msg << value;
	_msg = out.str();
}

Config::BadConfigException::~BadConfigException() throw()
{
	//std::cout << "Error message destroyed" << std::endl;
}

const char *Config::BadConfigException::what() const throw()
{
	return (this->_msg.c_str());
}

config_fileutException::config_fileutException(std::string msg)
{
	std::ostringstream out;
	out << msg;
	_msg = out.str();
}

config_fileutException::~config_fileutException() throw()
{
	//std::cout << "Error message destroyed" << std::endl;
}

const char *config_fileutException::what() const throw()
{
	return (this->_msg.c_str());
}