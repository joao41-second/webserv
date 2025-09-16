#pragma once

#ifndef CONFIG_H
#define CONFIG_H

#include <iostream>
#include <sstream>
#include <fstream>
#include <locale>
#include <iomanip>
#include <cstdlib>
#include <cmath>
#include <climits>
#include <stdint.h>

#include <map>
#include <algorithm>
#include <typeinfo>

class Config
{
public:
	Config();
	//Config(std::string input);
	Config(const Config &orig);
	Config &operator = (const Config &orig);
	virtual ~Config();

	//unsigned int const	&size(void) const;
	//void					incSize(void);
	void				set_data(void);
	//void				set_input(std::string input);

	void		print_values(std::string input);

	class BadConfigException: public std::exception
	{
	private:
		std::string _msg;
	public:
		BadConfigException(std::string msg, std::string value);
		virtual ~BadConfigException() throw();
		virtual const char *what() const throw();
	};
private:
	std::map<std::string, float> _data;
	unsigned int	 _size;
};

class InputException: public std::exception
{
private:
	std::string _msg;
public:
	InputException(std::string msg);
	virtual ~InputException() throw();
	virtual const char *what() const throw();
};

#endif