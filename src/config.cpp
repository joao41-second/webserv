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

bool	isDigit(char c)
{
	if (c >= '0' && c <= '9')
		return (true);
	return (false);
}

// |----------------------
// | MEMBER FUNCTIONS
// |----------------------

/*void	Config::print_values(std::string input)
{
	std::ifstream	inp(input.c_str());
	std::string		line;

	// Check input header
	getline(inp, line);
	if (line != "date | value")
		throw InputException("Argument file lacks proper header (date | value)");

	// Printing loop, once per line in input file
	while (getline(inp, line))
	{
	try
	{
		// Register date and value
		std::string	date;
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
			throw BadConfigException("bad input => ", date);
		else if (value < 0)
			throw BadConfigException("not a positive number.", "");
		else if (value > 1000)
			throw BadConfigException("too large a number.", "");

		// Find corresponding date (or lower) in data.csv
		std::map<std::string, float>::iterator it_data = this->_data.lower_bound(date);
		if (it_data->first != date && it_data != this->_data.begin())
			it_data--;
		float exchanged = value * it_data->second;

		// Print valid results
		std::cout << date << " => " << value << " => " << exchanged << std::endl;
	}
	catch (std::exception &e)
	{
		std::cerr << "Error: " << e.what() << std::endl;
	}
	}
	// Close input file
	inp.close();
}*/

// |----------------------
// | GETTERS & SETTERS
// |----------------------

/*void	Config::set_data(void)
{
	std::ifstream	data("./data.csv");
	std::string		line;

	// Check data.csv header
	getline(data, line);
	if (line != "date,exchange_rate")
		throw InputException("data.csv lacks proper header (date,exchange_rate)");

	// Setting loop, once per line in input file
	while(getline(data, line))
	{
		// Validate separator
		size_t	sep = line.find(',');
		if (sep == std::string::npos)
			continue ;

		// Validate and register date and value
		std::string date = trim_whitespace(line.substr(0, sep));
		char* safeguard;
		this->_data[date] = std::strtof(trim_whitespace(line.substr(sep + 1, line.size() - sep)).c_str(), &safeguard); // Map-specific insertion method
		//this->_data.insert(std::make_pair(date, std::strtof(trim_whitespace(line.substr(sep + 1, line.size() - sep)).c_str(), &safeguard)));
		if (date == safeguard || *safeguard != '\0')
			throw InputException("data.csv is not properly formatted");
	}
	// Close data.csv
	data.close();
}*/

// |----------------------
// | CONSTRUCTORS & DESTRUCTORS
// |----------------------

Config &Config::operator = (const Config &orig)
{
	if (this != &orig)
		this->_data = orig._data;
	//std::cout << "Config assignment copy-constructed." << std::endl;
	return (*this);
}

Config::Config(const Config &orig): _data(orig._data)
{
	//std::cout << "Config copy-constructed." << std::endl;
}

Config::Config(std::string filename)
{
	//this->set_data(); // TODO
	//std::cout << "Config constructed." << std::endl;
}

Config::Config(void)
{
	//this->set_data(); // TODO
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

InputException::InputException(std::string msg)
{
	std::ostringstream out;
	out << msg;
	_msg = out.str();
}

InputException::~InputException() throw()
{
	//std::cout << "Error message destroyed" << std::endl;
}

const char *InputException::what() const throw()
{
	return (this->_msg.c_str());
}